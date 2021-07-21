#include "password_tree.h"

#include <cmath>
#include "utils.h"

using namespace std;

Password_Tree::Password_Tree(vector<pair<string, int>> passwords, vector<string> rules) {

    this->rules = rules;
    this->goal_pw_count = passwords.size();
    // size_t rule_count = rules.size();

    // Construct root list of goal passwords
    for (auto element : passwords) {
        // Upper limit on rules to attempt determined by earlier calculated lev dist
        auto root_node = Password_Node(element.first, element.second);
        goal_passwords.push_back(root_node);
    }

}

void Password_Tree::build_tree() {

    for (size_t i = 0; i < goal_pw_count; i++) {

    }

}

/* 
 * Calculates number of all subset permutations for a set of n rules and
 * m passwords, equivalent to node count of tree
 */
inline size_t Password_Tree::n_nodes(size_t for_n_rules, size_t m_passwords) {
    return ((!for_n_rules) ? 1 : floor(M_E * factorial(for_n_rules))) * m_passwords;
}

