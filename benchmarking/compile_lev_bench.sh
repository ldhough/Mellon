g++ lev_dist_benchmarking.cc ../src/levenshtein.cc ./fsu_lev/levenshtein.cpp -O3 -std=c++11 -isystem ../../benchmark/include -L../../benchmark/build/src -lbenchmark -lpthread -o lev_benchmark
