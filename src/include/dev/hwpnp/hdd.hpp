#ifndef _HDD_HPP
#define _HDD_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include "blockdevice.hpp"

namespace btos_api{
namespace hwpnp{

	class HDDDeviceNode;

	class IHDDDevice : public IBlockDevice{
	public:
		int GetType() {
			return driver_types::STR_HDD;
		}
		
		virtual ~IHDDDevice() {}
	};
	
	class IVolume : public IDevice{
	public:
		virtual bool ReadSector(size_t index, uint64_t lba, uint8_t *buf) = 0;
		virtual bool WriteSector(size_t index, uint64_t lba, const uint8_t *buf) = 0;
		virtual size_t GetSectorSize() = 0;
		virtual bt_filesize_t GetSize(size_t index) = 0;
		
		int GetType() {
			return driver_types::STR_VOLUME;
		}
		
		virtual ~IVolume() {}
	};
	
}
}

#endif