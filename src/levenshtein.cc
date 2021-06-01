#include <string>
#include <algorithm>
#include "levenshtein.h"

using namespace std;

// Compute the Levenshtein Distance between two strings
int lev_dist(string &s1, string &s2) {

    // First row/col is substrings compared against the null character
    string col_str = string("\n", 1) + s1;
    string row_str = string("\n", 1) + s2;
    size_t col_count = col_str.size(), row_count = row_str.size();
    int r1[col_count];
    int r2[col_count];

    // Initialize first row to sequence, and what will be first comparison row to all zeroes
    for (size_t i = 0; i < col_count; i++) {
        r1[i] = i;
        r2[i] = 0;
    }

    for (size_t row = 1; row < row_count; row++) {
        /*
         * Swap which row is being operated on and storing the computed distances, use the
         * previously operated on row to store the results of the last row of operations
         */
        int *r1_ref = r1;
        int *r2_ref = r2;
        auto mutating_row = (row & 1) ? r2_ref : r1_ref;
        auto comparison_row = (row & 1) ? r1_ref : r2_ref;
        mutating_row[0] = row; // Initialize first element in a row
        for (size_t pos = 1; pos < col_count; pos++) {
            if (row_str[row] == col_str[pos]) {
                mutating_row[pos] = comparison_row[pos-1];
            } else {
                mutating_row[pos] = min(mutating_row[pos-1], min(comparison_row[pos], comparison_row[pos-1])) + 1;
            }
        }
    }

    // Return final element of row containing result
    return (row_count & 1) ? r1[col_count-1] : r2[col_count-1];
}
