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
	gds::Colour GetButtonFocus();
	
	gds::Colour GetLabelText();
	
	gds::Colour GetTextBoxText();
	gds::Colour GetTextBoxHiLight();
	gds::Colour GetTextBoxLowLight();
	gds::Colour GetTextCursor();
	
	gds::Colour GetSliderLineHiLight();
	gds::Colour GetSliderLineLowLight();
	gds::Colour GetSliderColour();
	gds::Colour GetSliderFocus();
	gds::Colour GetSliderTick();
	
	gds::Colour GetCheckboxText();
	gds::Colour GetCheckboxHiLight();
	gds::Colour GetCheckboxLowLight();
	gds::Colour GetCheckboxCheck();
	gds::Colour GetCheckboxFocus();
	
	gds::Colour GetRadioButtonText();
	gds::Colour GetRadioButtonHiLight();
	gds::Colour GetRadioButtonLowLight();
	gds::Colour GetRadioButtonCheck();
	gds::Colour GetRadioButtonFocus();
	
	gds::Colour GetScrollbarBackground();
	gds::Colour GetScrollbarButton();
	gds::Colour GetScrollbarHiLight();
	gds::Colour GetScrollbarLowLight();
	gds::Colour GetScrollbarArrow();
	gds::Colour GetScrollbarFocus();
}

namespace fonts{
	gds::Font GetButtonFont();
	uint32_t GetButtonTextSize();
	
	gds::Font GetLabelFont();
	uint32_t GetLabelTextSize();
	
	gds::Font GetTextBoxFont();
	uint32_t GetTextBoxFontSize();
	
	gds::Font GetCheckboxFont();
	uint32_t GetCheckboxTextSize();
	
	gds::Font GetRadioButtonFont();
	uint32_t GetRadioButtonTextSize();
}

}
}

#endif
