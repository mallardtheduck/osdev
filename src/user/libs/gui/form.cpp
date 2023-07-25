#include <gui/form.hpp>
#include <gui/defaults.hpp>
#include <gds/libgds.h>
#include <wm/eventloop.hpp>
#include <gui/resizehandle.hpp>

#include <iostream>

using namespace std::placeholders;

namespace btos_api{
namespace gui{

const auto handleSize = 18;

struct FormImpl{
	Form *that;

	bool expanded = false;
	bool enableUpdate = true;
	gds::Rect nonExpandRect;

	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	
	std::shared_ptr<IControl> resizeHandle;
	
	uint32_t curSubs;
	
	std::function<bool()> onClose;
	std::function<void(const gds::Rect&)> onResize;
	std::function<void()> onExpand;
	std::function<void(const gds::Rect&)> onMove;
	std::function<void(const wm_Event &e)> onGlobal;
	
	bool HandleEvent(const wm_Event &e);
	void CreateResizeHandle();
	void PerformResize();
};
PIMPL_IMPL(FormImpl);
	
gds::Surface &Form::GetSurface(){
	return *im->surf;
}

gds::Rect Form::GetBoundingRect(){
	return im->rect.AtZero();
}

void Form::Update(const gds::Rect &r){
	if(im->enableUpdate) wm::Window::Update(r);
}

void Form::Update(){
	if(im->enableUpdate) wm::Window::Update();
}

void Form::SetSubscribed(uint32_t subs){
	uint32_t formSubs = wm_FrameEvents | wm_EventType::MenuSelection;
	if(im->onGlobal) formSubs |= wm_GlobalEvents;
	im->curSubs = subs;
	wm::Window::SetSubscribed(formSubs | subs);
}

bool FormImpl::HandleEvent(const wm_Event &e){
	if(!(that->GetOptions() & wm_WindowOptions::Visible) && !(e.type & wm_GlobalEvents)) return true;
	
	if(e.type == wm_EventType::Close){
		if(!onClose || !onClose()){
			that->Close();
			auto el = wm::EventLoop::GetFor(*that);
			if(el) el->RemoveWindow(that->GetID());
		}
		return true;
	}else if(e.type == wm_EventType::Hide){
		that->Hide();
		surf->Compress();
	}else if(e.type == wm_EventType::Expand){
		if(!expanded){
			auto mode = that->GetScreenMode();
			auto info = that->Info();
			auto titleSize = info.contentY;
			auto borderSize = info.contentX;
			nonExpandRect = rect;
			rect.x = 0;
			rect.y = 0;
			rect.w = mode.width - (2 * borderSize);
			rect.h = mode.height - (titleSize + borderSize);
			that->SetPosition({0, 0});
			expanded = true;
		}else{
			rect = nonExpandRect;
			that->SetPosition({rect.x, rect.y});
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
	}else if((e.type & wm_GlobalEvents)){
		if(onGlobal) onGlobal(e);
	}
	
	return that->Container::HandleEvent(e);
}

Form::Form(const gds::Rect &r, uint32_t options, const std::string &title) : 
	Window({r.x, r.y}, options, 0, gds::Surface::Wrap(GDS_NewSurface(gds_SurfaceType::Vector, r.w, r.h, 100, gds_ColourType::True), false), title),
	im(new FormImpl())
	{
		im->that = this;
		im->rect = r;
		im->surf.reset(new gds::Surface(gds::Surface::Wrap(wm::Window::GetSurface().GetID(), true)));
		SetEventHandler([&](const wm_Event &e){
			return im->HandleEvent(e);
		});
		if((options & wm_WindowOptions::Resizable)){
			im->CreateResizeHandle();
		}
		Paint();
}

void FormImpl::CreateResizeHandle(){
	auto rsBtn = std::make_shared<ResizeHandle>(gds::Rect{(int32_t)rect.w - handleSize, (int32_t)rect.h - handleSize, handleSize, handleSize});
	rsBtn->OnAction([this]{
		that->StartResize();
	});
	resizeHandle = rsBtn;
	that->AddControl(rsBtn);
}

void FormImpl::PerformResize(){
	that->Resize(rect.w, rect.h);
}

void Form::Resize(uint32_t w, uint32_t h){
	im->rect.w = w; im->rect.h = h;
	im->enableUpdate = false;
	im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
	if(im->onResize) im->onResize(im->rect);
	if(im->resizeHandle){
		im->resizeHandle->SetPosition({(int32_t)im->rect.w - handleSize, (int32_t)im->rect.h - handleSize, handleSize, handleSize});
	}
	Paint({0, 0, w, h});
	SetSurface(*im->surf);
	im->enableUpdate = true;
}

void Form::OnClose(std::function<bool()> oC){
	im->onClose = oC;
}

void Form::OnResize(std::function<void(const gds::Rect &)> oR){
	im->onResize = oR;
}

void Form::OnExpand(std::function<void()> oX){
	im->onExpand = oX;
}

void Form::OnMove(std::function<void(const gds::Rect &)> oM){
	im->onMove = oM;
}

void Form::OnGlobal(std::function<void(const wm_Event &e)> oG){
	im->onGlobal = oG;
	SetSubscribed(im->curSubs);
}

}
}
