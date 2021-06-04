#include <benchmark/benchmark.h>
#include "../src/levenshtein.h"
#include "./fsu_lev/levenshtein.hpp"

using namespace std;

static void BM_lev_dist(benchmark::State &state) {
    for (auto _ : state) {
        string s1 = "kitten";
        string s2 = "sitting";
        int dist = lev_dist(s1, s2);
    }
}

static void BM_fsu_lev_dist(benchmark::State &state) {
    for (auto _ : state) {
        string s1 = "kitten";
        string s2 = "sitting";
        int dist = levenshtein_distance(s1.size(), s1, s2.size(), s2);
    }
}

BENCHMARK(BM_lev_dist);
BENCHMARK(BM_fsu_lev_dist);

BENCHMARK_MAIN();
