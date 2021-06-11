#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <vector>
#include <string>
#include <utility>

class Password_Preprocessor {
    private:
        std::vector<std::string> password_list;
        size_t list_size;
        std::vector<std::pair<std::string, int>> password_distances;
        int calculate_min_lev(size_t);
        void sort_by_lev_dist();
        void lev_subprocess(int, int);
    public:
        Password_Preprocessor(std::vector<std::string> password_list);
        std::vector<std::pair<std::string, int>> process();

};

#endif /* PREPROCESSING_H */
