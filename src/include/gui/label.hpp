#ifndef _LABEL_HPP
#define _LABEL_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

class LabelImpl;
PIMPL_CLASS(LabelImpl);

class Label : public IDecorativeControl{
public:
	enum class Justification{
		Left, Center, Right	
	};

private:
	btos::pimpl_ptr<LabelImpl> im;
public:
	Label(const gds::Rect &r, const std::string &t, Justification just = Justification::Center);
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void SetPosition(const gds::Rect&) override;
	
	void SetText(const std::string &t);
};

}
}

#endif
