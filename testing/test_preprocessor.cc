#include <gtest/gtest.h>
#include "../src/preprocessing.h"
#include "../src/levenshtein.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<pair<string, int>> answers_to_pair_vec(string);
vector<string> passwords_to_string_vec(string);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PasswordPreprocessorTest, TestSizeTen) {
    string filename = "random_password_lists_testing/test_list_10";
    auto v1 = answers_to_pair_vec(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    for (size_t i = 0; i < v1.size(); i++) {
        ASSERT_TRUE(v1[i].first == v2[i].first);
        ASSERT_TRUE(v1[i].second == v2[i].second);
    }
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


