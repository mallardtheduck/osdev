#ifndef _SHM_HPP
#define _SHM_HPP

#include <btos.h>
#include "handle.hpp"

namespace btos_api{

	class SHMMapping : public Handle{
	private:
		friend class SHMSpace;

		uint64_t id;
		void *addr;
		uint32_t offset;
		size_t pages;
		uint32_t flags;

		SHMMapping(bt_handle_t h, uint64_t id, void *addr, uint32_t offset, size_t pages, uint32_t flags);
	public:
		SHMMapping(uint64_t id, void *addr, uint32_t offset, size_t pages, uint32_t flags);

		uint64_t ID();
		void *Address();
		uint32_t Offset();
		size_t Pages();
		size_t Size();
		uint32_t Flags();
	};

	class SHMSpace : public Handle{
	private:
	public:
		SHMSpace(uint32_t flags);
		uint64_t ID();

		SHMMapping Map(void *addr, uint32_t offset, size_t pages, uint32_t flags);
	};

}

#endif
