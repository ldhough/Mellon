#include <gtest/gtest.h>
#include "../src/preprocessing.h"
#include "../src/levenshtein.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#define DEBUG 0

using namespace std;

map<string, int> answers_to_map(string);
vector<string> passwords_to_string_vec(string);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void debug_print_pass_dist(string p, int d) {
    #if DEBUG
    cout << "Pass is: " << p << endl << "Dist is: " << d << endl;
    #endif
}

void debug_print(string s) {
    #if DEBUG
    cout << s << endl;
    #endif
}

TEST(PasswordPreprocessorTest, TestSizeFive) {
    string filename = "random_password_lists_testing/test_list_5";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 5 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 5 PASSWORD PREPROCESSOR END ==========");
}

TEST(PasswordPreprocessorTest, TestSizeThree) {
    string filename = "random_password_lists_testing/test_list_3";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 3 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 3 PASSWORD PREPROCESSOR END ==========");
}

TEST(PasswordPreprocessorTest, TestSizeTwentyFive) {
    string filename = "random_password_lists_testing/test_list_25";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 25 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 25 PASSWORD PREPROCESSOR END ==========");
}

TEST(PasswordPreprocessorTest, TestSizeTwenty) {
    string filename = "random_password_lists_testing/test_list_20";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 20 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 20 PASSWORD PREPROCESSOR END ==========");
}

TEST(PasswordPreprocessorTest, TestSizeOne) {
    string filename = "random_password_lists_testing/test_list_1";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 1 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 1 PASSWORD PREPROCESSOR END ==========");
}

TEST(PasswordPreprocessorTest, TestSizeThirteen) {
    string filename = "random_password_lists_testing/test_list_13";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 13 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 13 PASSWORD PREPROCESSOR END ==========");
}


TEST(PasswordPreprocessorTest, TestSizeHundred) {
    string filename = "random_password_lists_testing/test_list_100";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 100 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 100 PASSWORD PREPROCESSOR END ==========");
}



TEST(PasswordPreprocessorTest, TestSizeTen) {
    string filename = "random_password_lists_testing/test_list_10";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    debug_print("========== TEST SIZE 10 PASSWORD PREPROCESSOR ==========");
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        auto dist = v2[i].second;
        debug_print_pass_dist(pass, dist);
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
    }
    debug_print("========== TEST SIZE 10 PASSWORD PREPROCESSOR END ==========");
}

vector<string> passwords_to_string_vec(string name) {
    ifstream fin(name);
    vector<string> v;
    string line;
    while (getline(fin, line))
        v.push_back(line);
    return v;
}

map<string, int> answers_to_map(string name) {

    map<string, int> m;
    ifstream fin(name);
    string line;

    while (getline(fin, line)) {
        istringstream to_split(line);
        pair<string, int> p;
        int i = 0;
        string segment;
        while (getline(to_split, segment, ',')) {
            if (0 == i++)
                p.first = segment;
            else
                p.second = atoi(segment.c_str());
        }
        m.insert_or_assign(p.first, p.second);
    }

    fin.close();
    return m;
}


