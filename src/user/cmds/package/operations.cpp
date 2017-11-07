#include <btos/ini.hpp>
#include <btos/registry.hpp>

#include <vector>
#include <string>
#include <map>

#include "package.hpp"

using std::vector;
using std::string;
using std::map;

namespace reg = btos_api::registry;

bool starts_with(const string &str, const string &start){
    if(str.length() < start.length()) return false;
    return str.substr(0, start.length()) == start;
}

string get_or_blank(const map<string, string> &section, const string &key){
    if(section.find(key) != section.end()) return section.at(key);
    else return "";
}

void ImportPackage(const string &infpath, const string &path){
    auto file = btos_api::ReadIniFile(infpath);
    if(file.find("package") != file.end()){
        auto pkgsection = file["package"];
        reg::PackageInfo pkginfo;
        pkginfo.name = get_or_blank(pkgsection, "name");
        pkginfo.description = get_or_blank(pkgsection, "description");
        pkginfo.ver = get_or_blank(pkgsection, "version");
        pkginfo.path = path;
        if(pkginfo.name == "") return;

        int64_t pkgid;
        auto cpkg = reg::GetPackageByName(pkginfo.name);
        if(cpkg.id > 0) pkgid = cpkg.id;
        else pkgid = reg::InstallPackage(pkginfo);

        for(auto &s : file){
            if(starts_with(s.first, "feature")){
                reg::FeatureInfo featinfo;
                featinfo.package = pkgid;
                featinfo.name = get_or_blank(s.second, "name");
                featinfo.description = get_or_blank(s.second, "description");
                featinfo.path = get_or_blank(s.second, "path");
                featinfo.file = get_or_blank(s.second, "file");
                featinfo.type = get_or_blank(s.second, "type");
                featinfo.ver = get_or_blank(s.second, "version");
                featinfo.flags = 0;

                if(featinfo.name == "") continue;
                if(featinfo.ver == "") featinfo.ver = pkginfo.ver;

                if(reg::GetFeatureByName(featinfo.name).id < 0){
                    reg::InstallFeature(featinfo);
                }
            }
        }
    }
}