#ifndef _ICONTROL_HPP
#define _ICONTROL_HPP

#include <btos.h>
#include <wm/wm.h>
#include <gds/surface.hpp>

namespace btos_api{
namespace gui{

class IControl{
public:
	virtual bool HandleEvent(const wm_Event&) = 0;
	virtual void Paint(gds::Surface &surf) = 0;
	virtual gds::Rect GetRect() = 0;
	virtual uint32_t GetSubscribed() = 0;
	virtual void Focus() = 0;
	virtual void Blur() = 0;

	virtual ~IControl() {}
};

}
}

#endif