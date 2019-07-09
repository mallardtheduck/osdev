#ifndef _EVENTRESPONSE_HPP
#define _EVENTRESPONSE_HPP

#include <vector>
#include <gds/geom.hpp>

namespace btos_api{
namespace gui{

class EventResponse{
private:
	bool finishedProcessing = false;
public:
	EventResponse(bool fP = false);

	bool IsFinishedProcessing();
};

}
}

#endif