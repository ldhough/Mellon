#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "preprocessing.h"
#include "password_tree.h"

using namespace std;

vector<string> read_passwords(string in_file) {

    vector<string> v;

    ifstream f(in_file);
    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            v.push_back(line);
        }
    } else {
        cout << "Could not open file provided." << endl;
    }

    return v;
}

int main(int argc, char **argv) {

    // Open password textfile
    // should only contain unique passwords separated by newlines
    
    vector<string> vec = read_passwords(argv[1]);
    if (vec.empty()) {
        cout << "No passwords to parse, check file." << endl;
        return -1;
    }
    vec.push_back("");
    vec.push_back("");
    Password_Preprocessor processor(vec);
    auto result = processor.process();
    vector<string> rules;
    rules.push_back("1");
    rules.push_back("2");
    Password_Tree t(result, rules);
    t.build_tree();
    return 0;
}
