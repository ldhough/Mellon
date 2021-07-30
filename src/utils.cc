#include "utils.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// Reads each line of a file into a string vector, discards blank lines
vector<string> read_lines_to_vec(string in_file) {

    vector<string> v;

    ifstream f(in_file);
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            if (line != "")
                v.push_back(line);
        }
    } else {
        cerr << "ERROR: Could not open file provided." << endl;
    }

    return v;
}

