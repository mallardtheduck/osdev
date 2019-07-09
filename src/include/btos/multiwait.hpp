#ifndef _MULTIWAIT_HPP
#define _MULTIWAIT_HPP

#include "handle.hpp"
#include <vector>

namespace btos_api{
	
	class MultiWait : public Handle{
	private:
		std::vector<Handle*> handles;
	public:
		enum class WaitMode{
			Any, All
		};
	
		MultiWait(const std::vector<Handle*> &handles, WaitMode mode);
		
		Handle *GetTriggerHandle();
	};
	
}

#endif