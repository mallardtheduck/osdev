#ifndef _BLOCKDEVICE_HPP
#define _BLOCKDEVICE_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include <btos/ioctl.h>

namespace btos_api{
namespace hwpnp{

	class IBlockDevice : public IDevice{
	public:
		virtual bool ReadSector(uint64_t lba, uint8_t *buf) = 0;
		virtual bool WriteSector(uint64_t lba, const uint8_t *buf) = 0;
		virtual uint64_t AsyncReadSector(uint64_t lba, uint8_t *buf){
			return ReadSector(lba, buf);
		}
		virtual uint64_t AsyncWriteSector(uint64_t lba, const uint8_t *buf){
			return WriteSector(lba, buf);
		}
		virtual bool Await(uint64_t id){
			return (bool)id;
		}
		virtual size_t GetSectorSize() = 0;
		virtual bt_filesize_t GetSize() = 0;
	
		virtual ~IBlockDevice() {}
	};
	
	class BlockDeviceNode : public IDeviceNode{
	private:
		IBlockDevice *device;
		struct Handle{
			bt_filesize_t pos = 0;
		};
	public:
		BlockDeviceNode(IBlockDevice *dev) : device(dev) {}
		
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
			size_t read = 0;
			vector<uint64_t> opIds;
			for(size_t i = 0; i < count; ++i){
				auto id = device->AsyncReadSector(lba + i, (uint8_t*)buf + (secSize * i));
				opIds.push_back(id);
				handle->pos += secSize;
			}
			bool ok = true;
			for(auto &id : opIds){
				if(!device->Await(id)) ok = false;
				if(ok) read += secSize;
			}
			return read;
		}
		
		virtual size_t Write(void *h, size_t bytes, const char *buf){
			uint32_t secSize =  device->GetSectorSize();
			if(bytes % secSize) return 0;
			Handle *handle = (Handle*)h;
			bt_filesize_t lba = handle->pos / secSize;
			size_t count = bytes / secSize;
			size_t written = 0;
			vector<uint64_t> opIds;
			for(size_t i = 0; i < count; ++i){
				auto id = device->AsyncWriteSector(lba + i, (uint8_t*)buf + (secSize * i));
				opIds.push_back(id);
				handle->pos += secSize;
			}
			bool ok = true;
			for(auto &id : opIds){
				if(!device->Await(id)) ok = false;
				if(ok) written += secSize;
			}
			return written;
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
			}else{
				dbgout("BLOCKDEV: Unknown seek flags!\n");
			}
			return handle->pos;
		}
		
		virtual int IOCtl(void */*h*/, int fn, size_t sz, char *buf){
			if(fn == bt_ioctl::BlockSize && sz >= sizeof(size_t)){
				*(size_t*)buf = device->GetSectorSize();
				return sizeof(size_t);
			}
			return 0;
		};
		
		virtual int GetType(){
			return device->GetType();
		}
		
		virtual const char *GetDescription(){
			return device->GetDescription();
		}
		
		virtual ~BlockDeviceNode() {}
	};

}
}

#endif