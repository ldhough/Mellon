#include <iostream>
#include <string>
#include <vector>
#include "preprocessing.h"
#include "password_tree.h"
#include "utils.h"
#include "rule.h"

using namespace std;

// Program usage: mellon_processing </path/to/passwords> </path/to/rules>

int main(int argc, char **argv) {

    cout << endl << GREEN << "PROGRAM STARTING..." << RESET << endl << endl;

    // Validate program arguments 
    if (argc != 3) {
        cerr << RED_ERR ", invalid arguments, usage is: " << GREEN << "mellon_processing " << RESET << BLUE << "</path/to/passwords> </path/to/rules>" << RESET << endl;
        return -1;
    }

    // Open password textfile
    // should only contain unique passwords separated by newlines
    cout << BLUE_INFO ": Attempting to open password file: "  << argv[1] << endl;
    vector<string> passwords_vector = read_lines_to_vec(argv[1]);
    if (passwords_vector.empty()) {
        cerr << RED << "ERROR: " << RESET << "No passwords to parse, check file." << endl;
        return -1;
    }

    // Open rules textfile
    // should only contain unique rules separated by newlines
    cout << BLUE_INFO ": Attempting to open rules file: " << argv[2] << endl;
    vector<string> rules_vector = read_lines_to_vec(argv[2]);
    if (rules_vector.empty()) {
        cerr << RED_ERR ": No rules to use, check rules file. Should be formatted as newline separated valid rules, check file." << endl;
        return -1;
    }

    // Build vector of rule functions/data from string form hashcat functions/rules
    
    vector<Rule> rule_v;
    for (string try_rule : rules_vector) {
        try {
            Rule r = Rule::build_rule(try_rule);
            rule_v.push_back(r);
        } catch (logic_error &e) {
            cerr << e.what() << endl;
        }
    }

    
    for (string password : passwords_vector) {
        Rule r = rule_v[1];
        password = r.apply_rule(password);
        cout << "Modified password: " << password << endl;
    }
    

    Password_Preprocessor processor(passwords_vector);
    auto processed_passwords = processor.process();
    //Password_Tree password_tree(processed_passwords, rules_vector);
    //password_tree.build_tree();

    cout << endl;
    return 0;
}
