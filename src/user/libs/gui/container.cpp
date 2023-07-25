#include <gui/container.hpp>
#include <gui/defaults.hpp>
#include <wm/libwm.h>
#include <dev/keyboard.h>

#include <algorithm>

namespace btos_api{
namespace gui{

struct ContainerImpl{
	std::vector<std::shared_ptr<IControl>> controls;
	std::shared_ptr<IControl> focus;
	std::shared_ptr<IControl> mouseOver;
	std::vector<gds::Rect> paintQueue;
	bool queuePaint = false;
	
	std::shared_ptr<IControl> FindNextFocus(bool reverse, Container *that);
	
	void ZSortControls();
};

PIMPL_IMPL(ContainerImpl);

void IControl::Paint(const gds::Rect &rect){
	if(paintFn) paintFn(rect);
}

void IControl::BindToParent(IControl &ctrl){
	if(bindFn) bindFn(ctrl);
}

bool IControl::IsFocus(){
	if(isFocusFn) return isFocusFn(this);
	else return false;
}

void IControl::FocusNext(bool reverse){
	if(focusNextFn) focusNextFn(reverse);
}

gds::Rect IControl::GetContainerRect(){
	if(getRectFn) return getRectFn();
	else return {};
}

void IControl::AddToParent(std::shared_ptr<IControl> ctrl){
	if(addControlFn) addControlFn(ctrl);
}

void IControl::RemoveFromParent(std::shared_ptr<IControl> ctrl){
	if(removeControlFn) removeControlFn(ctrl);	
}

template<typename T> static std::shared_ptr<IControl> FNFSearch(std::shared_ptr<IControl> focus, T begin, T end, std::function<bool()> onLastControl){
	auto i = begin;
	bool found = false;
	while(true){
		if(found && !((*i)->GetFlags() & ControlFlags::NoFocus) && (*i)->IsEnabled()) return *i;
		if(found && *i == focus) return focus;
		if(*i == focus) found = true;
		++i;
		if(i == end){
			if(onLastControl()) return nullptr;
			i = begin;
		}
	}
}

std::shared_ptr<IControl> ContainerImpl::FindNextFocus(bool reverse, Container *that){
	if(reverse) return FNFSearch(focus, controls.rbegin(), controls.rend(), [that, reverse]{return that->OnLastControlFocus(reverse);});
	else return FNFSearch(focus, controls.begin(), controls.end(), [that, reverse]{return that->OnLastControlFocus(reverse);});
}

void ContainerImpl::ZSortControls(){
	std::sort(controls.begin(), controls.end(), [](const std::shared_ptr<IControl> &a, const std::shared_ptr<IControl> &b){
		return a->GetZOrder() < b->GetZOrder();
	});
}

Container::Container() : impl(new ContainerImpl()) {}

bool Container::HandleEvent(const wm_Event &evt){
	impl->queuePaint = true;
	auto ctrlsCopy = impl->controls;
	EventResponse response;
	if(impl->focus && impl->focus->IsEnabled() && (evt.type & wm_KeyboardEvents) && (impl->focus->GetSubscribed() & evt.type)){
		response = impl->focus->HandleEvent(evt);
	}
	
	if(!ctrlsCopy.empty() && !response.IsFinishedProcessing() && evt.type == wm_EventType::Keyboard){
		int16_t code = KB_code(evt.Key.code);
		if(!(code & KeyFlags::NonASCII) && KB_char(evt.Key.code) == '\t'){
			if(!impl->focus){
				impl->focus = *ctrlsCopy.begin();
				if(impl->focus->GetFlags() & ControlFlags::NoFocus) impl->focus = impl->FindNextFocus(false, this);
				if(impl->focus) impl->focus->Focus();
			}else{
				impl->focus->Blur();
				impl->focus = impl->FindNextFocus(evt.Key.code & KeyFlags::Shift, this);
				if(impl->focus) impl->focus->Focus();
			}
		}
	}
	
	if(!response.IsFinishedProcessing() && (evt.type & wm_PointerEvents)){
		auto e = evt;
		auto br = GetBoundingRect();
		e.Pointer.x -= br.x;
		e.Pointer.y -= br.y;
		
		if(e.type == wm_EventType::PointerMove){
			if(impl->mouseOver && !gds::InRect(e.Pointer.x, e.Pointer.y, impl->mouseOver->GetInteractRect())){
				auto leaveEvt = e;
				leaveEvt.type = wm_EventType::PointerLeave;
				HandleEvent(leaveEvt);
				impl->mouseOver.reset();
			}
		}
		
		if(impl->mouseOver && impl->mouseOver->IsEnabled() && e.type == wm_EventType::PointerLeave){
			response = impl->mouseOver->HandleEvent(e);
		}
		
		if(!response.IsFinishedProcessing()){
			for(auto i = ctrlsCopy.rbegin(); i != ctrlsCopy.rend(); ++i){
				auto &c = *i;
				if(!c->IsEnabled()) continue;
				if(e.type == wm_EventType::PointerMove && impl->mouseOver != c && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetInteractRect()) && (c->GetSubscribed() & wm_EventType::PointerEnter)){
					impl->mouseOver = c;
					auto enterEvt = evt;
					enterEvt.type = wm_EventType::PointerEnter;
					HandleEvent(enterEvt);
				}
				if((c->GetSubscribed() & e.type) && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetInteractRect())){
					response = c->HandleEvent(e);
					if(response.IsFinishedProcessing()){
						if(e.type != wm_EventType::PointerMove && e.type != wm_EventType::PointerEnter && e.type != wm_EventType::PointerLeave){
							if(c != impl->focus && !(c->GetFlags() & ControlFlags::NoFocus)){
								if(impl->focus){
									impl->focus->Blur();
								}
								impl->focus = c;
								impl->focus->Focus();
							}
						}
						break;
					}
				}
			}
		}
	}
	impl->queuePaint = false;
	Paint(/*gds::TileRects(*/impl->paintQueue/*)*/);
	impl->paintQueue.clear();
	return true;
}
	
void Container::Paint(const std::vector<gds::Rect> &rects){
	if(rects.empty()) return;
	if(impl->queuePaint){ 
		for(auto &r : rects) impl->paintQueue.push_back(r);
		return;
	}
	
	auto &surface = GetSurface();
	auto br = GetBoundingRect();
	surface.Clear();
	surface.BeginQueue();
	auto bkg = colours::GetBackground().Fix(surface);
	surface.Box({0, 0, br.w, br.h}, bkg, bkg, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	for(auto &c : impl->controls){
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
	WM_Sync();
}

void Container::Paint(const gds::Rect &r){
	Paint(std::vector<gds::Rect>{r});
}

void Container::AddControl(std::shared_ptr<IControl> control){
	AddControls({control});
}

void Container::AddControls(std::vector<std::shared_ptr<IControl>> ncontrols){
	for(auto &c : ncontrols){
		if(std::find(impl->controls.begin(), impl->controls.end(), c) == impl->controls.end()){
			impl->controls.push_back(c);
			BindControl(*c);
		}
	}
	
	uint32_t subs = wm_EventType::Keyboard;
	for(auto &c : impl->controls)	subs |= c->GetSubscribed();
	
	if(subs & (wm_EventType::PointerEnter | wm_EventType::PointerLeave)) subs |= wm_EventType::PointerMove;
	impl->ZSortControls();
	SetSubscribed(subs);
	Paint();
}

void Container::RemoveControl(std::shared_ptr<IControl> ctrl){
	impl->controls.erase(std::remove(impl->controls.begin(), impl->controls.end(), ctrl), impl->controls.end());
	ctrl->paintFn = nullptr;
	ctrl->bindFn = nullptr;
	ctrl->isFocusFn = nullptr;
	ctrl->focusNextFn = nullptr;
	ctrl->getRectFn = nullptr;
	ctrl->addControlFn = nullptr;
	ctrl->removeControlFn = nullptr;
	Paint();
}

void Container::MoveControl(std::shared_ptr<IControl> control, gds::Rect newpos){
	if(control && std::find(impl->controls.begin(), impl->controls.end(), control) != impl->controls.end()){
		auto oldpos = control->GetPaintRect();
		control->SetPosition(newpos);
		Paint({oldpos, newpos});
	}else{
		control->SetPosition(newpos);
	}
}

void Container::BindControl(IControl &control){
	control.paintFn = [this] (const gds::Rect &rect) -> void {Paint(rect);};
	control.bindFn = [this] (IControl &ctrl) -> void {BindControl(ctrl);};
	control.isFocusFn = [this] (const IControl *ctrl) -> bool {return GetFocus().get() == ctrl;};
	control.focusNextFn = [this] (bool reverse) -> void {FocusNext(reverse);};
	control.getRectFn = [this]() -> gds::Rect {return GetBoundingRect();};
	control.addControlFn = [this](std::shared_ptr<IControl> ctrl) -> void {AddControl(ctrl);};
	control.removeControlFn = [this](std::shared_ptr<IControl> ctrl) -> void {RemoveControl(ctrl);};
	control.OnBind();
}

std::shared_ptr<IControl> &Container::GetFocus(){
	return impl->focus;
}

void Container::SetFocus(std::shared_ptr<IControl> ctrl){
	if(impl->focus == ctrl) return;
	bool found = false;
	for(auto &c : impl->controls){
		if(c == ctrl){
			found = true;
			break;
		}
	}
	if(found){
		if(impl->focus) impl->focus->Blur();
		impl->focus = ctrl;
		impl->focus->Focus();
	}
}

void Container::FocusNext(bool reverse){
	if(!impl->focus){
		impl->focus = *impl->controls.begin();
		if(impl->focus->GetFlags() & ControlFlags::NoFocus) impl->focus = impl->FindNextFocus(false, this);
		if(impl->focus) impl->focus->Focus();
	}else{
		impl->focus->Blur();
		impl->focus = impl->FindNextFocus(reverse, this);
		if(impl->focus) impl->focus->Focus();
	}
}

}
}
