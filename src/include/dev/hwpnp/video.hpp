#ifndef _VIDEO_HPP
#define _VIDEO_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include <dev/video_dev.h>

namespace btos_api{
namespace hwpnp{
	
	class IVideo : public IDevice{
	public:
		virtual size_t WriteFrameBuffer(size_t pos, size_t len, const uint8_t *buf, size_t &newpos) = 0;
		virtual size_t ReadFrameBuffer(size_t pos, size_t len, uint8_t *buf, size_t &newpos) = 0;
		virtual size_t GetFrameBufferSize() = 0;
		
		virtual size_t GetModeCount() = 0;
		virtual bt_vidmode GetMode(size_t idx) = 0;
		virtual void SetMode(const bt_vidmode &mode) = 0;
		virtual bt_vidmode QueryMode() = 0;
		virtual bt_video_palette_entry GetPaletteEntry(uint8_t idx) = 0;
		
		virtual bool GetCursorVisibility() = 0;
		virtual void SetCursorVisibility(bool v) = 0;
		virtual void SetCursorPosition(size_t pos) = 0;
		
		virtual void ClearScreen() = 0;
		
		int GetType() {
			return driver_types::VIDEO;
		}
		
		virtual ~IVideo() {}
	};
	
	class VideoDeviceNode : public IDeviceNode{
	private:
		IVideo *device;
		struct Handle{
			bt_filesize_t pos = 0;
		};
	public:
		VideoDeviceNode(IVideo *dev) : device(dev) {}
		
		virtual const char *GetBaseName() = 0;
		
		void *Open(){
			return new Handle();
		}
		
		virtual bool Close(void *h){
			if(!h) return false;
			delete (Handle*)h;
			return true;
		}
		
		virtual size_t Read(void *h, size_t bytes, char *buf){
			Handle *handle = (Handle*)h;
			size_t newpos;
			size_t ret = device->ReadFrameBuffer(handle->pos, bytes, (uint8_t*)buf, newpos);
			handle->pos = newpos;
			return ret;
		}
		
		virtual size_t Write(void *h, size_t bytes, const char *buf){
			Handle *handle = (Handle*)h;
			size_t newpos;
			size_t ret = device->WriteFrameBuffer(handle->pos, bytes, (const uint8_t*)buf, newpos);
			handle->pos = newpos;
			return ret;
		}
		
		virtual bt_filesize_t Seek(void *h, bt_filesize_t pos, uint32_t flags){
			Handle *handle = (Handle*)h;
			auto size = device->GetFrameBufferSize();
			if(flags == FS_Set){
				if(pos > size) pos = size;
				handle->pos = pos;
			}else if(flags == (FS_Set | FS_Backwards)){
				if(pos > size) pos = size;
				handle->pos = size - pos;
			}else if(flags == FS_Relative){
				if(handle->pos + pos < handle->pos || handle->pos > size){
					handle->pos = size;
				}else{
					handle->pos += pos;
				}
			}else if(flags == (FS_Relative | FS_Backwards)){
				if(handle->pos - pos > handle->pos){
					handle->pos = 0;
				}else{
					handle->pos -= pos;
				}
			}
			return handle->pos;
		}
		
		virtual int IOCtl(void */*h*/, int fn, size_t bytes, char *buf){
			if(fn == bt_vid_ioctl::GetModeCount) {
		        return device->GetModeCount();
		    }
		    else if(fn==bt_vid_ioctl::QueryMode) {
		        if(bytes == sizeof(bt_vidmode)) {
		            bt_vidmode mode = device->QueryMode();
		            memcpy(buf, &mode, sizeof(mode));
		            return bytes;
		        }else return 0;
		    }
		    else if(fn==bt_vid_ioctl::GetMode) {
		        if(bytes == sizeof(bt_vidmode)) {
		            size_t index = *(size_t *) buf;
		            bt_vidmode mode = device->GetMode(index);
		            memcpy(buf, &mode, sizeof(mode));
		            return bytes;
		        }else return 0;
		    }else if(fn==bt_vid_ioctl::SetMode) {
		        if(bytes == sizeof(bt_vidmode)) {
		            bt_vidmode vidmode = *(bt_vidmode *) buf;
		            device->SetMode(vidmode);
		        }
		        return 0;
		    }else if(fn==bt_vid_ioctl::GetPaletteEntry) {
		        if(bytes == sizeof(bt_video_palette_entry)){
		            bt_video_palette_entry &entry=*(bt_video_palette_entry*)buf;
		            entry=device->GetPaletteEntry((uint8_t)entry.index);
		            return (int)entry.index;
		        }
		        return 0;
		    }else if(fn==bt_vid_ioctl::ClearScreen){
		        device->ClearScreen();
		    }else if(fn==bt_vid_ioctl::SetCursorPosition){
		    	if(bytes==sizeof(size_t)){
		    		device->SetCursorPosition(*(size_t*)buf);
		    	}
		    }
			return 0;
		};
		
		virtual int GetType(){
			return device->GetType();
		}
		
		virtual const char *GetDescription(){
			return device->GetDescription();
		}
		
		virtual ~VideoDeviceNode() {}
	};
	
}
}

#endif