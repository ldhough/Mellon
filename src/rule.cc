#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <map>
#include <utility>
#include <vector>
#include <sstream>
#include <set>
#include "hashcat_fn.h"
#include "hashcat_fn_data.h"
#include "rule.h"
#include "utils.h"

#define DEBUG 0

using namespace std;

inline pair<hc_fn_ptr, Hashcat_Fn_Data> get_len_1_fn(const string&);
inline pair<hc_fn_ptr, Hashcat_Fn_Data> get_len_2_fn(const string&);

// Maps hashcat "primitive" funcs/rules signifiers to pointers to imitating functions
const map<char, hc_fn_ptr> hc_fn_primitives = 
    {
        {'$', &Hashcat_Fn::append_char},
        {'^', &Hashcat_Fn::prepend_char}
    };

const set<char> set_N = {'T', 'P', 'D', '\'', 'z', 'Z'};
const set<char> set_X = {'$', '^', '@'};

Rule::Rule() {}

Rule Rule::build_rule(string rule_str) {

    Rule rule;

    stringstream ss(rule_str);
    string fn_str;

    while (ss >> fn_str) {

        size_t fn_str_size = fn_str.size();

        if (fn_str_size > 3) {
            string err_str = RED_ERR;
            err_str += ": Rule could not be constructed, ";
            err_str += fn_str + " is not a valid function!";
            throw logic_error(err_str);
        }

        pair<hc_fn_ptr, Hashcat_Fn_Data> fn_pair;

        switch (fn_str_size) {
            case 1:
                fn_pair = get_len_1_fn(fn_str);
                break;
            case 2:
                fn_pair = get_len_2_fn(fn_str);
                break;
            case 3:
                break;
        }

        rule.functions.push_back(fn_pair);

    }

    return rule;

}

string Rule::apply_rule(string to_str) {
    for (auto fn_data_pair : this->functions) {
        auto fn = fn_data_pair.first;
        auto data = fn_data_pair.second;
        fn(to_str, data);
    }
    return to_str;
}

inline pair<hc_fn_ptr, Hashcat_Fn_Data> get_len_1_fn(const string &from_fn_str) {
    //char c = rule[0];
    //char c2 = rule[1];
    Hashcat_Fn_Data fnd;
    return {0, fnd};
}

inline pair<hc_fn_ptr, Hashcat_Fn_Data> get_len_2_fn(const string &from_fn_str) {

    char c = from_fn_str[0];
    char c2 = from_fn_str[1];
    Hashcat_Fn_Data fnd;

    // Char 1 in rule should be a number
    if ((set_N.find(c) != set_N.end()) && isdigit(c2))
        fnd.N = (unsigned int) c2;
    // Char 1 in rule should be a letter
    else if (set_X.find(c) != set_X.end())
        fnd.X = c2;
    // Is not a valid rule expressed by two characters
    else {
        string err_str = RED_ERR;
        err_str += ": Rule could not be constructed, ";
        err_str += from_fn_str + " is not a valid function!";
        throw logic_error(err_str);
    }

    return {hc_fn_primitives.at(c), fnd};
}



