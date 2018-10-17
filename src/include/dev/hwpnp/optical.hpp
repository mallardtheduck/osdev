#ifndef _OPTICAL_HPP
#define _OPTICAL_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include "blockdevice.hpp"

namespace btos_api{
namespace hwpnp{

	class IOpticalDevice : public IBlockDevice{
	public:
		int GetType() {
			return driver_types::STR_OPTICAL;
		}
		
		~IOpticalDevice() {}
	}
	
}
}

#endif