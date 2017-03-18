#ifndef _FONTS_HPP
#define _FONTS_HPP

#include "gds.hpp"

static const std::string FontPath = "/BTOS/FONTS";

class FontManager{
private:
	struct Font{
		std::shared_ptr<gds_FontInfo> info;
		std::string file;
		
		Font() : info(new gds_FontInfo()) {}
	};

	uint32_t counter = 0;
	std::map<uint32_t, std::shared_ptr<Font>> fonts;
	
public:
	FontManager();
	
	std::shared_ptr<gds_FontInfo> GetFont(std::string family, gds_FontStyle::Enum style);
	std::shared_ptr<gds_FontInfo> GetFont(uint32_t id);
	std::string GetFontFile(uint32_t id);
	
	gds_GlyphInfo GetGlyphInfo(uint32_t fontID, size_t size, char c);
};

std::shared_ptr<FontManager> GetFontManager();

#endif
