#include <gui/testcontrol.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{

TestControl::TestControl(const gds::Rect &r) : rect(r) {}
	
EventResponse TestControl::HandleEvent(const wm_Event &e){
	if(onEvent) return {onEvent(e)};
	else return {false};
}

void TestControl::Paint(gds::Surface &s){
	auto colour = colours::constants::Magenta.Fix(s);
	
	s.Box(rect, colour, colour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

gds::Rect TestControl::GetPaintRect(){
	return rect;
}

gds::Rect TestControl::GetInteractRect(){
	return rect;
}

uint32_t TestControl::GetSubscribed(){
	return (uint32_t)-1;
}

void TestControl::Focus() {}
void TestControl::Blur() {}

uint32_t TestControl::GetFlags(){
	return ControlFlags::NoFocus;
}

void TestControl::OnEvent(const std::function<bool(const wm_Event&)> &oE){
	onEvent = oE;
}

void TestControl::Enable(){}

void TestControl::Disable(){}

bool TestControl::IsEnabled(){
	return true;
}

void TestControl::SetPosition(const gds::Rect &r){
	rect = r;
}

}
}
