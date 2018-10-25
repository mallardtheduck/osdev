#ifndef _VIDEO_HPP
#define _VIDEO_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include <dev/video_dev.h>

namespace btos_api{
namespace hwpnp{
	
	class IVideo : public IDevice{
	public:
		virtual size_t WriteFrameBuffer(size_t pos, size_t len, const uint8_t *buf, ENUM_NAME(bt_vid_text_access_mode) textmode, size_t &newpos) = 0;
		virtual size_t ReadFrameBuffer(size_t pos, size_t len, uint8_t *buf, ENUM_NAME(bt_vid_text_access_mode) textmode, size_t &newpos) = 0;
		virtual size_t GetFrameBufferSize(ENUM_NAME(bt_vid_text_access_mode) textmode) = 0;
		
		virtual size_t GetModeCount() = 0;
		virtual bt_vidmode GetMode(size_t idx) = 0;
		virtual void SetMode(const bt_vidmode &mode) = 0;
		virtual bt_vidmode QueryMode() = 0;
		virtual bt_video_palette_entry GetPaletteEntry(uint8_t idx) = 0;
		
		virtual void SetTextColours(uint8_t c) = 0;
		virtual uint8_t GetTextColours() = 0;
		virtual bool GetScrolling() = 0;
		virtual void SetScrolling(bool v) = 0;
		virtual bool GetCursorVisibility() = 0;
		virtual void SetCursorVisibility(bool v) = 0;
		
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
			ENUM_NAME(bt_vid_text_access_mode) textmode = ENUM_GET(bt_vid_text_access_mode, Simple);
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
			size_t ret = device->ReadFrameBuffer(handle->pos, bytes, (uint8_t*)buf, handle->textmode, newpos);
			handle->pos = newpos;
			return ret;
		}
		
		virtual size_t Write(void *h, size_t bytes, const char *buf){
			Handle *handle = (Handle*)h;
			size_t newpos;
			size_t ret = device->WriteFrameBuffer(handle->pos, bytes, (const uint8_t*)buf, handle->textmode, newpos);
			handle->pos = newpos;
			return ret;
		}
		
		virtual bt_filesize_t Seek(void *h, bt_filesize_t pos, uint32_t flags){
			Handle *handle = (Handle*)h;
			auto size = device->GetFrameBufferSize(handle->textmode);
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
		
		virtual int IOCtl(void *h, int fn, size_t bytes, char *buf){
			Handle *handle = (Handle*)h;
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
		    }else  if(fn==bt_vid_ioctl::SetTextColours){
		        if(bytes>=1){
		            device->SetTextColours((uint8_t)*buf);
		            return 1;
		        }else return 0;
		    }else if(fn==bt_vid_ioctl::GetTextColours){
		        return device->GetTextColours();
		    }else if(fn==bt_vid_ioctl::ClearScreen){
		        device->ClearScreen();
		    }else if(fn==bt_vid_ioctl::GetScrolling){
		        return device->GetScrolling();
		    }else if(fn==bt_vid_ioctl::SetScrolling){
		        device->SetScrolling(*(bool*)buf);
		    }else if(fn==bt_vid_ioctl::GetTextAccessMode){
		        return handle->textmode;
		    }else if(fn==bt_vid_ioctl::SetTextAccessMode){
		        if(bytes==sizeof(ENUM_NAME(bt_vid_text_access_mode))) {
		            handle->textmode = *(ENUM_NAME(bt_vid_text_access_mode)*) buf;
		            return sizeof(ENUM_NAME(bt_vid_text_access_mode));
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