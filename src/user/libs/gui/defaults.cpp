#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{
	
namespace colours{
	namespace constants{
		gds::Colour Black		{0, 0x00, 0x00, 0x00, 0};
		gds::Colour Blue		{0, 0x00, 0x00, 0xA8, 0};
		gds::Colour Green		{0, 0x00, 0xA8, 0x00, 0};
		gds::Colour Cyan		{0, 0x00, 0xA8, 0xA8, 0};
		gds::Colour Red			{0, 0xA8, 0x00, 0x00, 0};
		gds::Colour Purple		{0, 0xA8, 0x00, 0xA8, 0};
		gds::Colour Orange		{0, 0xA8, 0x54, 0x00, 0};
		gds::Colour Grey		{0, 0xA8, 0xA8, 0xA8, 0};
		gds::Colour DarkGrey	{0, 0x54, 0x54, 0x54, 0};
		gds::Colour LightBlue	{0, 0x54, 0x54, 0xFF, 0};
		gds::Colour LightGreen	{0, 0x54, 0xFF, 0x54, 0};
		gds::Colour LightCyan	{0, 0x54, 0xFF, 0xFF, 0};
		gds::Colour Pink		{0, 0xFF, 0x54, 0x54, 0};
		gds::Colour Magenta		{0, 0xFF, 0x54, 0xFF, 0};
		gds::Colour Yellow		{0, 0xFF, 0xFF, 0x54, 0};
		gds::Colour White		{0, 0xFF, 0xFF, 0xFF, 0};
	}
	
	gds::Colour GetBackground(){
		return constants::White;
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
}

namespace fonts{
	gds::Font GetButtonFont(){
		return gds::Font::Get("Resagnicto", gds_FontStyle::Bold);
	}
	
	uint32_t GetButtonTextSize(){
		return 12;
	}
}

}
}
