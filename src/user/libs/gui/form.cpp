#include <gui/form.hpp>
#include <gui/defaults.hpp>
#include <gds/libgds.h>
#include <wm/eventloop.hpp>
#include <gui/resizehandle.hpp>

#include <iostream>

using namespace std::placeholders;

namespace btos_api{
namespace gui{
	
gds::Surface &Form::GetSurface(){
	return *surf;
}

gds::Rect Form::GetBoundingRect(){
	return {0, 0, rect.w, rect.h};
}

void Form::Update(const gds::Rect &r){
	wm::Window::Update(r);
}

void Form::Update(){
	wm::Window::Update();
}

void Form::SetSubscribed(uint32_t subs){
	uint32_t formSubs = wm_EventType::Close | wm_EventType::Resize | wm_EventType::Move;
	wm::Window::SetSubscribed(subs | formSubs);
}

bool Form::HandleEvent(const wm_Event &e){
	if(!(GetOptions() & wm_WindowOptions::Visible)) return true;
	
	if(e.type == wm_EventType::Close){
		if(!onClose || !onClose()){
			Close();
			auto el = wm::EventLoop::GetCurrent();
			if(el) el->RemoveWindow(GetID());
		}
		return true;
	}else if(e.type == wm_EventType::Resize){
		rect.w = e.MoveResize.w;
		rect.h = e.MoveResize.h;
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		if(onResize) onResize(rect);
		if(resizeHandle){
			RemoveControl(resizeHandle);
			auto rsBtn = std::make_shared<ResizeHandle>(gds::Rect{(int32_t)rect.w - 20, (int32_t)rect.h - 20, 20, 20});
			rsBtn->OnAction([this]{
				StartResize();
			});
			resizeHandle = rsBtn;
			AddControl(rsBtn);
		}else{
			Paint();
		}
		SetSurface(*surf);
		
	}else if(e.type == wm_EventType::Move){
		rect.x = e.MoveResize.x;
		rect.y = e.MoveResize.y;
		if(onMove) onMove(rect);
	}
	
	return Container::HandleEvent(e);
}

Form::Form(const gds::Rect &r, uint32_t options, const std::string &title)
	: Window({r.x, r.y}, options, 0, gds::Surface::Wrap(GDS_NewSurface(gds_SurfaceType::Vector, r.w, r.h, 100, gds_ColourType::True), false), title),
	rect(r),
	surf(new gds::Surface(gds::Surface::Wrap(wm::Window::GetSurface().GetID(), true)))
{
	SetEventHandler(std::bind(&Form::HandleEvent, this, _1));
	if((options & wm_WindowOptions::Resizable)){
		auto rsBtn = std::make_shared<ResizeHandle>(gds::Rect{(int32_t)r.w - 20, (int32_t)r.h - 20, 20, 20});
		rsBtn->OnAction([this]{
			StartResize();
		});
		resizeHandle = rsBtn;
		AddControl(rsBtn);
	}
	Paint();
}

void Form::OnClose(std::function<bool()> oC){
	onClose = oC;
}

void Form::OnResize(std::function<void(gds::Rect)> oR){
	onResize = oR;
}

void Form::OnExpand(std::function<void()> oX){
	onExpand = oX;
}

void Form::OnMove(std::function<void(gds::Rect)> oM){
	onMove = oM;
}

}
}
