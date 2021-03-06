#include "preprocessing.h"
#include "levenshtein.h"
#include "utils.h"
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <thread>
#include <cmath>
#include <climits>
#include <algorithm>
#include <mutex>

#define DEBUG 0

using namespace std;

#if DEBUG
mutex cout_mutex;
#endif

// Password_Preprocessor constructor
Password_Preprocessor::Password_Preprocessor(vector<string> password_list) {

    this->password_list = password_list;
    this->list_size = this->password_list.size();
    this->password_distances.resize(this->list_size); 

}

inline void Password_Preprocessor::sort_by_lev_dist() {

    sort(begin(this->password_distances), end(this->password_distances),
        [](pair<string, int> a, pair<string, int> b) {
            return a.second < b.second;
        });

}

/*
 *
 * Compare each password to every other password to calculate the minimum levenshtein distance from any password
 * to any other password in the list of passwords.  Because levenshtein / edit distance is symmetric, if we store
 * already computed minimum distances as we advance down the list, when we reach a given password i we only have
 * to compute the distance to passwords i+1 -> n because distances to all passwords before i have already been
 * computed
 *
 */

inline void Password_Preprocessor::calculate_minimum_lev_distances() {
    
    size_t n = this->list_size;

    // Initialize password_distances to contain password strings and distances from the first password
    string first = this->password_list.at(0);
    unsigned int first_min = UINT_MAX;
    for (size_t i = 1; i < n; i++) {

        string compare_password = this->password_list.at(i);
        unsigned int distance = lev_dist(first, compare_password);

        this->password_distances[i] = {compare_password, distance};
        if (distance < first_min)
            first_min = distance;

    }
    this->password_distances[0] = {first, first_min};

    // Calculate min lev distances for all other passwords
    for (size_t i = 1; i < n; i++) {

        string password = this->password_list.at(i);
        unsigned int min_lev_from_uncalculated = UINT_MAX;

        for (size_t j = i+1; j < n; j++) {

            string compare_password = this->password_list.at(j);
            unsigned int distance = lev_dist(password, compare_password);
            if (distance < min_lev_from_uncalculated)
                min_lev_from_uncalculated = distance;

            if (distance < this->password_distances[i].second)
                this->password_distances[i].second = distance;

        }

        if (min_lev_from_uncalculated < this->password_distances[i].second)
            this->password_distances[i].second = min_lev_from_uncalculated;
    }

}

vector<pair<string, unsigned int>> Password_Preprocessor::process() {

   this->calculate_minimum_lev_distances();
   this->sort_by_lev_dist();
   return this->password_distances;

}

/*
inline int Password_Preprocessor::calculate_min_remaining_lev(size_t for_index) {
   
    int min_lev = INT_MAX;
    size_t i = for_index;
    for (size_t j = i+1; j < this->list_size; j++) {
        #if DEBUG
        cout_mutex.lock();
        cout << "Comparing password " << this->password_list.at(i) << " to " << this->password_list.at(j) << endl;
        cout << "Distance between compared passwords is " << lev_dist(this->password_list.at(i), this->password_list.at(j)) << endl;
        cout_mutex.unlock();
        #endif
        int lev_distance = lev_dist(this->password_list.at(i), this->password_list.at(j));
        if (lev_distance < min_lev)
            min_lev = lev_distance;
    }

    #if DEBUG
    cout_mutex.lock();
    cout << "Returning min_lev " << min_lev << " for password " << this->password_list.at(for_index) << endl;
    cout_mutex.unlock();
    #endif

    return min_lev;
}

// Calculates lev dist for passwords in range [i, n)
inline void Password_Preprocessor::lev_subprocess(size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        auto pw = password_list.at(i);
        #if DEBUG
        if (pw == "")
            cout << "password is empty string" << endl;
        #endif
        password_distances[i] = pair<string, int>(pw, this->calculate_min_remaining_lev(i));
    }
}


vector<pair<string, int>> Password_Preprocessor::process() {

    
     // We want to compute the minimum levenshtein distance from one password to another in the set for each password.  
     // Because the distance is symmetric each password i only needs to be compared to passwords i+1 -> n.  To parallelize
     // this well, we want to know the total number of distances to calculate.  The number of distances computed can be
     // expressed as ~~ sum of i from i=0 to n-1 ~~ where n is the size of the list.  One password is compared to no
     // passwords, one is compared to one passwords ... one is compared to n-1 passwords. Closed form is (1/2)(n-1)n
     

    size_t n = this->list_size;
    // long is needed to hold number of computations needed for large password lists which exceed INT_MAX
    long num_distances = ceil(0.5*(n-1)*n);

    const unsigned int num_cores = thread::hardware_concurrency(); // **TEMP** until a portable way to discover physical cores is implemented
    int cores_unassigned = num_cores;
    const long optimal_comps_per_core = num_distances / num_cores;

    #if DEBUG
    cout << "Maximum threads to create is: " << num_cores << endl;
    cout << "num_distances is: " << num_distances << endl;
    cout << "optimal_comps_per_core = " << optimal_comps_per_core << endl;
    #endif

    // Want threads to process all computations for an individual password to prevent overhead in having threads safely communicate
    // Will try to keep the number of computations as close as possible to optimal_dists_per_core with this constraint in mind
   
    unsigned int earliest_unassigned = 0; // Next unassigned password index
    stack<pair<int, int>> processing_stack;
    for (size_t core = 0; core < num_cores; core++) {
        
        const size_t pass_start_index = earliest_unassigned;
        size_t pass_end_index = earliest_unassigned; // exclusive range
        int cumulative_computations = 0;
        
        // Check if adding the number of computations for the next password to this core will be
        // closer or further away from optimal_computations_per_core
        
        int computations_password_i = n - earliest_unassigned - 1; // Number of Levenshtein distances to calc for a single pw i
        // Proposed cumulative computation; what the cumulative_computations will be if
        // another password and its associated computations are assigned to this core
        int proposed_comps = cumulative_computations + computations_password_i;

        while (abs(optimal_comps_per_core - proposed_comps) < abs(optimal_comps_per_core - cumulative_computations)) {
            
            cumulative_computations = proposed_comps;
            earliest_unassigned++;
            pass_end_index++;
            computations_password_i = n - earliest_unassigned - 1;
            proposed_comps = cumulative_computations + computations_password_i;
        }

        cores_unassigned--;
        // If all cores have been assigned passwords and there are still passwords left unassigned, assign to final core
        // OR if no passwords were assigned to this core assign remainder to this core - this is likely to occur when
        // the number representing optimal computations per core is a small one and the number of computations needed
        // for a single password is > the total number of computations evenly distributed across cores
        if ((!cores_unassigned && earliest_unassigned < n-1) || !cumulative_computations) {
            pass_end_index = n; // Used as exclusive upper bound so not n-1
        }

        pair<size_t, size_t> range = {pass_start_index, pass_end_index};
        processing_stack.push(range);

        // If reached end of password list don't continue attempting to assign passwords to cores
        // even if there are still cores that have not been assigned passwords
        if (pass_end_index == n)
            break;
    }

    size_t stack_size = processing_stack.size();
    processing_stack.top().second = n; // End should always be n

    #if DEBUG
    auto ps = processing_stack;
    for (size_t i = 0; i < stack_size; i++) {
        auto pair = ps.top();
        ps.pop();
        cout << "Range in processing_stack is " << pair.first << " - " << pair.second << endl;
    }

    cout << "PRE COMPUTATIONS: " << endl;
    for (auto p : this->password_distances)
        cout << "Distance for password " << p.first << " is " << p.second << endl;

    #endif

    if (stack_size > 1 && execute_parallel) {

        thread tid[stack_size];

        cout << BLUE_INFO ": Creating " << stack_size << " threads to compute minimum Levenshtein distances." << endl;

        for (size_t i = 0; i < stack_size; i++) {
            auto range = processing_stack.top();
            processing_stack.pop();
            tid[i] = thread(&Password_Preprocessor::lev_subprocess, this, range.first, range.second);
        }

        for (thread &t : tid) {
            t.join();
        }
    } else {
        cout << BLUE_INFO ": Computing minimum Levenshtein distances." << endl;    
        this->lev_subprocess(0, n);
    }

    cout << GREEN_SUCCESS ": Computing minimum Levenshtein distances completed." << endl;

    #if DEBUG
    cout << "PRE SORT: " << endl;
    for (auto p : this->password_distances)
        cout << "Distance for password " << p.first << " is " << p.second << endl;
    cout << "POST SORT: " << endl; 
    #endif

    this->sort_by_lev_dist();

    #if DEBUG
    for (auto p : this->password_distances)
        cout << "Distance for password " << p.first << " is " << p.second << endl;
    #endif

    return this->password_distances;
}
*/
