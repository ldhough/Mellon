#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <vector>
#include <string>
#include <utility>

class Password_Preprocessor {
    private:
        std::vector<std::string> password_list;
        std::vector<std::pair<std::string, int>> password_distances;
        void calculate_lev();
        void sort_by_lev_dist();
    public:
        Password_Preprocessor(std::vector<std::string> password_list);
        std::vector<std::pair<std::string, int>> process();

};

#endif /* PREPROCESSING_H */
