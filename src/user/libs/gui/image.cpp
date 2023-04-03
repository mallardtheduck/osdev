#include <gui/image.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{

struct ImageImpl{
	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	std::shared_ptr<gds::Surface> img;
};
PIMPL_IMPL(ImageImpl);

Image::Image(const gds::Rect &r, std::shared_ptr<gds::Surface> i) : im(new ImageImpl()){
	im->rect = r;
	im->img = i;
}
	
EventResponse Image::HandleEvent(const wm_Event&){
	return {false};
}

void Image::Paint(gds::Surface &s){
	if(!im->surf){
		im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		auto info = im->img->Info();
		im->surf->Blit(*im->img, {0, 0, info.w, info.h}, {0, 0, info.w, info.h});
		im->surf->Compress();
	}
	
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
}

gds::Rect Image::GetPaintRect(){
	return im->rect;
}

gds::Rect Image::GetInteractRect(){
	return {0, 0, 0, 0};
}

uint32_t Image::GetSubscribed(){
	return 0;
}

void Image::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->surf.reset();
}

}
}
