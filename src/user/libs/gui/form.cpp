#include <gui/form.hpp>
#include <gui/defaults.hpp>

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
	auto info = surface.Info();
	surface.Clear();
	surface.BeginQueue();
	auto bkg = colours::GetBackground().Fix(surface);
	surface.Box({0, 0, info.w, info.h}, bkg, bkg, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	for(auto &c : controls){
		c->Paint(surface);
	}
	surface.CommitQueue();
	Update();
}

void Form::AddControl(std::shared_ptr<IControl> control){
	controls.push_back(control);
	
	uint32_t subs = 0;
	for(auto &c : controls){
		subs |= c->GetSubscribed();
	}
	SetSubscribed(subs);
}

}
}
