#ifndef _KVARS_HPP
#define _KVARS_HPP

#include "string.hpp"

class string;

void init_kvars();
void set_kvar(const string &name, const string &value);
string get_kvar(const string &name);
bool is_kvar_set(const string &name);

#endif