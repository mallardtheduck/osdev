#include <gui/form.hpp>

using namespace std::placeholders;

namespace btos_api{
namespace gui{

Form::Form(const gds::Rect &r, uint32_t options, const std::string &title)
	: Window({r.x, r.y}, options, 0, gds::Surface(gds_SurfaceType::Vector, r.w, r.h, 100, gds_ColourType::True), title){
	SetEventHandler(std::bind(&Form::HandleEvent, this, _1));
}

bool Form::HandleEvent(const wm_Event &e){
	if(focus && (e.type | wm_KeyboardEvents) && (focus->GetSubscribed() | e.type)){
		if(focus->HandleEvent(e)) return true;
	}
	
	if((e.type | wm_PointerEvents)){
		for(auto &c : controls){
			if((c->GetSubscribed() | e.type) && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetRect())){
				if(c->HandleEvent(e)){
					focus = c;
					c->Focus();
					return true;
				}
			}
		}
	}
	
	return true;
}

void Form::Paint(const gds::Rect &){
	auto surface = GetSurface();
	surface.Clear();
	for(auto &c : controls){
		c->Paint(surface);
	}
}

void Form::AddControl(std::shared_ptr<IControl> control){
	controls.push_back(control);
}

}
}