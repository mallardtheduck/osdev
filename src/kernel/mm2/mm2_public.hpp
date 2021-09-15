#ifndef _MM2_PUBLIC_HPP
#define _MM2_PUBLIC_HPP

#include "../kernel.hpp"
#include <module/kernelsys/mm2.hpp>

namespace MM2{
	void mm2_liballoc_lock();
	void mm2_liballoc_unlock();
}

#endif
