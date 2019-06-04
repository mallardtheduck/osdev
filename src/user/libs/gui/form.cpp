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
	if(enableUpdate) wm::Window::Update(r);
}

void Form::Update(){
	if(enableUpdate) wm::Window::Update();
}

void Form::SetSubscribed(uint32_t subs){
	uint32_t formSubs = wm_FrameEvents;
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
	}else if(e.type == wm_EventType::Expand){
		if(!expanded){
			auto mode = GetScreenMode();
			auto info = Info();
			auto titleSize = info.contentY;
			auto borderSize = info.contentX;
			nonExpandRect = rect;
			rect.x = 0;
			rect.y = 0;
			rect.w = mode.width - (2 * borderSize);
			rect.h = mode.height - (titleSize + borderSize);
			SetPosition({0, 0});
			expanded = true;
		}else{
			rect = nonExpandRect;
			SetPosition({rect.x, rect.y});
			expanded = false;
		}
		PerformResize();
		if(onExpand) onExpand();
	}else if(e.type == wm_EventType::Resize){
		rect.w = e.MoveResize.w;
		rect.h = e.MoveResize.h;
		PerformResize();
	}else if(e.type == wm_EventType::Move){
		rect.x = e.MoveResize.x;
		rect.y = e.MoveResize.y;
		if(expanded){
			rect.w = nonExpandRect.w;
			rect.h = nonExpandRect.h;
			expanded = false;
			PerformResize();
		}
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
		CreateResizeHandle();
	}
	Paint();
}

void Form::CreateResizeHandle(){
	auto rsBtn = std::make_shared<ResizeHandle>(gds::Rect{(int32_t)rect.w - handleSize, (int32_t)rect.h - handleSize, handleSize, handleSize});
	rsBtn->OnAction([this]{
		StartResize();
	});
	resizeHandle = rsBtn;
	AddControl(rsBtn);
}

void Form::PerformResize(){
	enableUpdate = false;
	surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
	if(onResize) onResize(rect);
	if(resizeHandle){
		resizeHandle->SetPosition({(int32_t)rect.w - handleSize, (int32_t)rect.h - handleSize, handleSize, handleSize});
	}
	Paint();
	SetSurface(*surf);
	enableUpdate = true;
}

void Form::OnClose(std::function<bool()> oC){
	onClose = oC;
}

void Form::OnResize(std::function<void(const gds::Rect &)> oR){
	onResize = oR;
}

void Form::OnExpand(std::function<void()> oX){
	onExpand = oX;
}

void Form::OnMove(std::function<void(const gds::Rect &)> oM){
	onMove = oM;
}

}
}
