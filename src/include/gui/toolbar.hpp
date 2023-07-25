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
	void SetPosition(const gds::Rect&) override {}
	
	virtual ~IToolbarControlBase() {}
};

class IToolbarControl : public IToolbarControlBase{
public:
	void Focus() override {}
	void Blur() override {}
	uint32_t GetFlags() override { return ControlFlags::NoFocus; }
	
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
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void Focus() override;
	void Blur() override;
	uint32_t GetFlags() override;
	void Enable() override;
	void Disable() override;
	bool IsEnabled() override;
	void SetPosition(const gds::Rect&) override {}
	
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
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void Enable() override;
	void Disable() override;
	bool IsEnabled() override;
	
	uint32_t GetWidth() override;
};

class ToolbarSpacer : public IDecorativeToolbarControl{
private:
public:
	ToolbarSpacer();
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	
	uint32_t GetWidth() override;
};

}
}

#endif