#ifndef _INFOFS_HPP
#define _INFOFS_HPP

typedef char* (*info_function)();
void infofs_init();
void infofs_register(char *name, info_function fn);

#endif