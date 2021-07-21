#include "password_node.h"

using namespace std;

Password_Node::Password_Node(string password, size_t n_children) {
    this->password = password;
    this->children.reserve(n_children);
}
