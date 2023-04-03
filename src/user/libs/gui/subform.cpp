#include <gui/subform.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{

struct SubFormImpl{
	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	
	uint32_t subs;
	std::vector<gds::Rect> updateRects;
	
	bool enabled = true;
};
PIMPL_IMPL(SubFormImpl);

gds::Surface &SubForm::GetSurface(){
	if(!im->surf) im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
	return *im->surf;
}

gds::Rect SubForm::GetBoundingRect(){
	return im->rect;
}

void SubForm::Update(const gds::Rect &r){
	auto rt = r;
	rt.x += im->rect.x;
	rt.y += im->rect.y;
	im->updateRects.push_back(rt);
}

void SubForm::Update(){
	im->updateRects.push_back(im->rect);
}

void SubForm::SetSubscribed(uint32_t s){
	im->subs = s;
}

bool SubForm::OnLastControlFocus(bool reverse){
	IControl::FocusNext(reverse);
	return !IControl::IsFocus();
}

SubForm::SubForm(const gds::Rect &r): im(new SubFormImpl()){
	im->rect = r;
}

EventResponse SubForm::HandleEvent(const wm_Event &e){
	return {Container::HandleEvent(e)};
}


//IControl::Paint
void SubForm::Paint(gds::Surface &s){   
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect SubForm::GetPaintRect(){
	return im->rect;
}

gds::Rect SubForm::GetInteractRect(){
	return im->rect;
}

uint32_t SubForm::GetSubscribed(){
	return im->subs;
}

void SubForm::Focus(){
	auto fcs = GetFocus();
	if(fcs) fcs->Focus();
	else Container::FocusNext(false);
}

void SubForm::Blur(){
	auto fcs = GetFocus();
	if(fcs) fcs->Blur();
}

uint32_t SubForm::GetFlags(){
	return 0;
}

//Container::Paint
void SubForm::Paint(const std::vector<gds::Rect> &rects){
	Container::Paint(rects);
	for(const auto &uR : im->updateRects) IControl::Paint(uR);
	im->updateRects.clear();
}

void SubForm::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void SubForm::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool SubForm::IsEnabled(){
	return im->enabled;
}

void SubForm::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->surf.reset();
}
	
}
}
