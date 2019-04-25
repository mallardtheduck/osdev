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

template<typename T>
class IActionControl : public IControl{
protected:
	std::function<bool(T)> actionFn;
	bool RaiseEvent(const T &p){
		if(actionFn) return actionFn(p);
		else return false;
	}
public:
	void SetAction(const std::function<bool(T)> &fn){
		actionFn = fn;
	}
	
	virtual ~IActionControl() {}
};

template<>
class IActionControl<void> : public IControl{
protected:
	std::function<bool()> actionFn;
	bool RaiseEvent(){
		if(actionFn) return actionFn();
		else return false;
	}
public:
	void SetAction(const std::function<bool()> &fn){
		actionFn = fn;
	}
	
	virtual ~IActionControl() {}
};

template<typename T> 
class IValueControl : public IControl{
public:
	virtual T GetValue() = 0;
	virtual ~IValueControl() {}
};

}
}

#endif
