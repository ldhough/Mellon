#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <map>
#include <utility>
#include <vector>
#include <sstream>
#include "rules.h"
#include "utils.h"

using namespace std;

/*
 * A rulefile consists of rules separated by newlines, a single rule may be made
 * out of multiple "primitive" hashcat rules/functions separated by spaces
 *
 * concrete_rules stores a list of composite rules, where a composite rule is
 * a list of function pointers to functions that imitate hashcat functions, as
 * well as data to support running these functions in the form of a Rule_Data
 * instance
 *
 * this list is built by calling build_concrete_rules
 *
 */

typedef void (*fptr)(string &s, Rules::Rule_Data r);

// Maps hashcat "primitive" funcs/rules signifiers to pointers to imitating functions
//const map<char, void (*)(string&, Rules::Rule_Data)> rule_primitives = {pair<char, fptr>('$', &Rules::append_char)};

vector<vector<pair<fptr, Rules::Rule_Data>>> Rules::concrete_rules;

const map<char, fptr> rule_primitives = {pair<char, fptr>('$', &Rules::append_char)};

inline fptr is_valid_len_1_rule(string &rule, bool &is_valid) {
    return rule_primitives.at('$');
}

void build_concrete_rules(vector<string> rules) {

    unsigned int ith_rule = 0;
    for (auto rule : rules) {

        bool valid_hashcat_rules = true;
        vector<pair<fptr, Rules::Rule_Data>> rules_in_line;
        
        stringstream ss(rule);
        string try_rule;

        while (ss >> try_rule) {
            
            // Hashcat rules consist of 1-3 symbols, (except "Extract memory/XNMI" which is one of the TODO rules)
            
            size_t try_rule_len = try_rule.size();
            if (try_rule_len > 3) {
                cerr << RED << "ERROR: " << RESET << "Invalid rule on nonblank line " << ith_rule << ", cannot use line as rule" << endl;
                valid_hashcat_rules = false;
                break;
            }

            //bool valid_hashcat_function = true;
            fptr fp;
            Rules::Rule_Data rd;
            switch (try_rule_len) {
                case 1:
                    fp = is_valid_len_1_rule(try_rule, valid_hashcat_rules);
                    break;
                case 2:
                    break;
                case 3:
                    break;
            }

            if (valid_hashcat_rules) {
               rules_in_line.push_back({fp, rd}); 
            } else {
                cerr << RED << "ERROR: " << RESET << "Invalid rule on nonblank line " << ith_rule << ", cannot use line as rule" << endl;
                break;
            }
        }

        if (valid_hashcat_rules)
            Rules::concrete_rules.push_back(rules_in_line);

        ith_rule++;
    }
}

// HASHCAT RULE FUNCTION IMITATIONS AFTER THIS POINT * * * * * * * * * * * * * * * * * * * *

// TN, toggle character case at pos N
void toggle_char(string &s, Rules::Rule_Data args) {
    try {
        char c = s.at(args.N);
        if (65 <= c && c <= 90) // Is A-Z
            s.at(args.N) = tolower(c);
        else if (97 <= c && c <= 122) // Is a-z
            s.at(args.N) = toupper(c);
    } catch (const out_of_range &oob) {
        cerr << RED << "ERROR, " << RESET << "index oob: " << oob.what() << endl;
    }
}

// $X, append character X
void Rules::append_char(string &str, Rules::Rule_Data args) {
    str += args.X;
}

// ^X, prepend character X
void prepend_char(string &str, Rules::Rule_Data args) {
    string s = string(1, args.X) + str;
    str = s;
}

