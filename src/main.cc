#include <iostream>
#include <string>
#include <vector>
#include "preprocessing.h"
#include "password_tree.h"
#include "utils.h"
#include "rules.h"

using namespace std;

// Program usage: mellon_processing </path/to/passwords> </path/to/rules>

int main(int argc, char **argv) {

    cout << endl << GREEN << "PROGRAM STARTING..." << RESET << endl << endl;

    // Validate program arguments 
    if (argc != 3) {
        cerr << RED << "ERROR" << RESET << ", invalid arguments, usage is: " << GREEN << "mellon_processing " << RESET << BLUE << "</path/to/passwords> </path/to/rules>" << RESET << endl;
        return -1;
    }

    // Open password textfile
    // should only contain unique passwords separated by newlines
    cout << BLUE << "INFO: " << RESET << "Attempting to open password file..." << endl;
    vector<string> passwords_vector = read_lines_to_vec(argv[1]);
    if (passwords_vector.empty()) {
        cerr << RED << "ERROR: " << RESET << "No passwords to parse, check file." << endl;
        return -1;
    }

    // Open rules textfile
    // should only contain unique rules separated by newlines
    cout << BLUE << "INFO: " << RESET << "Attempting to open rules file..." << endl;
    vector<string> rules_vector = read_lines_to_vec(argv[2]);
    if (rules_vector.empty()) {
        cerr << RED << "ERROR: " << RESET << "No rules to use, check rules file. Should be formatted as newline separated valid rules, check file." << endl;
        return -1;
    }

    // Validate rules


    Password_Preprocessor processor(passwords_vector);
    auto processed_passwords = processor.process();
    //Password_Tree password_tree(processed_passwords, rules_vector);
    //password_tree.build_tree();
    return 0;
}
