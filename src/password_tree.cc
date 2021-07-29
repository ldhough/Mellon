#include "password_tree.h"
#include <cmath>
#include "utils.h"

using namespace std;

Password_Tree::Password_Tree(vector<pair<string, int>> passwords, vector<string> rules) {

    this->rules = rules;
    this->rule_count = rules.size();
    this->goal_pw_count = passwords.size();
    // size_t rule_count = rules.size();

    // Construct root list of goal passwords
    for (auto element : passwords) {
        // Upper limit on rules to attempt determined by earlier calculated lev dist
        Password_Node *p_root_node = new Password_Node(element.first, element.second);
        goal_passwords.push_back(p_root_node);
    }

}

void Password_Tree::generate_children(Password_Node *node, vector<bool> rules_subset, size_t child_count) {
    
    if(!child_count)
        return;

    for (size_t i = 0; i < this->rule_count; i++) {
        if (rules_subset[i]) {
            const size_t new_child_count = child_count-1;
            auto new_rules_subset = rules_subset;
            new_rules_subset[i] = false;
            // TODO: THIS LOGIC
            //string new_pw = this->apply_rule(this->rules[i], node->password);
            //if this->matches_goal(new_pw)
            Password_Node *p_node = new Password_Node(node->password+"a", new_child_count);
            p_node->parents.push_back(node);
            node->children.push_back(p_node);
            generate_children(p_node, new_rules_subset, new_child_count);
            
        }
    
    }
}

void Password_Tree::build_tree() {

    for (size_t i = 0; i < goal_pw_count; i++) {
        auto root_node = goal_passwords[i];
        vector<bool> rules_subset(this->rule_count, true);
        this->generate_children(root_node, rules_subset, this->rule_count);
    }

}

/* 
 * Calculates number of all subset permutations for a set of n rules and
 * m passwords, equivalent to node count of tree
 */
inline size_t Password_Tree::n_nodes(size_t for_n_rules, size_t m_passwords) {
    return ((!for_n_rules) ? 1 : floor(M_E * factorial(for_n_rules))) * m_passwords;
}

