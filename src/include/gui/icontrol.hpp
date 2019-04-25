#ifndef _ICONTROL_HPP
#define _ICONTROL_HPP

#include <btos.h>
#include <wm/wm.h>
#include <gds/surface.hpp>

#include "eventresponse.hpp"

namespace btos_api{
namespace gui{
	
class Container;

namespace ControlFlags{
	static const uint32_t NoFocus = 1 << 0;
}

class IControl{
protected:
	void Paint(const gds::Rect &rect);
	void BindToParent(IControl &ctrl);
	void FocusNext(bool reverse);
public:
	std::function<void(const gds::Rect &)> paintFn;
	std::function<void(IControl &)> bindFn;
	std::function<bool(const IControl *)> isFocusFn;
	std::function<void(bool)> focusNextFn;

	virtual EventResponse HandleEvent(const wm_Event&) = 0;
	virtual void Paint(gds::Surface &surf) = 0;
	virtual gds::Rect GetPaintRect() = 0;
	virtual gds::Rect GetInteractRect() = 0;
	virtual uint32_t GetSubscribed() = 0;
	virtual void Focus() = 0;
	virtual void Blur() = 0;
	virtual uint32_t GetFlags() = 0;
	
	bool IsFocus();

	virtual ~IControl() {}
};

}
}

#endif
