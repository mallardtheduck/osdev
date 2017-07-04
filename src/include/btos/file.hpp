#ifndef _FILE_HPP
#define _FILE_HPP

#include "handle.hpp"

namespace btos_api{

	class File;

	class FileMapping : public Handle{
	private:
		friend class File;

		bt_handle_t filehandle;
		size_t offset;
		char *addr;
		size_t size;

		FileMapping(bt_handle_t h, size_t o, char *a, size_t s);
	public:
		File GetFile();

		size_t Offset();
		char *Address();
		size_t Size();
	};
	
	class File : public Handle{
	private:
	public:
		File(bt_handle_t h);
		File(const char *path, uint32_t flags);

		size_t Write(size_t bytes, const char *buffer);
		size_t Read(size_t bytes, char *buffer);
		size_t IOCtl(int function, size_t bytes, char *buffer);
		bt_filesize_t Seek(bt_filesize_t bytes, uint32_t flags);
		bt_filesize_t Tell();
		void Flush();

		FileMapping MemMap(size_t offset, char *addr, size_t size);
	};

}

#endif
