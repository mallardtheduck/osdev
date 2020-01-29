#include <sm/sessions.hpp>

#include <btos/directory.hpp>
#include <btos/envvars.hpp>
#include <btos/ini.hpp>
#include <btos/registry.hpp>
#include <btos/resc.h>

#include <algorithm>
#include <cctype>

#include <ext/stdio_filebuf.h>

namespace btos_api{
namespace sm{
	
namespace reg = btos_api::registry;

static const std::string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/");

static char char_tolower(char ch){
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}

static void addSession(std::vector<SessionType> &sessions, const std::string &fname, const std::string &id){
	auto info = bt_stat(fname.c_str());
	if(info.type == FS_File){
		std::string filename = info.filename;
		if(filename.length() > 4){
			std::transform(filename.begin(), filename.end(), filename.begin(), char_tolower);
			auto ext = filename.substr(filename.length() - 4);
			
			btos_api::IniFile file;
			if(ext == ".ini"){
				file = btos_api::ReadIniFile(fname);
			}else if(ext == ".elx"){
				auto h = resc::Resc_FileOpen(fname);
				auto sessionIni = resc::Resc_OpenResc(h, "session.ini");
				if(sessionIni){
					__gnu_cxx::stdio_filebuf<char> filebuf(sessionIni, std::ios::in);
					std::istream is(&filebuf);
					file = btos_api::ReadIniFile(is);
				}
				resc::Resc_Close(h);
			}
		
			if(!file.empty()){
				auto varGet = [&](const std::string &key){
					if(key == "this") return fname;
					else return btos_api::GetEnv(key);
				};
				
				auto section = file["session"];
				auto name = section["name"];
				auto leadElx = Interpolate(section["lead"], varGet);
				std::vector<std::string> svcs;
				if(file.find("services") != file.end()){
					auto services = file["services"];
					for(auto s : services){
						svcs.push_back(s.second);
					}
				}
				sessions.push_back(SessionType{id, name, leadElx, svcs});
			}
		}
	}
};

static std::string to_lower(std::string str){
	std::transform(str.begin(), str.end(), str.begin(), char_tolower);
	return str;
}

static bool hasEnding (const std::string &fullString, const std::string &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

std::vector<SessionType> GetSessionTypes(){
	std::vector<SessionType> ret;
	Directory d {SessionsPath.c_str(), FS_Read};
	for(auto f : d){
		std::string fname = f.filename;
		if(f.type == FS_File && hasEnding(to_lower(fname), ".ini")){
			addSession(ret, SessionsPath + fname, fname.substr(0, fname.length() - 4));
		}
	}
	auto feats = reg::GetFeaturesByType("sm.ses");
	for(auto &f : feats){
		auto feat = reg::GetFeatureByName(f);
		auto fname = reg::GetFeaturePath(feat.id);
		addSession(ret, fname, f);
	}
	return ret;
}

}
}