#include "preprocessing.h"
#include "levenshtein.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <thread>

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

    int num_cores = thread::hardware_concurrency();

    this->calculate_min_lev(0);
    return this->password_distances;
}
