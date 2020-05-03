#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include <wm/libwm.h>
#include <memory>
#include <gds/surface.hpp>

class Sprite : public std::enable_shared_from_this<Sprite>{
protected:
	std::shared_ptr<btos_api::gds::Surface> surf;
	Sprite(std::shared_ptr<btos_api::gds::Surface> s) : surf(s) {}
public:
	virtual void Input(const wm_Event &/*e*/) {}
	virtual bool Step() {return false;}
	virtual void Draw() {}
	virtual btos_api::gds::Rect GetBoundingRect() {return btos_api::gds::Rect();}
	virtual uint32_t GetZOrder() {return 0;}
	
	virtual ~Sprite(){}
};

#endif
