#include <gui/image.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{

Image::Image(const gds::Rect &r, std::shared_ptr<gds::Surface> i) : rect(r), img(i) {}
	
EventResponse Image::HandleEvent(const wm_Event&){
	return {false};
}

void Image::Paint(gds::Surface &s){
	if(!surf){
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		auto bkgCol = colours::GetBackground().Fix(*surf);
		
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		auto info = img->Info();
		surf->Blit(*img, {0, 0, info.w, info.h}, {0, 0, info.w, info.h});
		surf->Compress();
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
}

gds::Rect Image::GetPaintRect(){
	return rect;
}

gds::Rect Image::GetInteractRect(){
	return {0, 0, 0, 0};
}

uint32_t Image::GetSubscribed(){
	return 0;
}

void Image::SetPosition(const gds::Rect &r){
	rect = r;
	surf.reset();
}

}
}
