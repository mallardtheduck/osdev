#include "../kernel.hpp"
#include "mm2_internal.hpp"

namespace MM2{
	uint64_t mm2_mmap(char *ptr, file_handle &file, size_t offset, size_t size){
		fs_seek(file, offset, FS_Set);
		fs_read(file, size, ptr);
		return 0;
	}
	
	void mm2_flush(file_handle &file){
		//panic("(MM2) Memory-mapped files not implmented!");
		(void)file;
	}
	
	void mm2_close(file_handle &file){
		//panic("(MM2) Memory-mapped files not implmented!");
		(void)file;
	}
	
	void mm2_closemap(uint64_t id){
		//panic("(MM2) Memory-mapped files not implmented!");
		(void)id;
	}
}