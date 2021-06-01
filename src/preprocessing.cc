#include "preprocessing.h"
#include "levenshtein.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

// Password_Preprocessor constructor
Password_Preprocessor::Password_Preprocessor(vector<string> password_list) {
    this->password_list = password_list;
}

void Password_Preprocessor::calculate_lev() {
    for (size_t i = 0; i < this->password_list.size(); i++) {
        for (size_t j = i+1; j < this->password_list.size(); j++) {
            int lev_distance = lev_dist(this->password_list.at(i), this->password_list.at(j));
            cout << "Calculated lev_dist of " << lev_distance << " for " << this->password_list.at(i) << " and " << this->password_list.at(j) << endl;
        }
    }
}

void Password_Preprocessor::sort_by_lev_dist() {

}

vector<pair<string, int>> Password_Preprocessor::process() {
    this->calculate_lev();
    return this->password_distances;
}
