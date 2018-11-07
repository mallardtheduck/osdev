#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include <btos/registry.hpp>
#include <ext/dmi.hpp>
#include <btos/ini.hpp>

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace reg = btos_api::registry;
namespace hwpnp = btos_api::hwpnp;

static const string DriverFeatureType = "dm.driver";

struct Driver{
	string path;
	string feature;
	hwpnp::DeviceID devid;
};

static string MakeFilePath(const reg::FeatureInfo &feat, const string &file){
	auto pkg = reg::GetPackageById(feat.package);
	std::stringstream ss;
	ss << pkg.path;
	ss << feat.path;
	if(feat.path.back() != '/') ss << '/';
	ss << file;
	return ss.str();
}

static vector<string> SplitString(const string &str, const char sep){
	vector<string> ret;
	string current;
	for(char c : str){
		if(c == sep && !current.empty()){
			ret.push_back(current);
			current.clear();
		}else{
			current += c;
		}
	}
	if(current!="") ret.push_back(current);
	return ret;
}

static hwpnp::DeviceID ParseDeviceID(const string &str){
	auto parts = SplitString(str, ':');
	if(parts.size() != 6) return hwpnp::NullDeviceID;
	
	hwpnp::DeviceID ret;
	ret.Bus = (hwpnp::PNPBUS::Enum)strtol(parts[0].c_str(), nullptr, 0);
	ret.VendorID = strtoull(parts[1].c_str(), nullptr, 0);
	ret.DeviceID = strtoull(parts[2].c_str(), nullptr, 0);
	ret.Revision = strtoull(parts[3].c_str(), nullptr, 0);
	ret.ExtraID = strtoull(parts[4].c_str(), nullptr, 0);
	ret.Class = strtoull(parts[5].c_str(), nullptr, 0);
	return ret;
}

static string UnParseDeviceID(const hwpnp::DeviceID id){
	std::stringstream ss;
	ss << std::hex;
	ss << id.Bus << ':';
	ss << id.VendorID << ':';
	ss << id.DeviceID << ':';
	ss << id.Revision << ':';
	ss << id.ExtraID << ':';
	ss << id.Class;
	return ss.str();
}

static vector<Driver> GetDrivers(){
	vector<Driver> ret;
	auto regDrivers = reg::GetFeaturesByType(DriverFeatureType);
	for(const auto &rd : regDrivers){
		auto df = reg::GetFeatureByName(rd);
		auto path = reg::GetFeaturePath(df.id);
		std::ifstream file(path);
		if(file.is_open()){
			auto ini = btos_api::ReadIniFile(file);
			auto section = ini["driver"];
			if(section.size()){
				auto devIdStr = section["devid"];
				auto devId = ParseDeviceID(devIdStr);
				auto fileName = section["file"];
				auto driverPath = MakeFilePath(df, fileName);
				if(devId != hwpnp::NullDeviceID) ret.push_back({driverPath, rd, devId});
			}
		}
	}
	return ret;
}

int main(int /*argc*/, char **/*argv*/){
	cout << "BT/OS Driver Manager" << endl;
	auto drivers = GetDrivers();
	cout << "Drivers: " << drivers.size() << endl << endl;
	
	for(const auto &d : drivers){
		cout << "Registry Feature ID: " << d.feature << endl;
		cout << "DeviceID: " << UnParseDeviceID(d.devid) << endl;
		cout << "File: " << d.path << endl << endl;
	}
	
	return 0;
}