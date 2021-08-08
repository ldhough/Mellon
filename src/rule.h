#ifndef RULES_H
#define RULES_H

#include <vector>
#include <string>
#include <utility>
#include "hashcat_fn.h"
#include "hashcat_fn_data.h"

/*
 * A hashcat "rule" consists of multiple "primitive" hashcat
 * functions
 *
 * A hashcat rulefile consists of rules separated by newlines
 * where each rule may be made of multiple primitive hc fns
 * separated by whitespace
 *
 * Rule::build_rule attempts to create a rule out of a single
 * line of a rulefile, represented as an std::string
 *
 * A rule is internally represented as a list of pointers to
 * hashcat function imitations, and can be applied by calling
 * Rule::apply_rule
 */

class Rule {
    private:
        Rule();
        std::vector<std::pair<hc_fn_ptr, Hashcat_Fn_Data>> functions;
    public:
        std::string apply_rule(std::string);
        static Rule build_rule(std::string);
};

#endif /* RULES_H */
