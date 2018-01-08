#include "packagefile.hpp"
#include "package.hpp"
#include <btos/ini.hpp>
#include <memory>
#include <sstream>

using std::string;
using std::unique_ptr;
using std::stringstream;
using std::vector;

namespace reg = btos_api::registry;

const size_t MaxInfSize = 1 * 1024 * 1024;

static string filter_filename(const string &name){
	if(starts_with(name, "./")){
		return name.substr(2);
	}else return name;
}

void PackageFile::Parse(){
	tar::reader rdr(stream);
	while(rdr.contains_another_file()){
		if(rdr.get_next_file_size() <= MaxInfSize && filter_filename(rdr.get_next_file_name()) == "package.inf"){
			stringstream infStream;
			{
				auto size = rdr.get_next_file_size();
				unique_ptr<char> buffer{new char[size]};
				rdr.read_next_file(buffer.get());
				infStream.write(buffer.get(), size);
				infStream.seekg(0);
			}
			auto infFile = btos_api::ReadIniFile(infStream);
			if(infFile.find("package") != infFile.end()){
				auto pkgsection = infFile["package"];
				packageInfo.name = get_or_blank(pkgsection, "name");
				packageInfo.description = get_or_blank(pkgsection, "description");
				packageInfo.ver = get_or_blank(pkgsection, "version");
				packageInfo.path = "NOT YET INSTALLED";
				if(packageInfo.name == "") return;
				
				for(auto &s : infFile){
					if(starts_with(s.first, "feature")){
						reg::FeatureInfo featinfo;
						featinfo.package = -1;
						featinfo.name = get_or_blank(s.second, "name");
						featinfo.description = get_or_blank(s.second, "description");
						featinfo.path = get_or_blank(s.second, "path");
						featinfo.file = get_or_blank(s.second, "file");
						featinfo.type = get_or_blank(s.second, "type");
						featinfo.ver = get_or_blank(s.second, "version");
						featinfo.flags = 0;
						
						if(featinfo.name == "") continue;
						if(featinfo.ver == "") featinfo.ver = packageInfo.ver;
						features.push_back(featinfo);
					}
				}
			}
		}else{
			rdr.skip_next_file();
		}
	}
	stream.seekg(0);
}

PackageFile::PackageFile(const string &path){
	stream.open(path);
	Parse();
}

reg::PackageInfo PackageFile::GetInfo(){
	return packageInfo;
}

vector<reg::FeatureInfo> PackageFile::GetFeatures(){
	return features;
}

uint64_t PackageFile::Install(const string &/*path*/){
	return -1;
}

