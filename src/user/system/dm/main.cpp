#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#define BTOS_NO_USING

#include <btos/registry.hpp>
#include <ext/dmi.hpp>
#include <btos/ini.hpp>
#include <btos/messageloop.hpp>
#include <btos/imessagehandler.hpp>
#include <btos/envvars.hpp>

using std::string;
using std::vector;

namespace reg = btos_api::registry;
namespace hwpnp = btos_api::hwpnp;

static const string DriverFeatureType = "dm.driver.inf";
static uint16_t dmi_ext = 0;

vector<hwpnp::DeviceID> known_devices;

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

static vector<string> split(const string& s, char delimiter){
   vector<string> tokens;
   string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

static vector<Driver> GetDrivers(){
	static vector<Driver> ret;
	auto regDrivers = reg::GetFeaturesByType(DriverFeatureType);
	if(regDrivers.empty()) btos_api::bt_zero("DM: No drivers found!\n");
	for(const auto &rd : regDrivers){
		if(std::find_if(ret.begin(), ret.end(), [&](const Driver &x) -> bool{
			return x.feature == rd;
		}) == ret.end()){
			auto df = reg::GetFeatureByName(rd);
			auto path = reg::GetFeaturePath(df.id);
			std::ifstream file(path);
			if(file.is_open()){
				auto ini = btos_api::ReadIniFile(file);
				auto section = ini["driver"];
				if(section.size()){
					auto devIdList = section["devid"];
					auto devIds = split(devIdList, ',');
					for(auto &devIdStr : devIds){
						auto devId = ParseDeviceID(devIdStr);
						auto fileName = section["file"];
						auto driverPath = MakeFilePath(df, fileName);
						if(devId != hwpnp::NullDeviceID) ret.push_back({driverPath, rd, devId});
					}
				}
			}
		}
	}
	return ret;
}

void Register(){
	if(!dmi_ext) dmi_ext = btos_api::bt_query_extension("DMI");
	uint32_t callid = (dmi_ext << 16) | bt_dm_function::Register;
	btos_api::btos_call(callid, 0, 0, 0);
}

dm_dev_info GetFirstDevice(){
	if(!dmi_ext) dmi_ext = btos_api::bt_query_extension("DMI");
	uint32_t callid = (dmi_ext << 16) | bt_dm_function::GetFirstDevice;
	dm_dev_info ret;
	btos_api::btos_call(callid, (uint32_t)&ret, 0, 0);
	return ret;
}

dm_dev_info GetNextDevice(dm_dev_info dev){
	if(!dmi_ext) dmi_ext = btos_api::bt_query_extension("DMI");
	uint32_t callid = (dmi_ext << 16) | bt_dm_function::GetNextDevice;
	btos_api::btos_call(callid, (uint32_t)&dev, 0, 0);
	return dev;
}

int DeviceIDMatch(const hwpnp::DeviceID &a, const hwpnp::DeviceID &b){
	int ret = 0;
	if(a.Bus != b.Bus) return 0;
	if(a.VendorID != 0 && a.VendorID != b.VendorID) return 0;
	else ++ret;
	if(a.DeviceID != 0 && a.DeviceID != b.DeviceID) return 0;
	else ++ret;
	if(a.Revision != 0 && a.Revision != b.Revision) return 0;
	else ++ret;
	if(a.ExtraID != 0 && a.ExtraID != b.ExtraID) return 0;
	else ++ret;
	if(a.Class != 0 && a.Class != b.Class) return 0;
	else ++ret;
	return ret;
}

void DeviceFound(const hwpnp::DeviceID dev){
	btos_api::bt_zero("DM: Found device: ");
	btos_api::bt_zero(UnParseDeviceID(dev).c_str());
	btos_api::bt_zero("\n");
	
	auto drivers = GetDrivers();
	
	Driver bestDriver;
	int matchLevel = 0;
	for(const auto &d : drivers){
		auto ml = DeviceIDMatch(d.devid, dev);
		if(ml > matchLevel){
			bestDriver = d;
			matchLevel = ml;
		}
	}
	
	if(matchLevel){
		btos_api::bt_zero("DM: Loading: ");
		btos_api::bt_zero(bestDriver.path.c_str());
		btos_api::bt_zero("\n");
		btos_api::bt_load_module(bestDriver.path.c_str(), "");
	}
}

int main(int argc, char **argv){
	vector<string> args{argv, argv + argc};
	bool newDevice = true;
	btos_api::bt_zero("DM: Checking existing devices...\n");
	while(newDevice){
		newDevice = false;
		auto cDev = GetFirstDevice();
		while(cDev.devid != hwpnp::NullDeviceID){
			if(std::find(known_devices.begin(), known_devices.end(), cDev.devid) == known_devices.end()){
				DeviceFound(cDev.devid);
				known_devices.push_back(cDev.devid);
				newDevice = true;
			}
			cDev = GetNextDevice(cDev);
		}
	}
	if(args.size() > 1){
		btos_api::bt_setenv(args[1].c_str(), "READY", 1);
	}
	btos_api::bt_zero("DM: Entering on-demand mode...\n");
	Register();
	auto handler = std::make_shared<btos_api::CustomHandler>([&](const btos_api::Message &msg) -> bool{
		if(msg.From() == 0 && msg.Source() == dmi_ext){
			switch(msg.Type()){
				case bt_dm_event::DeviceFound:
					hwpnp::DeviceID dev = msg.Content<hwpnp::DeviceID>();
					if(std::find(known_devices.begin(), known_devices.end(), dev) == known_devices.end()){
						DeviceFound(dev);
						known_devices.push_back(dev);
					}
				break;
			}
			msg.SendReply();
		}
		return true;
	});
	btos_api::MessageLoop loop;
	loop.AddHandler(handler);
	loop.RunLoop();
	
	return 0;
}