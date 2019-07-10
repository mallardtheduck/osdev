#ifndef _LABEL_HPP
#define _LABEL_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Label : public IDecorativeControl{
public:
	enum class Justification{
		Left, Center, Right	
	};

private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	
	Justification just;
public:
	Label(const gds::Rect &r, const std::string &t, Justification just = Justification::Center);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void SetPosition(const gds::Rect&);
	
	void SetText(const std::string &t);
};

}
}

#endif
