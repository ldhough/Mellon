#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>

using namespace std;

inline void cap_char(string &s, size_t at) {
    try {
        s.at(at) = toupper(s.at(at));
    } catch (const out_of_range &oob) {
        cout << "Index oob: " << oob.what() << endl;
    }
}

inline void low_char(string &s, size_t at) {
    try {
        s.at(at) = tolower(s.at(at));
    } catch (const out_of_range &oob) {
        cout << "Index oob: " << oob.what() << endl;
    }
}

inline void toggle_char(string &s, size_t at) {
    try {
        char c = s.at(at);
        if (65 <= c && c <= 90) // Is A-Z
            s.at(at) = tolower(c);
        else if (97 <= c && c <= 122) // Is a-z
            s.at(at) = toupper(c);
    } catch (const out_of_range &oob) {
        cerr << "Index oob: " << oob.what() << endl;
    }
}

void append_char(string &str, char c) {
    str += c;
}

void append_chars(string &str, string chars) {
    str += chars;
}

void capitalize(string &str) {
    cap_char(str, 0);
    for (size_t i = 1; i < str.size()-1; i++)
        low_char(str, i);
}

void delete_range_from_end(string &str) {

}
