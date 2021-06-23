#include "preprocessing.h"
#include "levenshtein.h"
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <thread>
#include <cmath>
#include <climits>

using namespace std;

// Password_Preprocessor constructor
Password_Preprocessor::Password_Preprocessor(vector<string> password_list) {
    this->password_list = password_list;
    this->list_size = this->password_list.size();
    this->password_distances.resize(this->list_size); 
}

inline int Password_Preprocessor::calculate_min_lev(size_t for_index) {
   
    int min_lev = INT_MAX;

    for (size_t i = for_index; i < this->list_size; i++) {
        for (size_t j = i+1; j < this->list_size; j++) {
            int lev_distance = lev_dist(this->password_list.at(i), this->password_list.at(j));
            if (lev_distance < min_lev)
                min_lev = lev_distance;
            cout << "distance between " << this->password_list.at(i) << " and " << this->password_list.at(j) << " is " << lev_distance << endl;
        }
    }

    return min_lev;
}

// Calculates lev dist for passwords in range [i, n)
inline void Password_Preprocessor::lev_subprocess(size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        auto pw = password_list.at(i);
        password_distances[i] = pair<string, int>(pw, this->calculate_min_lev(i));
    }
}

vector<pair<string, int>> Password_Preprocessor::process() {

    /*
     * We want to compute the minimum levenshtein distance from one password to another in the set for each password.  
     * Because the distance is symmetric each password i only needs to be compared to passwords i+1 -> n.  To parallelize
     * this well, we want to know the total number of distances to calculate.  The number of distances computed can be
     * expressed as ~~ sum of i from i=0 to n-1 ~~ where n is the size of the list.  One password is compared to no
     * passwords, one is compared to one passwords ... one is compared to n-1 passwords. Closed form is (1/2)(n-1)n
     */ 

    size_t n = this->list_size;
    // long is needed to hold number of computations needed for large password lists which exceed INT_MAX
    long num_distances = ceil(0.5*(n-1)*n);

    const unsigned int num_cores = thread::hardware_concurrency() / 2; // **TEMP** until a portable way to discover physical cores is implemented
    int cores_unassigned = num_cores;

    const long optimal_comps_per_core = num_distances / num_cores;

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

    if (stack_size > 1) {

        thread tid[stack_size];

        cout << "Creating " << stack_size << " threads to compute minimum Levenshtein distances." << endl;

        for (size_t i = 0; i < stack_size; i++) {
            auto range = processing_stack.top();
            processing_stack.pop();
            tid[i] = thread(&Password_Preprocessor::lev_subprocess, this, range.first, range.second);
        }

        for (thread &t : tid) {
            t.join();
        }
    } else {
        cout << "Computing minimum Levenshtein distances." << endl;    
        this->lev_subprocess(0, n-1);
    }

    cout << "Computing minimum Levenshtein distances completed." << endl;

    return this->password_distances;
}

void Password_Preprocessor::sort_by_lev_dist() {

}
