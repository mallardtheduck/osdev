#include <gui/eventresponse.hpp>

#include <iostream>

namespace btos_api{
namespace gui{

EventResponse::EventResponse(bool fP, const std::vector<gds::Rect> &rR) : finishedProcessing(fP), redrawRects(gds::TileRects(rR)){
}

bool EventResponse::IsFinishedProcessing(){
	return finishedProcessing;
}

std::vector<gds::Rect> EventResponse::GetRedrawRects(){
	if(!rectTiled){
		redrawRects = gds::TileRects(redrawRects);
		rectTiled = true;
	}
	return redrawRects;
}

void EventResponse::AddRedrawRect(const gds::Rect &r){
	redrawRects.push_back(r);
	if(redrawRects.size() > 1) rectTiled = false;
}

}
}