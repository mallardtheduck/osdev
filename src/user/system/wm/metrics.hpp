#ifndef METRICS_HPP
#define METRICS_HPP

#include <string>

#define TitleBarSize "TitleBarSize"
#define TitleTextMargin "TitleTextMargin"
#define BorderWidth "BorderWidth"
#define ButtonSize "ButtonSize"
#define MenuButtonWidth "MenuButtonWidth"
#define FullWindowDrag "FullWindowDrag"
#define TitleFontSize "TitleFontSize"
#define MenuButtonFontSize "MenuButtonFontSize"
#define TitleTextBaseline "TitleTextBaseline"
#define ScreenWidth "ScreenWidth"
#define ScreenHeight "ScreenHeight"
#define ScreenBpp "ScreenBpp"

int32_t GetMetric(const std::string &name);

#define TitleBarColour "TitleBarColour"
#define ButtonFaceColour "ButtonFaceColour"
#define ButtonHighlightColour "ButtonHighlightColour"
#define ButtonShadowColour "ButtonShadowColour"
#define LineColour "LineColour"
#define BorderColour "BorderColour"
#define SeperatorColour "SeperatorColour"
#define TitleTextColour "TitleTextColour"
#define InactiveTitleColour "InactiveTitleColour"
#define SymbolColour "SymbolColour" 
#define BackgroundColour "BackgroundColour"

uint32_t GetColour(const std::string &name);

#define TitleFontName "TitleFontName"
#define MenuButtonFontName "MenuButtonFontName"

std::string GetSetting(const std::string &name);

#endif
