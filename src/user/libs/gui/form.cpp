#include <gui/form.hpp>
#include <gui/defaults.hpp>
#include <gds/libgds.h>

#include <iostream>

using namespace std::placeholders;

namespace btos_api{
namespace gui{

Form::Form(const gds::Rect &r, uint32_t options, const std::string &title)
	: Window({r.x, r.y}, options, 0, gds::Surface::Wrap(GDS_NewSurface(gds_SurfaceType::Vector, r.w, r.h, 100, gds_ColourType::True), false), title){
	SetEventHandler(std::bind(&Form::HandleEvent, this, _1));
	Paint();
}

bool Form::HandleEvent(const wm_Event &e){
	EventResponse response;
	if(focus && (e.type & wm_KeyboardEvents) && (focus->GetSubscribed() & e.type)){
		response = focus->HandleEvent(e);
	}
	
	if(!response.IsFinishedProcessing() && (e.type | wm_PointerEvents)){
		
		if(e.type == wm_EventType::PointerMove){
			if(mouseOver && !gds::InRect(e.Pointer.x, e.Pointer.y, mouseOver->GetInteractRect())){
				auto leaveEvt = e;
				leaveEvt.type = wm_EventType::PointerLeave;
				HandleEvent(leaveEvt);
				mouseOver.reset();
			}
		}
		
		if(mouseOver && e.type == wm_EventType::PointerLeave){
			response = mouseOver->HandleEvent(e);
		}
		
		if(!response.IsFinishedProcessing()){
			for(auto &c : controls){
				if(e.type == wm_EventType::PointerMove && mouseOver != c && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetInteractRect()) && (c->GetSubscribed() & wm_EventType::PointerEnter)){
					auto enterEvt = e;
					enterEvt.type = wm_EventType::PointerEnter;
					HandleEvent(enterEvt);
					mouseOver = c;
				}
				if((c->GetSubscribed() & e.type) && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetInteractRect())){
					response = c->HandleEvent(e);
					if(response.IsFinishedProcessing()){
						if(e.type != wm_EventType::PointerMove) focus = c;
						c->Focus();
						break;
					}
				}
			}
		}
	}
	
	Paint(response.GetRedrawRects());
	
	return true;
}

void Form::Paint(const std::vector<gds::Rect> &rects){
	if(rects.empty()) return;
	
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
	
	for(auto &r : rects){
		if(r.w && r.h) Update(r);
		else{
			Update();
			break;
		}
	}
}

void Form::Paint(const gds::Rect &r){
	Paint(std::vector<gds::Rect>{r});
}

void Form::AddControl(std::shared_ptr<IControl> control){
	controls.push_back(control);
	
	uint32_t subs = 0;
	for(auto &c : controls){
		subs |= c->GetSubscribed();
	}
	if(subs & (wm_EventType::PointerEnter | wm_EventType::PointerLeave)) subs |= wm_EventType::PointerMove;
	
	SetSubscribed(subs);
	
	Paint(control->GetPaintRect());
}

}
}
