#ifndef _MM2_HPP
#define _MM2_HPP

#include "kernel.hpp"

const size_t MM2_Page_Size = 4096;
const size_t MM2_Kernel_Boundary=1024*1024*1024;
const uint32_t MM2_Boundary_Page = MM2_Kernel_Boundary / MM2_Page_Size;

namespace MM2_Alloc_Mode{
	const uint32_t
	Kernel      = (1<<0),
	Userlow     = (1<<1),
	Userhigh    = (1<<2),
	NoBacking   = (1<<3),
	Immediate	= (1<<4);
}

void mm2_init(multiboot_info_t *mbt);
void *mm2_virtual_alloc(size_t pages, uint32_t mode = MM2_Alloc_Mode::Kernel);

#endif