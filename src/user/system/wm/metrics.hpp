#ifndef METRICS_HPP
#define METRICS_HPP

static const int32_t TitleBarSize = 20;
static const int32_t TitleTextMargin = 5;
static const int32_t BorderWidth = 1;
static const int32_t ButtonSize = TitleBarSize - 2;
static const int32_t MenuButtonWidth = (TitleBarSize + TitleTextMargin) * 2;
static const int32_t FullWindowDrag = 1;
static const int32_t TitleFontSize = 16;
static const int32_t TitleTextBaseline = 5;
static const int32_t ScreenWidth = 800;
static const int32_t ScreenHeight = 600;
static const int32_t ScreenBpp = 24;

#define GetMetric(x) x

#define TitleBarColour GDS_GetColour(0, 0, 255)
#define ButtonFaceColour GDS_GetColour(128, 128, 128)
#define ButtonHighlightColour GDS_GetColour(255, 255, 255)
#define ButtonShadowColour GDS_GetColour(64, 64, 64)
#define LineColour GDS_GetColour(0, 0, 0)
#define BorderColour GDS_GetColour(170, 0, 170)
#define SeperatorColour GDS_GetColour(64, 64, 64)
#define TitleTextColour GDS_GetColour(255, 255, 255)
#define InactiveTitleColour GDS_GetColour(64, 64, 64)
#define SymbolColour GDS_GetColour(0, 0, 0) 
#define BackgroundColour GDS_GetColour(0, 170, 170)

#define GetColour(x) x

static const std::string TitleFontName = "Resagokr";
static const std::string MenuButtonFontName = "DejaVu Sans";

#define GetSetting(x) x

#endif
