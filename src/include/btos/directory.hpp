#ifndef _DIRECTORY_HPP
#define _DIRECTORY_HPP

#include "handle.hpp"

namespace btos_api{
	
	class Directory : public Handle{
	private:
	public:
		Directory(const char *path, uint32_t flags);

		bool Write(const bt_directory_entry &entry);
		bt_directory_entry Read() const;
		size_t Seek(size_t bytes, uint32_t flags);
		size_t Tell() const;

		class iterator{
		private:
			friend class Directory;
			Directory *dir;
			bt_directory_entry ent;
		public:
			void operator++();
			bt_directory_entry operator*();

			bool operator==(const iterator &i);
			bool operator!=(const iterator &i);
		};

		iterator begin();
		iterator end();
	};

}

#endif
