#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include <wm/libwm.h>
#include <memory>

class Sprite : public std::enable_shared_from_this<Sprite>{
public:
	virtual void Input(const wm_Event &/*e*/) {}
	virtual bool Step() {return false;}
	virtual void Draw() {}
	virtual wm_Rect GetBoundingRect() {return wm_Rect();}
	virtual uint32_t GetZOrder() {return 0;}
	
	virtual ~Sprite(){}
};

#endif