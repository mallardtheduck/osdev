#ifndef _DEFAULTS_HPP
#define _DEFAULTS_HPP

#include <gds/geom.hpp>

namespace btos_api{
namespace gui{
	
namespace colours{
	namespace constants{
		extern const gds::Colour Black;
		extern const gds::Colour Blue;
		extern const gds::Colour Green;
		extern const gds::Colour Cyan;
		extern const gds::Colour Red;
		extern const gds::Colour Purple;
		extern const gds::Colour Orange;
		extern const gds::Colour Grey;
		extern const gds::Colour DarkGrey;
		extern const gds::Colour LightBlue;
		extern const gds::Colour LightGreen;
		extern const gds::Colour LightCyan;
		extern const gds::Colour Pink;
		extern const gds::Colour Magenta;
		extern const gds::Colour Yellow;
		extern const gds::Colour White;
	}
	
	gds::Colour GetBackground();
	gds::Colour GetBorder();
	gds::Colour GetSelection();
	gds::Colour GetSelectionFocus();
	gds::Colour GetDisabledCast();
	
	gds::Colour GetButtonColour();
	gds::Colour GetButtonHiLight();
	gds::Colour GetButtonLowLight();
	gds::Colour GetButtonText();
	gds::Colour GetButtonFocus();
	
	gds::Colour GetImageButtonColour();
	gds::Colour GetImageButtonHiLight();
	gds::Colour GetImageButtonLowLight();
	gds::Colour GetImageButtonFocus();
	
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
	
	gds::Colour GetTextAreaText();
	gds::Colour GetTextAreaHiLight();
	gds::Colour GetTextAreaLowLight();
	
	gds::Colour GetGroupBoxText();
	
	gds::Colour GetListBoxText();
	gds::Colour GetListBoxHiLight();
	gds::Colour GetListBoxLowLight();
	
	gds::Colour GetDetailListText();
	gds::Colour GetDetailListHiLight();
	gds::Colour GetDetailListLowLight();
	gds::Colour GetDetailListHeader();
	
	gds::Colour GetIconViewText();
	gds::Colour GetIconViewHiLight();
	gds::Colour GetIconViewLowLight();
}

namespace fonts{
	gds::Font GetButtonFont();
	uint32_t GetButtonTextSize();
	
	gds::Font GetLabelFont();
	uint32_t GetLabelTextSize();
	
	gds::Font GetTextBoxFont();
	uint32_t GetTextBoxTextSize();
	
	gds::Font GetCheckboxFont();
	uint32_t GetCheckboxTextSize();
	
	gds::Font GetRadioButtonFont();
	uint32_t GetRadioButtonTextSize();
	
	gds::Font GetTextAreaFont();
	uint32_t GetTextAreaTextSize();
	
	gds::Font GetGroupBoxFont();
	uint32_t GetGroupBoxTextSize();
	
	gds::Font GetListBoxFont();
	uint32_t GetListBoxTextSize();
	
	gds::Font GetDetailListFont();
	uint32_t GetDetailListTextSize();
	
	gds::Font GetIconViewFont();
	uint32_t GetIconViewTextSize();
}

}
}

#endif
