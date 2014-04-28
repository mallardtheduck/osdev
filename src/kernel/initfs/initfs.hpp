#ifndef _INITFS_HPP
#define _INITFS_HPP

#include "../kernel.hpp"

struct initfs_file{
	bool valid;
	char name[255];
	unsigned char *data;
	size_t size;
};

extern initfs_file initfs_data[];

fs_driver initfs_getdriver();

#endif
