/*
 * File contains implementations of imitations of hashcat functions
 */

#include <string>
#include <stdexcept>
#include <iostream>
#include "hashcat_fn.h"
#include "hashcat_fn_data.h"
#include "utils.h"

using namespace std;

// TN, toggle character case at pos N
void Hashcat_Fn::toggle_char(string &s, Hashcat_Fn_Data args) {
    try {
        char c = s.at(args.N);
        if (65 <= c && c <= 90) // Is A-Z
            s.at(args.N) = tolower(c);
        else if (97 <= c && c <= 122) // Is a-z
            s.at(args.N) = toupper(c);
    } catch (const out_of_range &oob) {
        cerr << RED_ERR ", index oob: " << oob.what() << endl;
    }
}

// $X, append character X
void Hashcat_Fn::append_char(string &str, Hashcat_Fn_Data args) {
    str += args.X;
}

// ^X, prepend character X
void Hashcat_Fn::prepend_char(string &str, Hashcat_Fn_Data args) {
    string s = string(1, args.X) + str;
    str = s;
}
