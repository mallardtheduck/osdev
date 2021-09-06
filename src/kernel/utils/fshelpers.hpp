#include "../kernel/kernel.hpp"
namespace FSHelpers{
	inline uint64_t SeekPosition(size_t pos, uint32_t flags, uint64_t cpos, uint64_t size){
		if(flags & FS_Relative){
			if(pos > size - cpos) cpos = size;
			else cpos += pos;
		}
		else if (flags == FS_Backwards){
			if(pos > size) cpos = 0;
			else cpos = size - pos;
		}else if(flags == (FS_Relative | FS_Backwards)){
			if(pos > cpos) cpos = 0;
			else cpos -= pos;
		}else{
			if(pos > size) cpos = size;
			else cpos = pos;
		}
		return cpos;
	}
}