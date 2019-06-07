#ifndef METRICS_HPP
#define METRICS_HPP

#include <string>
#include <gds/geom.hpp>
#include <gds/surface.hpp>

using namespace btos_api;

template<typename T> struct Metric{
	std::string name;
	bool present = false;
	T value;
	
	constexpr Metric<T>(const std::string &n) : name(n) {}
};

struct ColourValue{
	uint8_t r, g, b;
};

#define METRIC(type, name) extern Metric<type> name

METRIC(int32_t, TitleBarSize);
METRIC(int32_t, TitleTextMargin);
METRIC(int32_t, BorderWidth);
METRIC(int32_t, ButtonSize);
METRIC(int32_t, MenuButtonWidth);
METRIC(int32_t, FullWindowDrag);
METRIC(int32_t, TitleFontSize);
METRIC(int32_t, MenuButtonFontSize);
METRIC(int32_t, TitleTextBaseline);
METRIC(int32_t, ScreenWidth);
METRIC(int32_t, ScreenHeight);
METRIC(int32_t, ScreenBpp);
METRIC(int32_t, MenuFontSize);
METRIC(int32_t, MenuItemMargin);
METRIC(int32_t, MenuItemHeight);

int32_t GetMetric(Metric<int32_t> &metric);

METRIC(ColourValue, TitleBarColour);
METRIC(ColourValue, ButtonFaceColour);
METRIC(ColourValue, ButtonHighlightColour);
METRIC(ColourValue, ButtonShadowColour);
METRIC(ColourValue, LineColour);
METRIC(ColourValue, BorderColour);
METRIC(ColourValue, SeparatorColour);
METRIC(ColourValue, TitleTextColour);
METRIC(ColourValue, InactiveTitleColour);
METRIC(ColourValue, SymbolColour);
METRIC(ColourValue, DisabledSymbolColour);
METRIC(ColourValue, BackgroundColour);
METRIC(ColourValue, MenuBackgroundColour);
METRIC(ColourValue, MenuForegroundColour);
METRIC(ColourValue, MenuForegroundDisabledColour);
METRIC(ColourValue, MenuSelectionColour);

gds::Colour GetColour(const gds::Surface &surf, Metric<ColourValue> &metric);

METRIC(std::string, TitleFontName);
METRIC(std::string, MenuButtonFontName);
METRIC(std::string, MenuFontName);

std::string GetSetting(Metric<std::string> &metric);

#undef METRIC

#endif
