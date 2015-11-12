#ifndef METRICS_HPP
#define METRICS_HPP

static const uint32_t TitleBarSize = 20;
static const uint32_t BorderWidth = 1;
static const uint32_t ButtonSize = TitleBarSize - 2;
static const uint32_t MenuButtonWidth = 50;

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

#endif