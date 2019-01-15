#ifndef _MOUSE_HPP
#define _MOUSE_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include <dev/mouse.h>

namespace btos_api{
namespace hwpnp{
	
	class IMouse : public IDevice{
	public:
		virtual size_t Read(size_t bytes, char *buf) = 0;
		virtual void ClearBuffer() = 0;
		
		int GetType() {
			return driver_types::IN_MOUSE;
		}
		
		virtual ~IMouse() {}	
	};
	
	class MouseDeviceNode : public IDeviceNode{
	private:
		IMouse *dev;
		struct Handle{
		};
	public:
		MouseDeviceNode(IMouse *d) : dev(d) {}
	
		virtual const char *GetBaseName() = 0;
		
		virtual void *Open(){
			return new Handle();
		}
		
		virtual bool Close(void *h){
			if(h){
				delete (Handle*)h;
				return true;
			}else return false;
		}
		
		virtual size_t Read(void *h, size_t bytes, char *buf){
			if(h) return dev->Read(bytes, buf);
			else return 0;
		}
		
		virtual size_t Write(void *, size_t, const char *){
			return 0;
		}
		
		virtual bt_filesize_t Seek(void *, bt_filesize_t, uint32_t){
			return 0;
		}
		
		virtual int IOCtl(void *, int fn, size_t, char *){
			if(fn == bt_mouse_ioctl::ClearBuffer) dev->ClearBuffer();
			return 0;
		}
		
		virtual int GetType(){
			return dev->GetType();
		}
		
		virtual const char *GetDescription(){
			return dev->GetDescription();
		}
		
		virtual ~MouseDeviceNode() {}
	};
	
}
}

#endif