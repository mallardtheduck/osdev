#include "libx86emu/include/x86emu.h"
#include "libx86emu/include/btos_x86emu.h"
#include "vbe.hpp"
#include "vbe_device.hpp"
#include <module/io.h>
#include <util/ministl.hpp>

static map<uint32_t, void*> *page_mappings;
static map<uint32_t, void*> *mapping_cache;

static const uint32_t Page_Address_Mask = 0xFFFFF000;

namespace VBE_Fn{
	static const uint16_t GetInfo = 0x4F00;
	static const uint16_t GetModeInfo = 0x4F01;
}

template <typename T> static T *RealPtr(Real_Pointer ptr){
	return (T*)((ptr[1] * 0x10) + ptr[0]);
}

map<uint16_t, VBE_ModeInfo> *vbe_modes;

static void flush_log(x86emu_t *emu, char *buf, unsigned size){
	dbgpf("VGA: x86emu %x:%x ", emu->x86.R_CS, emu->x86.R_IP);
	dbgout(buf);
}

static void call_int10h(uint16_t ax, uint16_t bx, uint16_t cx, uint16_t dx, uint16_t es, uint16_t di){
	page_mappings = new map<uint32_t, void*>();
	mapping_cache = new map<uint32_t, void*>();
	x86emu_t* emu = x86emu_new(X86EMU_PERM_RWX, X86EMU_PERM_RWX);
	x86emu_set_memio_handler(emu, &btos_x86emu_memio_handler);
	x86emu_set_log(emu, 128, &flush_log);
	emu->log.trace = X86EMU_TRACE_DEFAULT;

	x86emu_set_seg_register(emu, emu->x86.R_CS_SEL, 0);
	x86emu_set_seg_register(emu, emu->x86.R_SS_SEL, 0x8000);
	x86emu_set_seg_register(emu, emu->x86.R_ES_SEL, es);
	
	emu->x86.R_IP = 0x7C00;
	*(uint8_t*)0x7C00 = 0x90;
	*(uint8_t*)0x7C01 = 0xF4;
	
	emu->x86.R_AX = ax;
	emu->x86.R_BX = bx;
	emu->x86.R_CX = cx;
	emu->x86.R_DI = di;
	x86emu_intr_raise(emu, 0x10, INTR_TYPE_SOFT, 0);

	x86emu_run(emu, X86EMU_RUN_LOOP);
	dbgpf("VGA: INT 10h return AX: %x\n", emu->x86.R_AX);
	x86emu_done(emu);
	for(auto m : *page_mappings){
		free_pages(m.second, 1);
	}
	delete page_mappings;
	delete mapping_cache;
}

void VBE_ResetToVGA(){
	call_int10h(0x03, 0, 0, 0, 0, 0);
}

VBE_Info VBE_GetInfo(){
	VBE_Info *info = (VBE_Info*)0x20000;
	memset(info, 0, 512);
	memcpy(info->Signature, "VBE2", 4);
	call_int10h(VBE_Fn::GetInfo, 0, 0, 0, 0x2000, 0);
	return *info;
}

VBE_ModeInfo VBE_GetModeInfo(uint16_t mode){
	VBE_ModeInfo *info = (VBE_ModeInfo*)0x30000;
	memset(info, 0, 256);
	call_int10h(VBE_Fn::GetModeInfo, 0, mode, 0, 0x3000, 0);
	return *info;
}

void VBE_SetMode(uint16_t modeId, bool linear){
	if(linear) modeId |= (1 << 14);
	modeId |= (1 << 15);
	call_int10h(0x4F02, modeId, 0, 0, 0, 0);
}

bt_video_palette_entry VBE_GetPaletteEntry(uint8_t index){
	uint32_t *entry = (uint32_t*)0x40000;
	*entry = 0;
	call_int10h(0x4F09, 1, 1, index, 0x4000, 0);
	dbgpf("VGA: VBE Palette entry %i: %x\n", index, *entry); 
	bt_video_palette_entry ret;
	ret.index = index;
	ret.r = (*entry & 0xFF0000) >> 14;
	ret.g = (*entry & 0xFF00) >> 6;
	ret.b = (*entry & 0xFF);
	ret.a = 0;
	return ret;
}

void VBE_SetPalette(void *address){
	void *rm_address = (void*)0x40000;
	memcpy(rm_address, address, 1024);
	call_int10h(0x4F09, 0, 256, 0, 0x4000, 0);
}

static bool is_mode_supported(const VBE_ModeInfo &mode){
	//Modes not supported by the hardware cannot be used
	if(!(mode.ModeAttributes & VBE_Attribute::Supported)) return false;
	//VGA modes supported via ordinary VGA driver code
	if(!(mode.ModeAttributes & VBE_Attribute::NonVGA)){
		if(mode.XResolution == 320 && mode.YResolution == 240) return false;
		if(mode.MemoryModel == VBE_MemoryModel::Text&& mode.XResolution == 80 && mode.YResolution == 25) return false;
	}
	//Don't support monochrome modes (really only applies to text)
	if(!(mode.ModeAttributes & VBE_Attribute::Colour)) return false;
	//Support only 4bpp text modes and 8, 16, 24 and 32bpp graphics modes
	if(!(mode.ModeAttributes & VBE_Attribute::Graphics) && mode.MemoryModel == VBE_MemoryModel::Text){
		if(mode.BitsPerPixel != 4) return false;
		//Disable text modes for now 
		return false;
	}else if(mode.BitsPerPixel != 8 && mode.BitsPerPixel != 16 && mode.BitsPerPixel != 24 && mode.BitsPerPixel != 32){
		return false;
	}
	//Only support linear framebuffers for non text modes
	if(!(mode.ModeAttributes & VBE_Attribute::LinearMode) && mode.MemoryModel != VBE_MemoryModel::Text) return false;
	//If mode is not text, confirm we have a framebuffer address
	if(mode.MemoryModel != VBE_MemoryModel::Text && !mode.PhysBasePtr) return false;
	//Only support Text, Packed (8bpp) and DirectColour memory models
	if(mode.MemoryModel != VBE_MemoryModel::Text && mode.MemoryModel != VBE_MemoryModel::Packed && mode.MemoryModel != VBE_MemoryModel::DirectColour) return false;
	return true;
}

static void dbgoutmode(uint16_t id, const VBE_ModeInfo &modeinfo){
	dbgpf("VGA: VBE Mode: %x\n", id);
	dbgpf("  %i x %i %ibpp\n", modeinfo.XResolution, modeinfo.YResolution, modeinfo.BitsPerPixel);
	dbgpf("  Attributes: %x\n", modeinfo.ModeAttributes);
	char *memoryModelName = "Unknown";
	switch(modeinfo.MemoryModel){
		case VBE_MemoryModel::Text:
			memoryModelName = "Text";
			break;
		case VBE_MemoryModel::CGA:
			memoryModelName = "CGA";
			break;
		case VBE_MemoryModel::Hercules:
			memoryModelName = "Hercules";
			break;
		case VBE_MemoryModel::Planar:
			memoryModelName = "Planar";
			break;
		case VBE_MemoryModel::Packed:
			memoryModelName = "Packed";
			break;
		case VBE_MemoryModel::NonChain:
			memoryModelName = "NonChain";
			break;
		case VBE_MemoryModel::DirectColour:
			memoryModelName = "DirectColour";
			break;
		case VBE_MemoryModel::YUV:
			memoryModelName = "YUV";
			break;
	}
	dbgpf("  Memory model: %s\n", memoryModelName);
	if(modeinfo.MemoryModel == VBE_MemoryModel::Text){
		dbgpf("  Chracter size: %i x %i\n", modeinfo.XCharSize, modeinfo.YCharSize);
	}
}

static void vbe_configure(){
	VBE_Info info = VBE_GetInfo();
	dbgpf("VGA: VBE signature: %c%c%c%c\n", info.Signature[0], info.Signature[1], info.Signature[2], info.Signature[3]);
	dbgpf("VGA: VBE version: %x\n", info.Version);
	dbgpf("VGA: VBE memory: %iKB\n", info.TotalMemory * 64 * 1024);
	dbgpf("VGA: VBE OEM String: %s\n", RealPtr<char>(info.OemStringPtr));
	dbgpf("VGA: VBE OEM Vendor name: %s\n", RealPtr<char>(info.OemVendorNamePtr));
	dbgpf("VGA: VBE OEM Product name: %s\n", RealPtr<char>(info.OemVendorNamePtr));
	dbgpf("VGA: VBE OEM Product revision: %s\n", RealPtr<char>(info.OemProductRevPtr));
	uint16_t *modeptr = RealPtr<uint16_t>(info.VideoModePtr);
	vbe_modes = new map<uint16_t, VBE_ModeInfo>();
	for(size_t i = 0; modeptr[i] != 0xFFFF; ++i){
		VBE_ModeInfo modeinfo = VBE_GetModeInfo(modeptr[i]);
		dbgoutmode(modeptr[i], modeinfo);
		if(is_mode_supported(modeinfo)) {
			dbgout("  Mode IS supported.\n");
			(*vbe_modes)[modeptr[i]] = modeinfo;
		}else{
			dbgout("  Mode IS NOT supported.\n");
		}
	}
	dbgout("VGA: Supported VBE modes:\n");
	for(auto m : *vbe_modes){
		dbgoutmode(m.first, m.second);
	}
}

static void *map_address(uint32_t addr){
	uint32_t page_addr = addr & Page_Address_Mask;
	uint32_t page_offset = addr - page_addr;
	//dbgpf("VGA: Mapping address %x (page %x offset %x).\n", addr, page_addr, page_offset);
	
	if(mapping_cache->has_key(page_addr)){
		void *vaddr = (*mapping_cache)[page_addr];
		void *ret = (void*)((uint32_t)vaddr + page_offset);
		//dbgpf("VGA: Mapping cached. Returning %p.\n", ret);
		return ret;
	 }
	
	if(addr >= 4096 && physaddr((void*)page_addr) == page_addr){
		(*mapping_cache)[page_addr] = (void*)page_addr;
		//dbgpf("VGA: Identity mapping. Returning %x.\n", addr);
		return (void*)addr;
	}

	void *vaddr = NULL;
	if(page_mappings->has_key(page_addr)){
		//dbgout("VGA: Previously mapped I/O page. Should not see this!\n");
		vaddr = (*page_mappings)[page_addr];
	}else{
		//dbgpf("VGA: Creating mapping for physical page %x.\n", page_addr);
		vaddr = map_physical_pages(page_addr, 1);
		(*page_mappings)[page_addr] = vaddr;
		(*mapping_cache)[page_addr] = vaddr;
	}
	return (void*)((uint32_t)vaddr + page_offset);
}

static bool verify_vesa_signature(const char sig[4]){
	return sig[0] == 'V' && sig[1] == 'E' && sig[2] == 'S' && sig[3] == 'A';
}

static bool is_vbe_usable(){
	bool ret = false;
	Real_Pointer *page_zero = (Real_Pointer*)map_physical_pages(0, 1);
	Real_Pointer &int10hvec = page_zero[0x10];
	uint32_t int10hlin = (uint32_t)RealPtr<void>(int10hvec);
	free_pages(page_zero, 1);
	dbgpf("VGA: Int 10h vector: %x\n", int10hlin);
	if(int10hlin > 0xC0000 && int10hlin < 0xD0000){
		VBE_Info info = VBE_GetInfo();
		if(verify_vesa_signature(info.Signature)){
			if(RealPtr<uint16_t>(info.VideoModePtr) < (uint16_t*)0xA0000){
				if(*RealPtr<uint16_t>(info.VideoModePtr) != 0xFFFF){
					dbgout("VGA: Tests passed. VBE is usable.\n");
					ret = true;
				}else{
					dbgout("VGA: VBE reports no video modes available. VBE unusable.\n");
				}
			}else{
				dbgout("VGA: VBE_Info mode list pointer not valid. VBE unusable.\n");
			}
		}else{
			dbgout("VGA: VBE_Info does not have required signature. VBE unusable.\n");
		}
	}else{
		dbgout("VGA: Int 10h vector is not in VGA BIOS range. VBE unusable.\n");
	}
	return ret;
}

bool vbe_init(){
	set_map_callback(&map_address);
	bool vbeok = is_vbe_usable();
	if(vbeok){
		vbe_configure();
		init_vbe_device();
	}	
	return vbeok;
}
