#ifndef _STRUTIL_HPP
#define _STRUTIL_HPP

#include "string.hpp"
#include "ministl.hpp"

string to_upper(const string &str);
bool starts_with(const string &str, const string &cmp);
vector<string> split_string(const string &str, const char c);

#endif
