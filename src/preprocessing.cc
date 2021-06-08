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

    int num_cores = thread::hardware_concurrency();

    long distances_per_core = num_distances / num_cores;

    this->calculate_min_lev(0);
    return this->password_distances;
}
