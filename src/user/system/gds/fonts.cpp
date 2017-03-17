#include "fonts.hpp"
#include <dirent.h>

using namespace std;

static bool ends_with (const string &fullString, const string &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


static bool is_font_file(const string &name){
	return ends_with(name, ".ttf");	
}

FontManager::FontManager(){
	FT_Init_FreeType(&library);
	DIR *fontdir = opendir(FontPath.c_str());
	while(dirent *fontent = readdir(fontdir)){
		if(is_font_file(fontent->d_name)){
			string fullPath = FontPath + '/' + fontent->d_name;
			FT_Face face;
			FT_New_Face(library, fullPath.c_str(), 0, &face);
			shared_ptr<Font> f {new Font()};
			f->file = fullPath;
			f->info->fontID = ++counter;
			strncpy(f->info->name, face->family_name, FONT_NAME_MAX);
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
			fonts[f->info->fontID] = f;
			FT_Done_Face(face);
			DBG("GDS: Font name: " << f->info->name << " Style: " << 
			(f->info->fontStyle == 0 ? "Normal" : f->info->fontStyle == 1 ? "Bold" : f->info->fontStyle == 2 ? "Italic" : "BoldItalic")
			<< " File: " << f->file);
		}
	}
	closedir(fontdir);
}

shared_ptr<gds_FontInfo> FontManager::GetFont(std::string family, gds_FontStyle::Enum style){
	for(auto &f : fonts){
		if(family == f.second->info->name && style == f.second->info->fontStyle){
			return f.second->info;
		}
	}
	return NULL;
}

string FontManager::GetFontFile(uint32_t id){
	if(fonts.find(id) != fonts.end()){
		return fonts[id]->file;
	}
	return "";
}

std::shared_ptr<FontManager> GetFontManager(){
	static shared_ptr<FontManager> fmgr;
	if(!fmgr) fmgr.reset(new FontManager());
	return fmgr;
}
