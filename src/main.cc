#include <iostream>
#include <string>
#include "preprocessing.h"

using namespace std;

int main() {
    vector<string> vec;
    vec.push_back("kitten");
    vec.push_back("sitting");
    Password_Preprocessor processor(vec);
    processor.process();
    return 0;
}
