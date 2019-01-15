#include "include/x86emu.h"
#include "include/btos_x86emu.h"
#include <btos_module.h>
#include <module/io.h>

map_address_fn map_address = NULL;

extern "C" void set_map_callback(map_address_fn fn){
	map_address = fn;
}

template<typename T> static u32 mem_read(u32 addr){
	T val = *(T*)map_address(addr);
	return val;
}

template<typename T> static void mem_write(u32 addr, u32 val){
	T tval = (T)val;
	*(T*)map_address(addr) = tval;
}

extern "C" unsigned btos_x86emu_memio_handler(x86emu_t *emu, u32 addr, u32 *val, unsigned type){
	emu->mem->invalid = 0;

	uint32_t bits = type & 0xFF;
	type &= ~0xFF;

	switch(type){
		
		case X86EMU_MEMIO_X:
		case X86EMU_MEMIO_R:
			switch(bits){
				case X86EMU_MEMIO_8:
					*val = mem_read<u8>(addr);
					break;
				case X86EMU_MEMIO_16:
					*val = mem_read<u16>(addr);
					break;
				case X86EMU_MEMIO_32:
					*val = mem_read<u32>(addr);
					break;
				case X86EMU_MEMIO_8_NOPERM:
					*val = mem_read<u8>(addr);
					break;
			}
			break;

		case X86EMU_MEMIO_W:
			switch(bits){
				case X86EMU_MEMIO_8:
					mem_write<u8>(addr, *val);
					break;
				case X86EMU_MEMIO_16:
					mem_write<u16>(addr, *val);
					break;
				case X86EMU_MEMIO_32:
					mem_write<u32>(addr, *val);
					break;
				case X86EMU_MEMIO_8_NOPERM:
					mem_write<u8>(addr, *val);
					break;
			}
			break;

		case X86EMU_MEMIO_I:
			switch(bits){
				case X86EMU_MEMIO_8:
					*val = inb(addr);
					break;
				case X86EMU_MEMIO_16:
					*val = in16(addr);
					break;
				case X86EMU_MEMIO_32:
					*val = in32(addr);
					break;
			}
			break;

		case X86EMU_MEMIO_O:
			switch(bits){
				case X86EMU_MEMIO_8:
					outb(addr, *val);
					break;
				case X86EMU_MEMIO_16:
					out16(addr, *val);
					break;
				case X86EMU_MEMIO_32:
					out32(addr, *val);
					break;
			}
			break;
	}

	return 0;
}
