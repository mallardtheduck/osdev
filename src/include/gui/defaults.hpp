#ifndef _DEFAULTS_HPP
#define _DEFAULTS_HPP

#include <gds/geom.hpp>

namespace btos_api{
namespace gui{
	
namespace colours{
	namespace constants{
		extern gds::Colour Black;
		extern gds::Colour Blue;
		extern gds::Colour Green;
		extern gds::Colour Cyan;
		extern gds::Colour Red;
		extern gds::Colour Purple;
		extern gds::Colour Orange;
		extern gds::Colour Grey;
		extern gds::Colour DarkGrey;
		extern gds::Colour LightBlue;
		extern gds::Colour LightGreen;
		extern gds::Colour LightCyan;
		extern gds::Colour Pink;
		extern gds::Colour Magenta;
		extern gds::Colour Yellow;
		extern gds::Colour White;
	}
	
	gds::Colour GetBackground();
	gds::Colour GetBorder();
	
	gds::Colour GetButtonColour();
	gds::Colour GetButtonHiLight();
	gds::Colour GetButtonLowLight();
	gds::Colour GetButtonText();
	gds::Colour GetLabelText();
}

namespace fonts{
	gds::Font GetButtonFont();
	uint32_t GetButtonTextSize();
	
	gds::Font GetLabelFont();
	uint32_t GetLabelTextSize();
}

}
}

#endif
