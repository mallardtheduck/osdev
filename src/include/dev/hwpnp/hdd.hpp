#ifndef _HDD_HPP
#define _HDD_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>

namespace btos_api{
namespace hwpnp{

	class HDDDeviceNode;

	class IHDDDevice : public IDevice{
	public:
		virtual void ReadSector(uint64_t lba, uint8_t *buf) = 0;
		virtual void WriteSector(uint64_t lba, const uint8_t *buf) = 0;
		virtual size_t GetSectorSize() = 0;
		virtual bt_filesize_t GetSize() = 0;
		
		int GetType() {
			return driver_types::STR_HDD;
		}
		
		virtual ~IHDDDevice() {}
	};
	
	class HDDDeviceNode : public IDeviceNode{
	private:
		IHDDDevice *device;
		struct Handle{
			bt_filesize_t pos = 0;
		};
	public:
		HDDDeviceNode(IHDDDevice *dev) : device(dev) {}
		
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
			uint32_t secSize =  device->GetSectorSize();
			if(bytes % secSize) return 0;
			Handle *handle = (Handle*)h;
			bt_filesize_t lba = handle->pos / secSize;
			size_t count = bytes / secSize;
			for(size_t i = 0; i < count; ++i){
				device->ReadSector(lba + i, (uint8_t*)buf + (secSize * i));
				handle->pos += secSize;
			}
			return bytes;
		}
		
		virtual size_t Write(void *h, size_t bytes, const char *buf){
			uint32_t secSize =  device->GetSectorSize();
			if(bytes % secSize) return 0;
			Handle *handle = (Handle*)h;
			bt_filesize_t lba = handle->pos / secSize;
			size_t count = bytes / secSize;
			for(size_t i = 0; i < count; ++i){
				device->WriteSector(lba + i, (uint8_t*)buf + (secSize * i));
				handle->pos += secSize;
			}
			return bytes;
		}
		
		virtual bt_filesize_t Seek(void *h, bt_filesize_t pos, uint32_t flags){
			Handle *handle = (Handle*)h;
			if(pos % device->GetSectorSize()) return handle->pos;
			auto size = device->GetSize();
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
		
		virtual int IOCtl(void *, int, size_t, char *){
			return 0;
		};
		
		virtual int GetType(){
			return device->GetType();
		}
		
		virtual const char *GetDescription(){
			return device->GetDescription();
		}
		
		virtual ~HDDDeviceNode() {}
	};
	
}
}

#endif