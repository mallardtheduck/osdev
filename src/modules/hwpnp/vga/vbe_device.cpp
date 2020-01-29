#include "vbe.hpp"
#include "device.hpp"
#include "modes.hpp"
#include <util/ministl.hpp>
#include <util/holdlock.hpp>

lock vga_device_lock;

static const size_t Page_Size = 4096;

uint32_t vbe_current_mode = 0xF0003;
char *fb = NULL;
size_t fb_sz = 0;
VBE_ModeInfo modeinfo;

extern vga_palette_entry vga_palette[256];

struct vbe_instance{
    size_t pos;
    vga_instance *vga;
};

bool is_vbe_mode(uint32_t mode_id){
	if((mode_id & 0xF0000) == 0xF0000) return false;
	else return true;
}

bt_vidmode make_vidmode_from_id(uint16_t id){
	auto m = (*vbe_modes)[id];
	bt_vidmode mode;
	mode.id = id;
	mode.width = m.XResolution;
	mode.height = m.YResolution;
	mode.bpp = m.BitsPerPixel;
	mode.textmode = (m.MemoryModel == VBE_MemoryModel::Text);
	mode.palette = (m.MemoryModel == VBE_MemoryModel::Packed);
	mode.bytesPerLine = m.BytesPerScanLine;
	mode.rBits = m.RedMaskSize;
	mode.gBits = m.GreenMaskSize;
	mode.bBits = m.BlueMaskSize;
	mode.rPos = m.RedFieldPosition;
	mode.gPos = m.GreenFieldPosition;
	mode.bPos = m.BlueFieldPosition;
	return mode;
}

bt_vidmode make_vidmode_from_index(size_t idx){
	size_t i = 0;
	for(auto m : *vbe_modes){
		if(i == idx){
			return make_vidmode_from_id(m.first);
		}
		++i;
	}
	return {0, 0, 0, 0, false, false, 0, 0, 0, 0, 0, 0, 0};
}

void map_fb(){
	fb_sz = (modeinfo.BytesPerScanLine * modeinfo.YResolution);
	size_t pages = fb_sz / Page_Size;
	if(pages * Page_Size < fb_sz) ++pages;
	fb = (char*)map_physical_pages(modeinfo.PhysBasePtr, pages);
	dbgpf("VGA: Mapped VBE LFB from %x at %p. Size: %i (%i pages).\n", modeinfo.PhysBasePtr, fb, (int)fb_sz, (int)pages);
}

void unmap_fb(){
	if(!fb) return;
	size_t pages = fb_sz / Page_Size;
	if(pages * Page_Size < fb_sz) ++pages;
	free_pages(fb, pages);
	fb = NULL;
	fb_sz = 0;
}

void set_palette(){
	uint32_t *palette = new uint32_t[256];
	for(int i=0; i<256; ++i){
		vga_palette_entry entry=vga_palette[i];
		uint32_t e = (entry.r << 16) | (entry.g << 8) | (entry.b << 0);
		palette[i] = e;
	}
	VBE_SetPalette(palette);
	delete[] palette;
}

bt_video_palette_entry get_palette_entry(uint8_t entry){
    bt_video_palette_entry ret;
    ret.index = entry;
    ret.r = vga_palette[entry].r << 2;
    ret.g = vga_palette[entry].g << 2;
    ret.b = vga_palette[entry].b << 2;
    ret.a=0;
    return ret;
}

void vbe_clear_screen(){
	size_t rowsize = modeinfo.XResolution * (modeinfo.BitsPerPixel / 8);
	for(size_t row = 0; row < modeinfo.YResolution; ++row){
		size_t fb_pos = row * modeinfo.BytesPerScanLine;
		memset(&fb[fb_pos], 0, rowsize);
	}
}

void init_vbe_device(){
	init_lock(&vga_device_lock);
}

