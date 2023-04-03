#ifndef _TOOLBAR_HPP
#define _TOOLBAR_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

class IToolbarControlBase : public virtual IControl{
protected:
	gds::Rect rect;
	uint32_t margin;
	uint32_t size;
	
	friend class Toolbar;
public:
	virtual uint32_t GetWidth() = 0;
	void SetPosition(const gds::Rect&){}
	
	virtual ~IToolbarControlBase() {}
};

class IToolbarControl : public IToolbarControlBase{
public:
	void Focus() {}
	void Blur() {}
	uint32_t GetFlags(){ return ControlFlags::NoFocus; }
	
	virtual ~IToolbarControl() {}
};

class IDecorativeToolbarControl : public IToolbarControlBase, public IDecorativeControl{
public:
	virtual ~IDecorativeToolbarControl() {}
};

class ToolbarImpl;
PIMPL_CLASS(ToolbarImpl);

class Toolbar : public IControl{
private:
	btos::pimpl_ptr<ToolbarImpl> im;
public:
	Toolbar(uint32_t size = 24);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	void Enable();
	void Disable();
	bool IsEnabled();
	void SetPosition(const gds::Rect&) {}
	
	std::vector<std::shared_ptr<IToolbarControlBase>> &Controls();
	void Refresh();
	
	void OnBind();
};

struct ToolbarButtonImpl;
PIMPL_CLASS(ToolbarButtonImpl);

class ToolbarButton : public IActionControl<void>, public IToolbarControl{
private:
	btos::pimpl_ptr<ToolbarButtonImpl> im;
public:
	ToolbarButton(std::shared_ptr<gds::Surface> icon = nullptr, const std::string &label = "");
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Enable();
	void Disable();
	bool IsEnabled();
	
	uint32_t GetWidth();
};

class ToolbarSpacer : public IDecorativeToolbarControl{
private:
public:
	ToolbarSpacer();
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	
	uint32_t GetWidth();
};

}
}

#endif