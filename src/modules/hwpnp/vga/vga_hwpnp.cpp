#include <btos_module.h>
#include <dev/hwpnp/video.hpp>
#include "vga.hpp"
#include "vbe.hpp"

static const btos_api::hwpnp::DeviceID VGADeviceID = {
	btos_api::hwpnp::PNPBUS::PCI, 0, 0, 0, 0, 0x0300
};

class VGAVideoDevice : public btos_api::hwpnp::IVideo{
public:
	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	btos_api::hwpnp::IDeviceNode *GetDeviceNode();
	
	size_t WriteFrameBuffer(size_t pos, size_t len, const uint8_t *buf);
	size_t ReadFrameBuffer(size_t pos, size_t len, uint8_t *buf);
		
	size_t GetModeCount();
	bt_vidmode GetMode(size_t idx);
	void SetMode(const bt_vidmode &mode);
	bt_vidmode QueryMode();
	bt_video_palette_entry GetPaletteEntry(uint8_t idx);
		
	void SetTextColours(uint8_t c);
	uint8_t GetTextColours();
	bool GetScrolling();
	void SetScrolling(bool v);
	bool GetCursorVisibility();
	void SetCursorVisibility(bool v);
		
	void ClearScreen();
};

btos_api::hwpnp::DeviceID VGAVideoDevice::GetID(){
	return VGADeviceID;
}

const char *VGAVideoDevice::GetDescription(){
	return "VGA/VESA VBE display device";
}

size_t VGAVideoDevice::GetSubDeviceCount(){
	return 0;
}

btos_api::hwpnp::DeviceID VGAVideoDevice::GetSubDevice(size_t){
	return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *VGAVideoDevice::GetDriver(){
	return nullptr;
}

btos_api::hwpnp::IDeviceNode *VGAVideoDevice::GetDeviceNode(){
	return nullptr;
}

size_t VGAVideoDevice::WriteFrameBuffer(size_t pos, size_t len, const uint8_t *buf){
	if(is_vbe_mode()){
		if(pos + len > fb_sz) len = (fb_sz - pos);
		memcpy(&fb[pos], buf, len);
		return len;
	}else{
		vga_instance inst;
		inst.pos = pos;
		if(current_mode->vidmode.textmode){
			return text_write(&inst, len, buf);
		}else {
			return graphics_write(&inst, len, buf);
		}
	}	
}

size_t VGAVideoDevice::ReadFrameBuffer(size_t pos, size_t len, uint8_t *buf){
	if(is_vbe_mode()){
		if(pos + len > fb_sz) len = (fb_sz - pos);
		memcpy(buf, &fb[inst->pos], len);
		return len;
	}else{
		vga_instance inst;
		inst.pos = pos;
		if(current_mode->vidmode.textmode){
			return text_read(inst, bytes, buf);
		}else{
			return graphics_read(inst, bytes, buf);
		}
	}	
}
		
size_t VGAVideoDevice::GetModeCount(){
	return vga_mode_count + vbe_modes->size();
}

bt_vidmode VGAVideoDevice::GetMode(size_t idx){
	if(idx < vbe_modes->size()){
		return (*vbe_modes)[idx];
	}else{
		index -= vbe_modes->size();
		bt_vidmode mode = vga_modes[index]->vidmode;
		mode.id += 0xF0000;
		return mode;
	}
}

void VGAVideoDevice::SetMode(const bt_vidmode &mode){
	dbgpf("VGA: Request for mode %x\n", mode.id);
	if(vidmode.id == vbe_current_mode){
		dbgout("VGA: Already in mode. Nothing to do.\n");
		return 0;
	}
	if(is_vbe_mode(mode.id)){
		dbgpf("VGA: Setting VBE mode %x\n", mode.id);
		unmap_fb();
		modeinfo = (*vbe_modes)[mode.id];
		if(!modeinfo.PhysBasePtr) return 0;
		VBE_SetMode(mode.id, true);
		vbe_current_mode = mode.id;
		if(modeinfo.MemoryModel == VBE_MemoryModel::Packed) set_palette();
		map_fb();
		vbe_clear_screen();
	}else{
		if(is_vbe_mode()){
			unmap_fb();
			VBE_ResetToVGA();
			vbe_current_mode = 0xF0003;
		}
		auto vidmode = mode;
		vidmode.id -= 0xF0000;
		dbgpf("VGA: Setting VGA mode %x\n", mode.id);
		graphics_end();
        vga_mode *vgamode=NULL;
        for(size_t i=0; i<vga_mode_count; ++i){
            if(vga_modes[i]->vidmode.id == vidmode.id){
                vgamode=vga_modes[i];
                break;
            }
        }
        if(vgamode==NULL) return 0;
        current_mode = vga;
        vgamode->set_mode();
		return ret;
	}
}

bt_vidmode VGAVideoDevice::QueryMode(){
	if(is_vbe_mode()) return make_vidmode_from_id(vbe_current_mode);
	auto ret = current_mode->vidmode;
	ret.id += 0xF0000;
	return ret;
}

bt_video_palette_entry VGAVideoDevice::GetPaletteEntry(uint8_t idx){
	return get_palette_entry((uint8_t)idx);
}
		
void VGAVideoDevice::SetTextColours(uint8_t c){
	text_color=c;
}

uint8_t VGAVideoDevice::GetTextColours(){
	return text_color;
}

bool VGAVideoDevice::GetScrolling(){
	return scrolling_enabled;
}

void VGAVideoDevice::SetScrolling(bool v){
	scrolling_enabled = v;
}

bool VGAVideoDevice::GetCursorVisibility(){
	return true;
}

void VGAVideoDevice::SetCursorVisibility(bool){
	//Not implemented
}
		
void VGAVideoDevice::ClearScreen(){
	if(is_vbe_mode()){
		vbe_clear_screen();
	}else{
		current_mode->set_mode();
	}
}
