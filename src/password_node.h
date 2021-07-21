#ifndef PASSWORD_NODE_H
#define PASSWORD_NODE_H

#include <string>
#include <vector>

class Password_Node {
    public:
        std::string password;

        // If empty str, can assume is root/goal
        std::string transformation = "";

        // "hashcat distance" of this password from root, 0 is root
        size_t distance = 0;

        // Upper limit on upper number of hashcat rules to attempt
        size_t rule_limit;
        std::vector<Password_Node> parents;
        std::vector<Password_Node> children;

        Password_Node(std::string, size_t);
};

#endif /* PASSWORD_NODE_H */

