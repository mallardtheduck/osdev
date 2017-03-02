#include "vbe.hpp"
#include "device.hpp"
#include <util/ministl.hpp>
#include <util/holdlock.hpp>

extern lock vga_device_lock;

static const size_t Page_Size = 4096;

static uint32_t current_mode = 0xF0003;
static char *fb = NULL;
static size_t fb_sz = 0;
static VBE_ModeInfo modeinfo;

struct vbe_instance{
    size_t pos;
    vga_instance *vga;
};

static bool is_vbe_mode(uint32_t mode_id = current_mode){
	if((mode_id & 0xF0000) == 0xF0000) return false;
	else return true;
}

static bt_vidmode make_vidmode_from_id(uint16_t id){
	auto m = (*vbe_modes)[id];
	bt_vidmode mode;
	mode.id = id;
	mode.width = m.XResolution;
	mode.height = m.YResolution;
	mode.bpp = m.BitsPerPixel;
	mode.textmode = (m.MemoryModel == VBE_MemoryModel::Text);
	mode.palette = (m.MemoryModel == VBE_MemoryModel::Packed);
	return mode;
}

static bt_vidmode make_vidmode_from_index(size_t idx){
	size_t i = 0;
	for(auto m : *vbe_modes){
		if(i == idx){
			return make_vidmode_from_id(m.first);
		}
		++i;
	}
	return {0, 0, 0, 0, false, false};
}

static void map_fb(){
	fb_sz = (modeinfo.BytesPerScanLine * modeinfo.YResolution);
	size_t pages = fb_sz / Page_Size;
	if(pages * Page_Size < fb_sz) ++pages;
	fb = (char*)map_physical_pages(modeinfo.PhysBasePtr, pages);
	dbgpf("VGA: Mapped VBE LFB from %x at %p. Size: %i (%i pages).\n", modeinfo.PhysBasePtr, fb, (int)fb_sz, (int)pages);
}

static void unmap_fb(){
	if(!fb) return;
	size_t pages = fb_sz / Page_Size;
	if(pages * Page_Size < fb_sz) ++pages;
	free_pages(fb, pages);
	fb = NULL;
	fb_sz = 0;
}

void *vbe_open(void *id){
	vbe_instance *inst = new vbe_instance();
	inst->vga = (vga_instance*)vga_device.open(id);
	inst->pos = 0;
	return inst;
}

bool vbe_close(void *instance){
	vbe_instance *inst=(vbe_instance*)instance;
	if(inst){
		vga_device.close(inst->vga);
		delete inst;
		return true;
	}else return false;
}

size_t vbe_read(void *instance, size_t bytes, char *buf){
	hold_lock hl(&vga_device_lock);
	vbe_instance *inst=(vbe_instance*)instance;
	if(is_vbe_mode()){
		if(inst->pos + bytes > fb_sz) bytes = (fb_sz - inst->pos);
		//dbgpf("VGA: VBE Reading %i bytes from %i (Addr: %p).\n", (int)bytes, (int)inst->pos, &fb[inst->pos]);
		memcpy(buf, &fb[inst->pos], bytes);
		inst->pos += bytes;
		return bytes;
	}else{
		return vga_device.read(inst->vga, bytes, buf);
	}	
}

size_t vbe_write(void *instance, size_t bytes, char *buf){
	hold_lock hl(&vga_device_lock);
	vbe_instance *inst=(vbe_instance*)instance;
	if(is_vbe_mode()){
		if(inst->pos + bytes > fb_sz) bytes = (fb_sz - inst->pos);
		//dbgpf("VGA: VBE Writing %i bytes to %i (Addr: %p).\n", (int)bytes, (int)inst->pos, &fb[inst->pos]);
		memcpy(&fb[inst->pos], buf, bytes);
		inst->pos += bytes;
		return bytes;
	}else{
		return vga_device.write(inst->vga, bytes, buf);
	}	
}

bt_filesize_t vbe_seek(void *instance, bt_filesize_t pos, uint32_t flags){
	hold_lock hl(&vga_device_lock);
	vbe_instance *inst=(vbe_instance*)instance;
	if(is_vbe_mode()){
		//dbgpf("VGA: VBE Seeking %i (mode %x). Current pos: %i.\n", (int)pos, flags, (int) inst->pos);
		if(flags & FS_Relative){
			inst->pos+=pos;
		}else if(flags & FS_Backwards){
			inst->pos=fb_sz - pos;
		}else if(flags == (FS_Relative | FS_Backwards)){
			inst->pos-=pos;
		}else{
			inst->pos=pos;
		}
		if(inst->pos > fb_sz) inst->pos = fb_sz;
		return inst->pos;
	}else{
		return vga_device.seek(inst->vga, pos, flags);
	}	
}

int vbe_ioctl(void *instance, int fn, size_t bytes, char *buf){
	hold_lock hl(&vga_device_lock);
	dbgpf("VGA: VBE ioctl %i. VBE mode: %i.\n", fn, is_vbe_mode());
	vbe_instance *inst=(vbe_instance*)instance;
	if(fn == bt_vid_ioctl::GetModeCount) {
		size_t vga_mode_count = vga_device.ioctl(inst->vga, fn, bytes, buf);
		return vga_mode_count + vbe_modes->size();
	}
	else if(fn==bt_vid_ioctl::QueryMode) {
		if(bytes == sizeof(bt_vidmode)) {
			bt_vidmode &vidmode = *(bt_vidmode *) buf;
			if(is_vbe_mode()){
				vidmode = make_vidmode_from_id(current_mode);
				return sizeof(vidmode);
			}else{
				bt_vidmode vga_mode;
				size_t ret = vga_device.ioctl(inst->vga, fn, sizeof(vga_mode), (char*)&vga_mode);
				vga_mode.id += 0xF0000;
				vidmode = vga_mode;
				return ret;
			}
		}else return 0;
	}
	else if(fn==bt_vid_ioctl::GetMode) {
		if(bytes == sizeof(bt_vidmode)) {
			uint32_t &index = *(uint32_t *) buf;
			if(index < vbe_modes->size()){
				bt_vidmode &vidmode = *(bt_vidmode *) buf;
				vidmode = make_vidmode_from_index(index);
				return sizeof(vidmode);
			}else{
				index -= vbe_modes->size();
				size_t ret = vga_device.ioctl(inst->vga, fn, bytes, buf);
				bt_vidmode &vidmode = *(bt_vidmode *) buf;
				vidmode.id += 0xF0000;
				return ret;
			}
		}else return 0;
	}else if(fn==bt_vid_ioctl::SetMode) {
		if(bytes == sizeof(bt_vidmode)) {
			bt_vidmode &vidmode = *(bt_vidmode *) buf;
			dbgpf("VGA: Request for mode %x\n", vidmode.id);
			if(is_vbe_mode(vidmode.id)){
				dbgpf("VGA: Setting VBE mode %x\n", vidmode.id);
				unmap_fb();
				modeinfo = (*vbe_modes)[vidmode.id];
				if(!modeinfo.PhysBasePtr) panic("(VGA) Bad mode.");
				VBE_SetMode(vidmode.id, true);
				current_mode = vidmode.id;
				map_fb();
			}else{
				if(is_vbe_mode()){
					unmap_fb();
					VBE_ResetToVGA();
					current_mode = 0xF0003;
				}
				vidmode.id -= 0xF0000;
				dbgpf("VGA: Setting VGA mode %x\n", vidmode.id);
				size_t ret = vga_device.ioctl(inst->vga, fn, bytes, buf);
				vidmode.id += 0xF0000;
				return ret;
			}
		}
		return 0;
	}else if(fn==bt_vid_ioctl::GetPaletteEntry) {
		if(bytes == sizeof(bt_video_palette_entry)){
			if(is_vbe_mode()){
				return 0;
			}else{
				return vga_device.ioctl(inst->vga, fn, bytes, buf);
			}
		}
		return 0;
	}else{
		if(is_vbe_mode()){
			return 0;
		}else{
			return vga_device.ioctl(inst->vga, fn, bytes, buf);
		}
	}
	return 0;
}

int vbe_type(){
    return driver_types::VIDEO;
}

char *vbe_desc(){
    return "VESA VBE video device";
}

drv_driver vbe_device={&vbe_open, &vbe_close, &vbe_read, &vbe_write, &vbe_seek, &vbe_ioctl, &vbe_type, &vbe_desc};

void init_vbe_device(){
	init_lock(&vga_device_lock);
    add_device("VGA", &vbe_device, NULL);
}

