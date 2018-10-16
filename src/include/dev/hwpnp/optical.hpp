#ifndef _OPTICAL_HPP
#define _OPTICAL_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>

namespace btos_api{
namespace hwpnp{

	class IOpticalDevice : public IDevice{
	public:
		void ReadSector(uint64_t lba, uint8_t *buf) = 0;
		size_t GetSectorSize() = 0;
		
		int GetType() {
			return driver_types::STR_OPTICAL;
		}
		
		~IOpticalDevice() {}
	}
	
}
}

#endif