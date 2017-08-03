#ifndef _SWITCHER_HPP
#define _SWITCHER_HPP

#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char delim);

struct term{
    uint64_t id;
    std::string title;
};

std::vector<term> get_term_list();

#endif
