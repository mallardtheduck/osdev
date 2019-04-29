#ifndef _CONTAINER_HPP
#define _CONTAINER_HPP

#include <memory>
#include <vector>

#include <gds/surface.hpp>
#include <wm/wm.h>

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class IControl;

class Container{
private:
	std::vector<std::shared_ptr<IControl>> controls;
	std::shared_ptr<IControl> focus;
	std::shared_ptr<IControl> mouseOver;
	std::vector<gds::Rect> paintQueue;
	bool queuePaint = false;
	
	virtual gds::Surface &GetSurface() = 0;
	virtual gds::Rect GetBoundingRect() = 0;
	
	virtual void Update(const gds::Rect &r) = 0;
	virtual void Update() = 0;
	virtual void SetSubscribed(uint32_t subs) = 0;
	
	std::shared_ptr<IControl> FindNextFocus(bool reverse);
	virtual bool OnLastControlFocus(bool /*reverse*/) {return false;}
protected:
	bool HandleEvent(const wm_Event &e);

public:
	virtual void Paint(const std::vector<gds::Rect> &rects);
	void Paint(const gds::Rect &r = gds::Rect());

	void AddControl(std::shared_ptr<IControl> control);
	void AddControls(std::vector<std::shared_ptr<IControl>> controls);
	
	void BindControl(IControl &control);
	
	std::shared_ptr<IControl> &GetFocus();
	void FocusNext(bool reverse);
	
	~Container() {}
};  

}
}

#endif
