#include <gui/subform.hpp>

namespace btos_api{
namespace gui{

gds::Surface &SubForm::GetSurface(){
	if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
	return *surf;
}

gds::Rect SubForm::GetBoundingRect(){
	return rect;
}

void SubForm::Update(const gds::Rect &r){
	auto rt = r;
	rt.x += rect.x;
	rt.y += rect.y;
	updateRects.push_back(rt);
}

void SubForm::Update(){
	updateRects.push_back(rect);
}

void SubForm::SetSubscribed(uint32_t s){
	subs = s;
}

SubForm::SubForm(const gds::Rect &r): rect(r) {}

EventResponse SubForm::HandleEvent(const wm_Event &e){
	bool ret = Container::HandleEvent(e);
	auto uR = updateRects;
	updateRects.clear();
	return {ret, uR};
}

void SubForm::Paint(gds::Surface &s){	
	Container::Paint();
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
}

gds::Rect SubForm::GetPaintRect(){
	return rect;
}

gds::Rect SubForm::GetInteractRect(){
	return rect;
}

uint32_t SubForm::GetSubscribed(){
	return subs;
}

void SubForm::Focus(){
	focus = true;
}

void SubForm::Blur(){
	focus = false;
}
	
}
}