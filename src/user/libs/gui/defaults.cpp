#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{
	
namespace colours{
	namespace constants{
		const gds::Colour Black               {0, 0x00, 0x00, 0x00, 0};
		const gds::Colour Blue                {0, 0x00, 0x00, 0xA8, 0};
		const gds::Colour Green               {0, 0x00, 0xA8, 0x00, 0};
		const gds::Colour Cyan                {0, 0x00, 0xA8, 0xA8, 0};
		const gds::Colour Red                 {0, 0xA8, 0x00, 0x00, 0};
		const gds::Colour Purple              {0, 0xA8, 0x00, 0xA8, 0};
		const gds::Colour Orange              {0, 0xA8, 0x54, 0x00, 0};
		const gds::Colour Grey                {0, 0xA8, 0xA8, 0xA8, 0};
		const gds::Colour DarkGrey    		  {0, 0x54, 0x54, 0x54, 0};
		const gds::Colour LightBlue   		  {0, 0x54, 0x54, 0xFF, 0};
		const gds::Colour LightGreen  	  	  {0, 0x54, 0xFF, 0x54, 0};
		const gds::Colour LightCyan   		  {0, 0x54, 0xFF, 0xFF, 0};
		const gds::Colour Pink                {0, 0xFF, 0x54, 0x54, 0};
		const gds::Colour Magenta             {0, 0xFF, 0x54, 0xFF, 0};
		const gds::Colour Yellow              {0, 0xFF, 0xFF, 0x54, 0};
		const gds::Colour White               {0, 0xFF, 0xFF, 0xFF, 0};
	}
	
	gds::Colour GetBackground(){
		return constants::White;
	}
	
	gds::Colour GetSelection(){
		return constants::LightBlue;
	}
	
	gds::Colour GetSelectionFocus(){
		return constants::Blue;
	}
	
	gds::Colour GetDisabledCast(){
		auto c = constants::Grey;
		c.a = 128;
		return c;
	}
	
	gds::Colour GetButtonColour(){
		return constants::Grey;
	}
	
	gds::Colour GetButtonHiLight(){
		return constants::White;
	}
	
	gds::Colour GetButtonLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetBorder(){
		return constants::Black;
	}
	
	gds::Colour GetButtonText(){
		return constants::Black;
	}
	
	gds::Colour GetButtonFocus(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetLabelText(){
		return constants::Black;
	}
	
	gds::Colour GetTextBoxText(){
		return constants::Black;
	}
	
	gds::Colour GetTextBoxHiLight(){
		return constants::Grey;
	}
	
	gds::Colour GetTextBoxLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetTextCursor(){
		return constants::Black;
	}
	
	gds::Colour GetSliderLineHiLight(){
		return constants::Grey;
	}
	
	gds::Colour GetSliderLineLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetSliderColour(){
		return constants::Grey;
	}
	
	gds::Colour GetSliderFocus(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetSliderTick(){
		return constants::Black;
	}
	
	gds::Colour GetCheckboxText(){
		return constants::Black;
	}
	
	gds::Colour GetCheckboxHiLight(){
		return constants::Grey;
	}
	
	gds::Colour GetCheckboxLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetCheckboxCheck(){
		return constants::Black;
	}
	
	gds::Colour GetCheckboxFocus(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetRadioButtonText(){
		return constants::Black;
	}
	
	gds::Colour GetRadioButtonHiLight(){
		return constants::Grey;
	}
	
	gds::Colour GetRadioButtonLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetRadioButtonCheck(){
		return constants::Black;
	}
	
	gds::Colour GetRadioButtonFocus(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetScrollbarBackground(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetScrollbarButton(){
		return constants::Grey;
	}
	
	gds::Colour GetScrollbarHiLight(){
		return constants::White;
	}
	
	gds::Colour GetScrollbarLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetScrollbarArrow(){
		return constants::Black;
	}
	
	gds::Colour GetScrollbarFocus(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetTextAreaText(){
		return constants::Black;
	}
	
	gds::Colour GetTextAreaHiLight(){
		return constants::Grey;
	}
	
	gds::Colour GetTextAreaLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetGroupBoxText(){
		return constants::Black;
	}
	
	gds::Colour GetListBoxText(){
		return constants::Black;
	}
	
	gds::Colour GetListBoxHiLight(){
		return constants::Grey;
	}
	
	gds::Colour GetListBoxLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetDetailListText(){
		return constants::Black;
	}
	
	gds::Colour GetDetailListHiLight(){
		return constants::Grey;
	}
	
	gds::Colour GetDetailListLowLight(){
		return constants::DarkGrey;
	}
	
	gds::Colour GetDetailListHeader(){
		return constants::Grey;
	}
}

namespace fonts{
	gds::Font GetButtonFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Bold);
	}
	
	uint32_t GetButtonTextSize(){
		return 12;
	}
	
	gds::Font GetLabelFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetLabelTextSize(){
		return 12;
	}
	
	gds::Font GetTextBoxFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetTextBoxTextSize(){
		return 12;
	}
	
	gds::Font GetCheckboxFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetCheckboxTextSize(){
		return 12;
	}
	
	gds::Font GetRadioButtonFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetRadioButtonTextSize(){
		return 12;
	}
	
	gds::Font GetTextAreaFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetTextAreaTextSize(){
		return 12;
	}
	
	gds::Font GetGroupBoxFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetGroupBoxTextSize(){
		return 12;
	}
	
	gds::Font GetListBoxFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetListBoxTextSize(){
		return 12;
	}
	
	gds::Font GetDetailListFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Normal);
	}
	
	uint32_t GetDetailListTextSize(){
		return 12;
	}
}

}
}
