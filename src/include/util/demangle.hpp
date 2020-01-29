#ifndef _DEMANGLE_HPP
#define _DEMANGLE_HPP

#include <cxxabi.h>
#include <string>
#include <memory>

static __attribute__ ((unused)) std::string demangle(const char* name) {

    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name;
}

#endif