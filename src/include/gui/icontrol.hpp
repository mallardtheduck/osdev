#ifndef _ICONTROL_HPP
#define _ICONTROL_HPP

#include <btos.h>
#include <wm/wm.h>
#include <gds/surface.hpp>

#include <type_traits>
#include <functional>

#include "eventresponse.hpp"

namespace btos_api{
namespace gui{
	
class Container;

namespace ControlFlags{
	static const uint32_t NoFocus = 1 << 0;
}

namespace ZOrder{
	const size_t Background = 1000;
	const size_t Default = 2000;
	const size_t Foreground = 3000;
};

class IControl{
protected:
	void Paint(const gds::Rect &rect);
	void BindToParent(IControl &ctrl);
	void FocusNext(bool reverse);
	gds::Rect GetContainerRect();
	void AddToParent(std::shared_ptr<IControl> ctrl);
	void RemoveFromParent(std::shared_ptr<IControl> ctrl);
public:
	std::function<void(const gds::Rect &)> paintFn;
	std::function<void(IControl &)> bindFn;
	std::function<bool(const IControl *)> isFocusFn;
	std::function<void(bool)> focusNextFn;
	std::function<gds::Rect()> getRectFn;
	std::function<void(std::shared_ptr<IControl>)> addControlFn;
	std::function<void(std::shared_ptr<IControl>)> removeControlFn;

	virtual EventResponse HandleEvent(const wm_Event&) = 0;
	virtual void Paint(gds::Surface &surf) = 0;
	virtual gds::Rect GetPaintRect() = 0;
	virtual gds::Rect GetInteractRect() = 0;
	virtual uint32_t GetSubscribed() = 0;
	virtual void Focus() = 0;
	virtual void Blur() = 0;
	virtual uint32_t GetFlags() = 0;
	virtual void Enable() = 0;
	virtual void Disable() = 0;
	virtual bool IsEnabled() = 0;
	virtual void SetPosition(const gds::Rect&) = 0;
	
	virtual size_t GetZOrder(){
		return ZOrder::Default;
	}
	
	bool IsFocus();
	virtual void OnBind() {}

	virtual ~IControl() {}
};

template<typename T>
class IActionControl : public IControl{
protected:
	std::function<void(T)> actionFn;
	void RaiseEvent(const T &p){
		if(actionFn) actionFn(p);
	}
public:
	void SetAction(const std::function<void(T)> &fn){
		actionFn = fn;
	}
	
	virtual ~IActionControl() {}
};

template<>
class IActionControl<void> : public virtual IControl{
private:
	std::function<void()> actionFn;
protected:
	void RaiseActionEvent(){
		if(actionFn) actionFn();
	}
public:
	virtual void OnAction(const std::function<void()> &fn){
		actionFn = fn;
	}
	
	virtual ~IActionControl() {}
};

template<typename T, bool Q> struct const_ref{};

template<typename T> struct const_ref<T, true>{
	typedef typename std::add_lvalue_reference<typename std::add_const<T>::type>::type type;
};

template<typename T> struct const_ref<T, false>{
	typedef T type;
};

template<typename T> struct const_ref_if_nonscalar{
	typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type baseT;
	typedef typename const_ref<baseT, !std::is_scalar<baseT>::value>::type type;
};

template<typename T> 
class IValueControl : public virtual IControl{
private:
	typedef typename const_ref_if_nonscalar<T>::type constRefT;
	std::function<void(constRefT)> onChangeFn;
protected:
	void RaiseChangeEvent(){
		if(onChangeFn) onChangeFn(GetValue());
	}
public:
	virtual void OnChange(const std::function<void(constRefT)> &fn){
		onChangeFn = fn;
	}
	
	virtual T GetValue() = 0;
	
	virtual ~IValueControl() {}
};

class IDecorativeControl : public virtual IControl{
public:
	void Enable() {}
	void Disable() {}
	bool IsEnabled() { return false; }
	void Focus() {}
	void Blur() {}
	uint32_t GetFlags(){ return ControlFlags::NoFocus; }
};

}
}

#endif
