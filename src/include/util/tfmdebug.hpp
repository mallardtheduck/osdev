#ifndef UTIL_TFMDEBUG_HPP
#define UTIL_TFMDEBUG_HPP

#include "tinyformat.hpp"
#include <btos.h>

template<typename ...T> inline void tfmdebug(const char *f, T...ts){
	auto str = tfm::format(f, ts...);
	btos_api::bt_zero(str.c_str());
}

#endif