#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <vector>
#include <string>
#include <utility>
#include <mutex>

class Password_Preprocessor {
    private:
        std::mutex distances_mutex;

        std::vector<std::string> password_list;
        size_t list_size;

        std::vector<std::pair<std::string, unsigned int>> password_distances;

        void calculate_minimum_lev_distances();
        //int calculate_min_remaining_lev(size_t);
        void sort_by_lev_dist();
        //void lev_subprocess(size_t, size_t);
    public:
        Password_Preprocessor(std::vector<std::string> password_list);
        std::vector<std::pair<std::string, unsigned int>> process();
        bool execute_parallel = true;

};

#endif /* PREPROCESSING_H */
