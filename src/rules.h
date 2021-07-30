#ifndef RULES_H
#define RULES_H

#include <vector>
#include <string>
#include <utility>

namespace Rules {

    // Carries data for the concrete construction of a rule
    struct Rule_Data {
        char X;
        unsigned int N;
        unsigned int M;
        // Unused rn
        unsigned int I;
    };

    extern std::vector<std::vector<std::pair<void (*)(std::string&, Rule_Data), Rule_Data>>> concrete_rules;
    void build_concrete_rules(std::vector<std::string>);

    void append_char(std::string&, Rule_Data); // $X
    void prepend_char(std::string&, Rule_Data); // ^X

}

#endif /* RULES_H */
