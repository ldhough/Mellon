#include <string>
#include <algorithm>
#include "levenshtein.h"

using namespace std;

// Compute the Levenshtein Distance between two strings
unsigned int lev_dist(string &s1, string &s2) {

    // First row/col is substrings compared against the null character
    size_t col_count = s1.size()+1, row_count = s2.size()+1;
    unsigned int r1[col_count];
    unsigned int r2[col_count];

    // Initialize first row to sequence, and what will be first comparison row to all zeroes
    for (size_t i = 0; i < col_count; i++)
        r1[i] = i;
    
    unsigned int *mutating_row;
    unsigned int *comparison_row;
    for (size_t row = 1; row < row_count; row++) {
        /*
         * Swap which row is being operated on and storing the computed distances, use the
         * previously operated on row to store the results of the last row of operations
         */
        if (row & 1) {
            mutating_row = r2;
            comparison_row = r1;
        } else {
            mutating_row = r1;
            comparison_row = r2;
        }
        mutating_row[0] = row; // Initialize first element in a row
        for (size_t pos = 1; pos < col_count; pos++) {
            if (s1[pos-1] == s2[row-1]) {
                mutating_row[pos] = comparison_row[pos-1];
            } else {
                mutating_row[pos] = min(mutating_row[pos-1], min(comparison_row[pos], comparison_row[pos-1])) + 1;
            }
        }
    }
    
    // Return final element of row containing result
    return (row_count & 1) ? r1[col_count-1] : r2[col_count-1];
}
