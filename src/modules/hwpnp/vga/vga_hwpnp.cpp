#include <btos_module.h>
#include <dev/hwpnp/video.hpp>
#include "vga.hpp"
#include "vbe.hpp"
#include "device.hpp"
#include "modes.hpp"
#include "ops.hpp"
#include <util/holdlock.hpp>

USE_PURE_VIRTUAL;
USE_STATIC_INIT;

lock device_lock;

static const btos_api::hwpnp::DeviceID VGADeviceID = {
	btos_api::hwpnp::PNPBUS::PCI, 0, 0, 0, 0, 0x0300
};

btos_api::hwpnp::IDriver* GetVGADriver();

class VGAVideoDevice : public btos_api::hwpnp::IVideo{
private:
	btos_api::hwpnp::VideoDeviceNode *node;
public:
	VGAVideoDevice();
	
	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	btos_api::hwpnp::IDeviceNode *GetDeviceNode();
	
	size_t WriteFrameBuffer(size_t pos, size_t len, const uint8_t *buf, bt_vid_text_access_mode::Enum textmode, size_t &newpos);
	size_t ReadFrameBuffer(size_t pos, size_t len, uint8_t *buf, bt_vid_text_access_mode::Enum textmode, size_t &newpos);
	size_t GetFrameBufferSize(bt_vid_text_access_mode::Enum textmode);
		
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
	void SetCursorPosition(size_t pos);
		
	void ClearScreen();
};

btos_api::hwpnp::DeviceID VGAVideoDevice::GetID(){
	return VGADeviceID;
}

const char *VGAVideoDevice::GetDescription(){
	return "VGA/VESA VBE display";
}

size_t VGAVideoDevice::GetSubDeviceCount(){
	return 0;
}

btos_api::hwpnp::DeviceID VGAVideoDevice::GetSubDevice(size_t){
	return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *VGAVideoDevice::GetDriver(){
	return GetVGADriver();
}

btos_api::hwpnp::IDeviceNode *VGAVideoDevice::GetDeviceNode(){
	return node;
}

size_t VGAVideoDevice::WriteFrameBuffer(size_t pos, size_t len, const uint8_t *buf, bt_vid_text_access_mode::Enum textmode, size_t &newpos){
	hold_lock hl(&device_lock);
	if(is_vbe_mode()){
		if(pos + len > fb_sz) len = (fb_sz - pos);
		memcpy(&fb[pos], buf, len);
		newpos = pos + len;
		return len;
	}else{
		vga_instance inst;
		inst.pos = pos;
		inst.mode = textmode;
		if(current_mode->vidmode.textmode){
			text_seek(&inst, pos, FS_Set);
			size_t ret = text_write(&inst, len, (char*)buf);
			newpos = inst.pos;
			return ret;
		}else {
			size_t ret = graphics_write(&inst, len, (char*)buf);
			newpos = inst.pos;
			return ret;
		}
	}	
}

size_t VGAVideoDevice::ReadFrameBuffer(size_t pos, size_t len, uint8_t *buf, bt_vid_text_access_mode::Enum textmode, size_t &newpos){
	hold_lock hl(&device_lock);
	if(is_vbe_mode()){
		if(pos + len > fb_sz) len = (fb_sz - pos);
		memcpy(buf, &fb[pos], len);
		newpos = pos + len;
		return len;
	}else{
		vga_instance inst;
		inst.pos = pos;
		inst.mode = textmode;
		if(current_mode->vidmode.textmode){
			text_seek(&inst, pos, FS_Set);
			size_t ret = text_read(&inst, len, (char*)buf);
			newpos = inst.pos;
			return ret;
		}else{
			size_t ret = graphics_read(&inst, len, (char*)buf);
			newpos = inst.pos;
			return ret;
		}
	}	
}

size_t VGAVideoDevice::GetFrameBufferSize(bt_vid_text_access_mode::Enum textmode){
	hold_lock hl(&device_lock);
	if(is_vbe_mode()){
		return fb_sz;
	}else{
		vga_instance inst;
		inst.pos = 0;
		inst.mode = textmode;
		if(current_mode->vidmode.textmode){
			//size_t cpos = text_seek(&inst, 0, FS_Relative);
			size_t ret = text_seek(&inst, 0, FS_Backwards);
			//text_seek(&inst, cpos, FS_Set);
			return ret;
		}else {
			return graphics_seek(&inst, 0, FS_Backwards);
		}
	}
}
		
size_t VGAVideoDevice::GetModeCount(){
	return vga_mode_count + vbe_modes->size();
}

bt_vidmode VGAVideoDevice::GetMode(size_t idx){
	if(idx < vbe_modes->size()){
		return make_vidmode_from_index(idx);
	}else{
		idx -= vbe_modes->size();
		bt_vidmode mode = vga_modes[idx]->vidmode;
		mode.id += 0xF0000;
		return mode;
	}
}

void VGAVideoDevice::SetMode(const bt_vidmode &mode){
	hold_lock hl(&device_lock);
	dbgpf("VGA: Request for mode %x\n", mode.id);
	if(mode.id == vbe_current_mode){
		dbgout("VGA: Already in mode. Nothing to do.\n");
		return;
	}
	if(is_vbe_mode(mode.id)){
		dbgpf("VGA: Setting VBE mode %x\n", mode.id);
		unmap_fb();
		modeinfo = (*vbe_modes)[mode.id];
		if(!modeinfo.PhysBasePtr) return;
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
        if(vgamode==NULL) return;
        current_mode = vgamode;
        vgamode->set_mode();
		return;
	}
}

bt_vidmode VGAVideoDevice::QueryMode(){
	hold_lock hl(&device_lock);
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

void VGAVideoDevice::SetCursorPosition(size_t pos){
	hold_lock hl(&device_lock);
	if(!is_vbe_mode() && current_mode->vidmode.textmode){
		vga_instance inst;
		inst.pos = 0;
		inst.mode = bt_vid_text_access_mode::Simple;
		text_seek(&inst, pos, FS_Set);
	}
}
		
void VGAVideoDevice::ClearScreen(){
	hold_lock hl(&device_lock);
	if(is_vbe_mode()){
		vbe_clear_screen();
	}else{
		current_mode->set_mode();
	}
}

class VGADeviceNode : public btos_api::hwpnp::VideoDeviceNode{
public:
	VGADeviceNode(VGAVideoDevice *dev);
	const char *GetBaseName();
};

VGAVideoDevice::VGAVideoDevice() : node(new VGADeviceNode(this)) {}

VGADeviceNode::VGADeviceNode(VGAVideoDevice *dev) : btos_api::hwpnp::VideoDeviceNode(dev) {}

const char *VGADeviceNode::GetBaseName(){
	return "VGA";
}

class VGADriver : public btos_api::hwpnp::IDriver{
public:
	btos_api::hwpnp::DeviceID GetDeviceID();
	bool IsCompatible(const btos_api::hwpnp::DeviceID &dev);
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index);
	const char *GetDescription();
	void DestroyDevice(btos_api::hwpnp::IDevice *dev);
	uint32_t GetPriority();
};

btos_api::hwpnp::DeviceID VGADriver::GetDeviceID(){
	return VGADeviceID;
}

bool VGADriver::IsCompatible(const btos_api::hwpnp::DeviceID &dev){
	if(dev.Bus == VGADeviceID.Bus && dev.Class == VGADeviceID.Class) return true;
	else return false;
}

btos_api::hwpnp::IDevice *VGADriver::CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index){
	return new VGAVideoDevice();
}

const char *VGADriver::GetDescription(){
	return "VGA/VESA VBE display driver";
}

void VGADriver::DestroyDevice(btos_api::hwpnp::IDevice *dev){
	delete (VGAVideoDevice*)dev;
}

uint32_t VGADriver::GetPriority(){
	return btos_api::hwpnp::DriverPriority::Fallback;
}

static VGADriver theDriver;

btos_api::hwpnp::IDriver* GetVGADriver(){
	return &theDriver;
}

void init_hwpnp(){
	init_lock(&device_lock);
	pnp_register_driver(GetVGADriver());
}
