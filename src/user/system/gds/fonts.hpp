#ifndef _FONTS_HPP
#define _FONTS_HPP

#include "gds.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

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
	FT_Library library;
	
public:
	FontManager();
	
	std::shared_ptr<gds_FontInfo> GetFont(std::string family, gds_FontStyle::Enum style);
	std::string GetFontFile(uint32_t id);
};

std::shared_ptr<FontManager> GetFontManager();

#endif
