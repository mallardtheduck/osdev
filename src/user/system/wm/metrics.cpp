#include <gds/libgds.h>
#include "metrics.hpp"
#include "config.hpp"
#include "ini.hpp"
#include <cstdlib>
#include <vector>
#include <unordered_map>

using namespace std;

#define METRIC(type, name) Metric<type> name { #name }

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

METRIC(ColourValue, TitleBarColour);
METRIC(ColourValue, ButtonFaceColour);
METRIC(ColourValue, ButtonHighlightColour);
METRIC(ColourValue, ButtonShadowColour);
METRIC(ColourValue, LineColour);
METRIC(ColourValue, BorderColour);
METRIC(ColourValue, SeperatorColour);
METRIC(ColourValue, TitleTextColour);
METRIC(ColourValue, InactiveTitleColour);
METRIC(ColourValue, SymbolColour);
METRIC(ColourValue, BackgroundColour);
METRIC(ColourValue, MenuBackgroundColour);
METRIC(ColourValue, MenuForegroundColour);
METRIC(ColourValue, MenuSelectionColour);

METRIC(std::string, TitleFontName);
METRIC(std::string, MenuButtonFontName);
METRIC(std::string, MenuFontName);

static const string colourPrefix = "Colour(";
static const string colourEnding = ")";

static bool starts_with(const string &s1, const string &s2){
    return s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0;
}

static bool ends_with(const string &s1, const string &s2){
	if(s1.length() >= s2.length()){
		return s1.compare(s1.length() - s2.length(), s2.length(), s2) == 0;
	}
	return false;
}

vector<string> split(const string &s, char c) {
	vector<string> v;
	unsigned int i = 0;
	unsigned int j = s.find(c);
	while (j < s.length()) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);
		if (j >= s.length()) {
			v.push_back(s.substr(i, s.length()));
			break;
		}
	}
	return v;
}

int32_t GetMetric(Metric<int32_t> &metric){
	if(!metric.present){
		string val = GetConfigValue(metric.name);
		metric.value = strtol(val.c_str(), NULL, 0);
		metric.present = true;
	}
	return metric.value;
}

uint32_t GetColour(Metric<ColourValue> &metric){
	if(!metric.present){
		string val = GetConfigValue(metric.name);
		if(!starts_with(val, colourPrefix)) return 0;
		if(!ends_with(val, colourEnding)) return 0;
		val = val.substr(colourPrefix.length(), val.length() - (colourPrefix.length() + colourEnding.length()));
		auto parts = split(val, ',');
		if(parts.size() != 3) return 0;
		string rstr = parts[0];
		trim(rstr);
		string gstr = parts[1];
		trim(gstr);
		string bstr = parts[2];
		trim(bstr);
		uint8_t r = strtol(rstr.c_str(), NULL, 0);
		uint8_t g = strtol(gstr.c_str(), NULL, 0);
		uint8_t b = strtol(bstr.c_str(), NULL, 0);
		metric.value = {r, g, b};
		metric.present = true;
	}
	return GDS_GetColour(metric.value.r, metric.value.g, metric.value.b);
}

string GetSetting(Metric<string> &metric){
	if(!metric.present){
		metric.value = GetConfigValue(metric.name);
		metric.present = true;
	}
	return metric.value;
}
