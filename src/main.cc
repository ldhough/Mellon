#include <iostream>
#include <string>
#include "preprocessing.h"
#include "password_tree.h"

using namespace std;

int main() {
    vector<string> vec;
    vec.push_back("");
    vec.push_back("");
    Password_Preprocessor processor(vec);
    auto result = processor.process();
    vector<string> rules;
    rules.push_back("1");
    rules.push_back("2");
    Password_Tree t(result, rules);
    t.build_tree();
    return 0;
}
