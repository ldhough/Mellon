#ifndef PASSWORD_TREE_H
#define PASSWORD_TREE_H

#define _USE_MATH_DEFINES

#include "password_tree.h"
#include "password_node.h"
#include <string>
#include <vector>

class Password_Tree {
    public:
        std::vector<Password_Node*> goal_passwords;
        void build_tree(void);
        Password_Tree(std::vector<std::pair<std::string, int>>, std::vector<std::string>); 
    private:
        size_t n_nodes(size_t, size_t);
        //set of goal pw
        
        //set of all pw


        size_t goal_pw_count;
        std::vector<std::string> rules;
        size_t rule_count;
        void generate_children(Password_Node*, std::vector<bool>, size_t);
};

#endif /* PASSWORD_TREE_H */

