#ifndef _EVENTRESPONSE_HPP
#define _EVENTRESPONSE_HPP

#include <vector>
#include <gds/geom.hpp>

namespace btos_api{
namespace gui{

class EventResponse{
private:
	bool finishedProcessing = false;
	std::vector<gds::Rect> redrawRects;
	bool rectTiled = true;
public:
	EventResponse(bool fP = false, const std::vector<gds::Rect> &rR = {});
	EventResponse(bool fP, gds::Rect r) : EventResponse(fP, std::vector<gds::Rect>{r}) {}

	bool IsFinishedProcessing();
	std::vector<gds::Rect> GetRedrawRects();
	
	void AddRedrawRect(const gds::Rect &r);
};

}
}

#endif