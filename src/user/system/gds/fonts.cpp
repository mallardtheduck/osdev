#include "fonts.hpp"
#include <dirent.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H
#include FT_LCD_FILTER_H
#include FT_CFF_DRIVER_H

#include <btos/registry.hpp>

using namespace std;
namespace reg = btos_api::registry;

extern "C" FT_Library *gdGetFTLibrary(void);
extern "C" void gdFTLoadFace(FT_Library lib, const char *path, int face_index, FT_Face *face);

static bool ends_with (const string &fullString, const string &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


static bool is_font_file(const string &name){
	return ends_with(name, ".ttf") || ends_with(name, ".otf");	
}

FontManager::FontManager(){ 
	FT_Library &library = *gdGetFTLibrary();
	FT_Bool warping = 1;
	FT_Property_Set( library, "autofitter", "warping", &warping );
	FT_UInt hinting_engine = FT_CFF_HINTING_ADOBE;
	FT_Property_Set( library, "cff", "hinting-engine", &hinting_engine );
	FT_Bool no_darkening = 1;
	//FT_Property_Set( library, "autofitter", "no-stem-darkening", &no_darkening );
	FT_Property_Set( library, "cff", "no-stem-darkening", &no_darkening );
	FT_Int darken_params[8] = { 1000, 500,   // x1, y1
								1500, 332,   // x2, y2
								1750, 166,   // x3, y3
								2000,   0 }; // x4, y4
	//FT_Property_Set( library, "autofitter", "darkening-parameters", darken_params );
	FT_Property_Set( library, "cff", "darkening-parameters", darken_params );
	FT_Library_SetLcdFilter(library, FT_LCD_FILTER_LEGACY);
	auto feats = reg::GetFeaturesByType("fontpath");
	for(auto &f : feats){
		auto feat = reg::GetFeatureByName(f);
		auto path = reg::GetFeaturePath(feat.id);
		DIR *fontdir = opendir(path.c_str());
		while(dirent *fontent = readdir(fontdir)){
			if(is_font_file(fontent->d_name)){
				string fullPath = path + '/' + fontent->d_name;
				FT_Face face;
				//FT_New_Face(library, fullPath.c_str(), 0, &face);
				gdFTLoadFace(library, fullPath.c_str(), 0, &face);
				shared_ptr<Font> f {new Font()};
				f->file = fullPath;
				f->info->fontID = ++counter;
				memset((void*)f->info->name, 0, FONT_NAME_MAX);
				strncpy(f->info->name, face->family_name, FONT_NAME_MAX - 1);
				switch(face->style_flags){
					case FT_STYLE_FLAG_ITALIC:
						f->info->fontStyle = gds_FontStyle::Italic;
						break;
					case FT_STYLE_FLAG_BOLD:
						f->info->fontStyle = gds_FontStyle::Bold;
						break;
					case FT_STYLE_FLAG_ITALIC | FT_STYLE_FLAG_BOLD:
						f->info->fontStyle = gds_FontStyle::BoldItalic;
						break;
					default:
						f->info->fontStyle = gds_FontStyle::Normal;
						break;
				}
				f->info->scale = face->units_per_EM;
				f->info->maxW = face->max_advance_width;
				f->info->maxH = face->max_advance_height;
				fonts[f->info->fontID] = f;
				//FT_Done_Face(face);
				DBG("GDS: Font name: " << f->info->name << " Style: " << 
				(f->info->fontStyle == 0 ? "Normal" : f->info->fontStyle == 1 ? "Bold" : f->info->fontStyle == 2 ? "Italic" : "BoldItalic")
				<< " File: " << f->file);
			}
		}
		closedir(fontdir);
	}
}

shared_ptr<gds_FontInfo> FontManager::GetFont(std::string family, gds_FontStyle::Enum style){
	if(aliases.find(family) != aliases.end()) family = aliases[family];
	for(auto &f : fonts){
		if(family == f.second->info->name && style == f.second->info->fontStyle){
			return f.second->info;
		}
	}
	return NULL;
}

std::shared_ptr<gds_FontInfo> FontManager::GetFont(uint32_t id){
	if(fonts.find(id) != fonts.end()){
		return fonts[id]->info;
	}
	return NULL;
}

string FontManager::GetFontFile(uint32_t id){
	if(fonts.find(id) != fonts.end()){
		return fonts[id]->file;
	}
	return "";
}

gds_GlyphInfo FontManager::GetGlyphInfo(uint32_t fontID, size_t size, char c){
	int brect[8];
	string fontFile = GetFontFile(fontID);
	if(!size || fontFile == "") return gds_GlyphInfo();
	char chstring[] = {c, 0};
	gdFTStringExtra ftex;
	ftex.flags = gdFTEX_RESOLUTION;
	ftex.vdpi = 72;
	ftex.hdpi = 72;
	gdImageStringFTEx(NULL, brect, 0, (char*)fontFile.c_str(), size, 0, 0, 0, chstring, &ftex);
	gds_GlyphInfo ret;
	ret.fontID = fontID;
	ret.size = size;
	ret.ch = c;
	ret.w = (brect[2] - brect[6]);// / 2;
	ret.h = (brect[3] - brect[7]);// / 2;
	return ret;
}

void FontManager::AddAlias(const string &name, const string &alias){
	if(aliases.find(alias) != aliases.end()) return;
	for(auto &f : fonts){
		if(name == f.second->info->name){
			aliases[alias] = name;
		}
	}
}

uint32_t FontManager::GetMaxFontID(){
	return counter - 1;
}

std::shared_ptr<FontManager> GetFontManager(){
	static shared_ptr<FontManager> fmgr;
	if(!fmgr) fmgr.reset(new FontManager());
	return fmgr;
}
