#include <gui/eventresponse.hpp>

#include <iostream>

namespace btos_api{
namespace gui{

EventResponse::EventResponse(bool fP) : finishedProcessing(fP){
}

bool EventResponse::IsFinishedProcessing(){
	return finishedProcessing;
}

}
}