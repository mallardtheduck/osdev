#include <gds/libgds.h>
#include "metrics.hpp"
#include "config.hpp"
#include "ini.hpp"
#include <cstdlib>
#include <vector>

using namespace std;

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

int32_t GetMetric(const string &name){
	string val = GetConfigValue(name);
	int32_t ret = strtol(val.c_str(), NULL, 0);
	return ret;
}

uint32_t GetColour(const string &name){
	string val = GetConfigValue(name);
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
	return GDS_GetColour(r, g, b);
}

string GetSetting(const string &name){
	return GetConfigValue(name);
}
