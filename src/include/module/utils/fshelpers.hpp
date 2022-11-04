#ifndef MODULE_FSHELPERS_HPP
#define MODULE_FSHELPERS_HPP

namespace FSHelpers{
	inline uint64_t SeekPosition(size_t pos, uint32_t flags, uint64_t cpos, uint64_t size){
		if(flags == FS_Relative){
			if(pos > size - cpos) cpos = size;
			else cpos += pos;
		}else if (flags == FS_Backwards){
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

	template<typename T> uint64_t SeekIterator(size_t pos, uint32_t flags, T &it, T begin, T end){
		size_t cpos = 0;
		for(auto i = begin; i != end && i != it; ++i, ++cpos);
		size_t size = 0;
		for(auto i = begin; i != end; ++i, ++size);
		auto newPos = SeekPosition(pos, flags, cpos, size);
		it = begin;
		for(uint64_t p = 0; it != end && p < newPos; ++it, ++p);
		return newPos;
	}
}

#endif