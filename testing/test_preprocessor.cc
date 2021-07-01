#include <gtest/gtest.h>
#include "../src/preprocessing.h"
#include "../src/levenshtein.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<pair<string, int>> answers_to_pair_vec(string);
vector<string> passwords_to_string_vec(string);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PasswordPreprocessorTest, TestSizeTwenty) {
    string filename = "random_password_lists_testing/test_list_20";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 20 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 20 PASSWORD PREPROCESSOR END ==========" << endl;
}

TEST(PasswordPreprocessorTest, TestSizeFive) {
    string filename = "random_password_lists_testing/test_list_5";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 5 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 5 PASSWORD PREPROCESSOR END ==========" << endl;
}

TEST(PasswordPreprocessorTest, TestSizeThree) {
    string filename = "random_password_lists_testing/test_list_3";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 3 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 3 PASSWORD PREPROCESSOR END ==========" << endl;
}

TEST(PasswordPreprocessorTest, TestSizeThirteen) {
    string filename = "random_password_lists_testing/test_list_13";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 13 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 13 PASSWORD PREPROCESSOR END ==========" << endl;
}

TEST(PasswordPreprocessorTest, TestSizeOne) {
    string filename = "random_password_lists_testing/test_list_1";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 1 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 1 PASSWORD PREPROCESSOR END ==========" << endl;
}

TEST(PasswordPreprocessorTest, TestSizeTwentyFive) {
    string filename = "random_password_lists_testing/test_list_25";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 25 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 25 PASSWORD PREPROCESSOR END ==========" << endl;
}

TEST(PasswordPreprocessorTest, TestSizeHundred) {
    string filename = "random_password_lists_testing/test_list_100";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 100 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 100 PASSWORD PREPROCESSOR END ==========" << endl;
}

TEST(PasswordPreprocessorTest, TestSizeTen) {
    string filename = "random_password_lists_testing/test_list_10";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 10 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < v1.size(); i++) {
        cout << "passwords are " << v1[i].first << " and " << v2[i].first << endl;
        cout << "distances are " << v1[i].second << " and " << v2[i].second << endl;
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
    cout << "========== TEST SIZE 10 PASSWORD PREPROCESSOR END ==========" << endl;
}

vector<string> passwords_to_string_vec(string name) {
    ifstream fin(name);
    vector<string> v;
    string line;
    while (getline(fin, line))
        v.push_back(line);
    return v;
}

vector<pair<string, int>> answers_to_pair_vec(string name) {

    vector<pair<string, int>> v;
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
        v.push_back(p);
    }

    fin.close();
    return v;
}


