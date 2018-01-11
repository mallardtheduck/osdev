#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include <wm/libwm.h>
#include <memory>
#include <gds/surface.hpp>

class Sprite : public std::enable_shared_from_this<Sprite>{
protected:
	std::shared_ptr<gds::Surface> surf;
	Sprite(std::shared_ptr<gds::Surface> s) : surf(s) {}
public:
	virtual void Input(const wm_Event &/*e*/) {}
	virtual bool Step() {return false;}
	virtual void Draw() {}
	virtual gds::Rect GetBoundingRect() {return gds::Rect();}
	virtual uint32_t GetZOrder() {return 0;}
	
	virtual ~Sprite(){}
};

#endif
