#include <gtest/gtest.h>
#include "../src/preprocessing.h"
#include "../src/levenshtein.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

map<string, int> answers_to_map(string);
vector<string> passwords_to_string_vec(string);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



TEST(PasswordPreprocessorTest, TestSizeTen) {
    string filename = "random_password_lists_testing/test_list_10";
    auto m = answers_to_map(filename + "_min_levs.csv");
    auto passwords = passwords_to_string_vec(filename + ".txt");
    Password_Preprocessor p(passwords);
    auto v2 = p.process();
    cout << "========== TEST SIZE 10 PASSWORD PREPROCESSOR ==========" << endl;
    for (size_t i = 0; i < passwords.size()-1; i++) { //-1 because last password with INT_MAX dist isn't included
        auto pass = v2[i].first;
        cout << "Pass is: " << pass << endl;
        auto dist = v2[i].second;
        cout << "Dist is: " << dist << endl;
        ASSERT_TRUE(m.contains(pass));
        ASSERT_TRUE(m[pass] == dist);
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

//vector<pair<string, int>> answers_to_pair_vec(string name) {
map<string, int> answers_to_map(string name) {

    // vector<pair<string, int>> v;
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
        //v.push_back(p);
        m.insert_or_assign(p.first, p.second);
    }

    fin.close();
    return m;
}


