#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#define RED "\033[1;31m"
#define BLUE "\033[1;36m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

template <typename T>
inline T factorial(T n) {
   return (!n) ? 1 : n * factorial(n - 1); 
}

std::vector<std::string> read_lines_to_vec(std::string);

#endif /* UTILS_H */
