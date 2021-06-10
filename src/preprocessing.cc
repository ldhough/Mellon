#include "preprocessing.h"
#include "levenshtein.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <thread>
#include <cmath>

using namespace std;

// Password_Preprocessor constructor
Password_Preprocessor::Password_Preprocessor(vector<string> password_list) {
    this->password_list = password_list;
    this->list_size = this->password_list.size();
}

int Password_Preprocessor::calculate_min_lev(size_t for_index) {
   
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

void Password_Preprocessor::sort_by_lev_dist() {

}

vector<pair<string, int>> Password_Preprocessor::process() {

    /*
     * We want to compute the minimum levenshtein distance from one password to another in the set for each password.  
     * Because the distance is symmetric each password i only needs to be compared to passwords i+1 -> n.  To parallelize
     * this well, we want to know the total number of distances to calculate.  The number of distances computed can be
     * expressed as ~~ sum of i from i=0 to n-1 ~~ where n is the size of the list.  One password is compared to no
     * passwords, one is compared to one passwords ... one is compared to n-1 passwords. Closed form is (1/2)(n-1)n
     */ 

    int n = this->list_size;
    // long is needed to hold number of computations needed for large password lists which exceed INT_MAX
    long num_distances = ceil(0.5*(n-1)*n);

    const int num_cores = thread::hardware_concurrency() / 2; // **TEMP** until a portable way to discover physical cores is implemented
    int cores_unassigned = num_cores;

    const long optimal_comps_per_core = num_distances / num_cores;

    // Want threads to process all computations for an individual password to prevent overhead in having threads safely communicate
    // Will try to keep the number of computations as close as possible to optimal_dists_per_core with this constraint in mind
    
    int earliest_unassigned = 0; // Next unassigned password index
    for (size_t core = 0; core < num_cores; core++) {
        
        vector<int> passwords_on_thread;
        int cumulative_computations = 0;
        
        // Check if adding the number of computations for the next password to this core will be
        // closer or further away from optimal_computations_per_core
        
        int computations_password_i = n - earliest_unassigned - 1;
        int proposed_comps = cumulative_computations + computations_password_i;

        while (optimal_comps_per_core - proposed_comps < optimal_comps_per_core - cumulative_computations) {
            
            cumulative_computations = proposed_comps;
            passwords_on_thread.push_back(earliest_unassigned);
            earliest_unassigned++;
            computations_password_i = n - earliest_unassigned - 1;
            proposed_comps = cumulative_computations + computations_password_i;
        }
        cores_unassigned--;
    }

    this->calculate_min_lev(0);
    return this->password_distances;
}
