#include "libx86emu/include/x86emu.h"
#include "libx86emu/include/btos_x86emu.h"
#include <module/io.h>
#include <util/ministl.hpp>

static map<uint32_t, void*> *page_mappings;
static map<uint32_t, void*> *mapping_cache;

static const uint32_t Page_Address_Mask = 0xFFFFF000;

static const uint16_t VBE_Fn_GetInfo = 0x4F00;
static const uint16_t VBE_Fn_GetModeInfo = 0x4F01;

template <typename T> static T *RealPtr(uint16_t ptr[2]){
	return (T*)((ptr[1] * 0x10) + ptr[0]);
}

struct VBE_Info {
	char Signature[4];
	uint16_t Version;
	uint16_t OemStringPtr[2];
	uint32_t Capabilities;
	uint16_t VideoModePtr[2];
	uint16_t TotalMemory;
	uint32_t OemSoftwareRev;
	uint16_t OemVendorNamePtr[2];
	uint16_t OemProductNamePtr[2];
	uint16_t OemProductRevPtr[2];
} __attribute__((packed));

struct VBE_ModeInfo {
	uint16_t attributes;
	uint8_t winA,winB;
	uint16_t granularity;
	uint16_t winsize;
	uint16_t segmentA, segmentB;
	uint16_t realFctPtr[2];
	uint16_t pitch;

	uint16_t Xres, Yres;
	uint8_t Wchar, Ychar, planes, bpp, banks;
	uint8_t memory_model, bank_size, image_pages;
	uint8_t reserved0;

	uint8_t red_mask, red_position;
	uint8_t green_mask, green_position;
	uint8_t blue_mask, blue_position;
	uint8_t rsv_mask, rsv_position;
	uint8_t directcolor_attributes;

	uint32_t physbase; 
	uint32_t reserved1;
	uint16_t reserved2;
} __attribute__((packed));

static map<uint16_t, VBE_ModeInfo> *vbe_modes;

static void flush_log(x86emu_t *emu, char *buf, unsigned size){
	dbgpf("VGA: x86emu %x:%x ", emu->x86.R_CS, emu->x86.R_IP);
	dbgout(buf);
}

void call_int10h(uint16_t ax, uint16_t bx, uint16_t cx, uint16_t es, uint16_t di){
	page_mappings = new map<uint32_t, void*>();
	mapping_cache = new map<uint32_t, void*>();
	x86emu_t* emu = x86emu_new(X86EMU_PERM_RWX, X86EMU_PERM_RWX);
	x86emu_set_memio_handler(emu, &btos_x86emu_memio_handler);
	x86emu_set_log(emu, 128, &flush_log);
	emu->log.trace = X86EMU_TRACE_DEFAULT;

	x86emu_set_seg_register(emu, emu->x86.R_CS_SEL, 0);
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
	for(auto m : *page_mappings){
		free_pages(m.second, 1);
	}
	delete page_mappings;
	delete mapping_cache;
}

VBE_Info VBE_GetInfo(){
	VBE_Info *info = (VBE_Info*)0x20000;
	memset(info, 0, 512);
	memcpy(info->Signature, "VBE2", 4);
	call_int10h(VBE_Fn_GetInfo, 0, 0, 0x2000, 0);
	return *info;
}

VBE_ModeInfo VBE_GetModeInfo(uint16_t mode){
	VBE_ModeInfo *info = (VBE_ModeInfo*)0x30000;
	memset(info, 0, 256);
	call_int10h(VBE_Fn_GetModeInfo, 0, mode, 0x3000, 0);
	return *info;
}

void vbe_test(){
	//call_int10h(0x4F02, 0x117, 0, 0);
	VBE_Info info = VBE_GetInfo();
	dbgpf("VGA: VBE signature: %c%c%c%c\n", info.Signature[0], info.Signature[1], info.Signature[2], info.Signature[3]);
	dbgpf("VGA: VBE version: %x\n", info.Version);
	dbgpf("VGA: VBE memory: %iKB\n", info.TotalMemory * 64 * 1024);
	dbgpf("VGA: VBE OEM String: %s\n", RealPtr<char>(info.OemStringPtr));
	dbgpf("VGA: VBE OEM Vendor name: %s\n", RealPtr<char>(info.OemVendorNamePtr));
	dbgpf("VGA: VBE OEM Product name: %s\n", RealPtr<char>(info.OemVendorNamePtr));
	dbgpf("VGA: VBE OEM Product revision: %s\n", RealPtr<char>(info.OemProductRevPtr));
	vector<uint16_t> modes;
	uint16_t *modeptr = RealPtr<uint16_t>(info.VideoModePtr);
	for(size_t i = 0; modeptr[i] != 0xFFFF; ++i){
		vbe_modes = new map<uint16_t, VBE_ModeInfo>();
		VBE_ModeInfo modeinfo = VBE_GetModeInfo(modeptr[i]);
		(*vbe_modes)[modeptr[i]] = modeinfo;
		dbgpf("VGA: VBE Mode: %x\n", modeptr[i]);
		dbgpf("  %i x %i %ibpp\n", modeinfo.Xres, modeinfo.Yres, modeinfo.bpp);
		dbgpf("  Attributes: %x\n", modeinfo.attributes);
		dbgpf("  Memory model: %x\n", modeinfo.memory_model);
	}
	while(true) disable_interrupts();
}

void *map_address(uint32_t addr){
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

void vbe_init(){
	set_map_callback(&map_address);
	vbe_test();
}
