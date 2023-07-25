#ifndef _CONTAINER_HPP
#define _CONTAINER_HPP

#include <memory>
#include <vector>

#include <gds/surface.hpp>
#include <wm/wm.h>

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

class IControl;

struct ContainerImpl;
PIMPL_CLASS(ContainerImpl);

class Container{
private:
	btos::pimpl_ptr<ContainerImpl> impl;
	friend struct ContainerImpl;

	virtual gds::Surface &GetSurface() = 0;
	virtual gds::Rect GetBoundingRect() = 0;
	
	virtual void Update(const gds::Rect &r) = 0;
	virtual void Update() = 0;
	virtual void SetSubscribed(uint32_t subs) = 0;

	virtual bool OnLastControlFocus(bool /*reverse*/) {return false;}
protected:
	bool HandleEvent(const wm_Event &e);

public:
	Container();

	virtual void Paint(const std::vector<gds::Rect> &rects);
	void Paint(const gds::Rect &r = gds::Rect());

	void AddControl(std::shared_ptr<IControl> control);
	void AddControls(std::vector<std::shared_ptr<IControl>> controls);
	void RemoveControl(std::shared_ptr<IControl> control);
	void MoveControl(std::shared_ptr<IControl> control, gds::Rect newpos);
	
	void BindControl(IControl &control);
	
	std::shared_ptr<IControl> &GetFocus();
	void SetFocus(std::shared_ptr<IControl> ctrl);
	void FocusNext(bool reverse);
	
	~Container() {}
};  

}
}

#endif
