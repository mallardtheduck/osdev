#define BTOS_NO_USING
#include <btos.h>
#include <btos/resc.h>
#include <btos/ini.hpp>
#include <gds/libgds.h>

#include <unistd.h>

#include <gui/shell/utils.hpp>

#include "shell_resc.tar.h"

#include <util/tinyformat.hpp>
#include <util/lrucache.hpp>
#include <ext/stdio_filebuf.h>
#include <btos/registry.hpp>

namespace btos_api{
namespace gui{
namespace shell{
	
static cache::lru_cache<std::string, std::shared_ptr<gds::Surface>> iconCache(128);

struct elxIconInfo{
	bool useDefault;
	std::string path;
	std::string name;
};

static cache::lru_cache<std::string, elxIconInfo> elxIconInfoCache(256);
static std::map<std::string, std::shared_ptr<gds::Surface>> loadedIcons;

static cache::lru_cache<std::string, AppInfo> appInfoCache(256);

static auto cacheLock = btos_api::bt_create_lock();

static std::shared_ptr<gds::Surface> LoadPNGFromFD(int fd){
	auto png = GDS_LoadPNG(fd);
	return std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(png, true)));
}

static resc::RescHandle GetLocalResc(){
	static auto ret = resc::Resc_LocalOpen(shell_resc_data, shell_resc_size);
	return ret;
}

std::shared_ptr<gds::Surface> LoadIcon(const char *path){
	auto i = loadedIcons.find(path);
	if(i == loadedIcons.end()){
		auto r = GetLocalResc();
		auto fd = resc::Resc_OpenResc(r, path);
		auto s = LoadPNGFromFD(fd);
		close(fd);
		i = loadedIcons.insert(loadedIcons.end(), std::make_pair(path, s));
	}
	return i->second;
}

static std::shared_ptr<gds::Surface> GetIconFromResc(resc::RescHandle h, const std::string &name, size_t size){
	std::shared_ptr<gds::Surface> ret = nullptr;
	auto iconsInf = resc::Resc_OpenResc(h, "icons.inf");
	if(iconsInf){
		__gnu_cxx::stdio_filebuf<char> filebuf(iconsInf, std::ios::in);
		std::istream is(&filebuf);
		auto ini = ReadIniFile(is);
		auto section = ini.find(name);
		if(section != ini.end()){
			auto sizeStr = tfm::format("%s", size);
			auto key = section->second.find(sizeStr);
			if(key != section->second.end()){
				auto png = resc::Resc_OpenResc(h, key->second);
				ret = LoadPNGFromFD(png);
				close(png);
			}
		}
	}
	return ret;
}

static std::string IconCacheKey(const std::string &path, const std::string &name, size_t size){
	return tfm::format("%s:%s:%s", path, name, size);
}

static std::shared_ptr<gds::Surface> GetIconFromCache(const std::string &cacheKey, std::function<std::shared_ptr<gds::Surface>()> loader){
	bt_lock(cacheLock);
	std::shared_ptr<gds::Surface> icon;
	if(!iconCache.exists(cacheKey)){
		bt_unlock(cacheLock);
		icon = loader();
		bt_lock(cacheLock);
		if(icon) iconCache.put(cacheKey, icon);
	}else{
		icon = iconCache.get(cacheKey);
	}
	bt_unlock(cacheLock);
	return icon;
}

static std::string GetDefaultIconName(DefaultIcons icon){
	std::string name;
	switch(icon){
		case DefaultIcons::Folder:
			name = "folder";
			break;
		case DefaultIcons::FolderOpen:
			name = "folder_open";
			break;
		case DefaultIcons::File:
			name = "file";
			break;
		case DefaultIcons::Executable:
			name = "exec";
			break;
		case DefaultIcons::Computer:
			name = "computer";
			break;
		case DefaultIcons::Drive:
			name = "hdd";
			break;
		case DefaultIcons::Device:
			name = "device";
			break;
		case DefaultIcons::Unknown:
		default:
			name = "error";
			break;
	}
	return name;
}

static std::string GetDefaultIconId(DefaultIcons icon, size_t size){
	auto name = GetDefaultIconName(icon);
	return IconCacheKey("-DEFAULT-", name, size);
}

std::shared_ptr<gds::Surface> GetDefaultIcon(DefaultIcons icon, size_t size){
	bt_lock(cacheLock);
	static std::map<std::string, std::shared_ptr<gds::Surface>> defaultIcons;
	
	std::shared_ptr<gds::Surface> ret;
	auto cacheKey = GetDefaultIconId(icon, size);
	auto it = defaultIcons.find(cacheKey);
	if(it != defaultIcons.end()) ret = it->second;
	else{
		auto name = GetDefaultIconName(icon);
		auto iconSurf = GetIconFromResc(GetLocalResc(), name, size);
		ret = iconSurf;
		defaultIcons[cacheKey] = iconSurf;
	};
	bt_unlock(cacheLock);
	return ret;
}

std::shared_ptr<gds::Surface> GetIconFromFile(const std::string &filename, const std::string iconName, size_t size){
	auto cacheKey = IconCacheKey(filename, iconName, size);
	return GetIconFromCache(cacheKey, [&]{
		std::shared_ptr<gds::Surface> ret = nullptr;
		auto h = resc::Resc_FileOpen(filename);
		if(h){
			ret = GetIconFromResc(h, iconName, size);
			resc::Resc_Close(h);
		}
		return ret;
	});
}


static std::string GetOrBlank(const std::map<std::string, std::string> &map, const std::string &key){
	auto it = map.find(key);
	if(it != map.end()) return it->second;
	else return "";
}

static AppInfo GetAppInfo(resc::RescHandle h){
	AppInfo ret;
	auto appInf = resc::Resc_OpenResc(h, "app.inf");
	if(appInf){
		__gnu_cxx::stdio_filebuf<char> filebuf(appInf, std::ios::in);
		std::istream is(&filebuf);
		auto ini = ReadIniFile(is);
		auto appSection = ini.find("app");
		if(appSection != ini.end()){
			ret.name = GetOrBlank(appSection->second, "name");
			ret.category = GetOrBlank(appSection->second, "category");
			ret.vendor = GetOrBlank(appSection->second, "vendor");
			ret.icon = GetOrBlank(appSection->second, "icon");
			ret.mode = GetOrBlank(appSection->second, "mode");
		}
		auto fiSection = ini.find("fileicons");
		if(fiSection != ini.end()){
			for(auto &fi : fiSection->second){
				if(fi.first == "default") ret.defaultFileIcon = fi.second;
				ret.fileIcons[fi.first] = fi.second;
			}
		}
	}
	return ret;
}

std::shared_ptr<gds::Surface> GetElxIcon(const std::string &filename, size_t size){
	resc::RescHandle h = nullptr;
	bt_lock(cacheLock);
	if(!elxIconInfoCache.exists(filename)){
		elxIconInfo info;
		info.useDefault = true;
		h = resc::Resc_FileOpen(filename);
		if(h){
			auto appInfo = GetAppInfo(h);
			if(!appInfo.icon.empty()){
				info.useDefault = false;
				info.path = filename;
				info.name = appInfo.icon;
			}
		}
		elxIconInfoCache.put(filename, info);
	}
	auto info = elxIconInfoCache.get(filename);
	bt_unlock(cacheLock);
	
	std::shared_ptr<gds::Surface> ret;
	if(info.useDefault) ret = GetDefaultIcon(DefaultIcons::Executable, size);
	else {
		auto iconKey = IconCacheKey(info.path, info.name, size);
		ret = GetIconFromCache(iconKey, [&]{
			if(h && info.path == filename) return GetIconFromResc(h, info.name, size);
			else return GetIconFromFile(info.path, info.name, size);
		});
	}
	if(h) resc::Resc_Close(h);
	return ret;
}

std::shared_ptr<gds::Surface> GetPathIcon(const std::string &path, size_t size){
	if(path == "") return GetDefaultIcon(DefaultIcons::Computer, size);
	
	auto entry = bt_stat(path.c_str());
	if(entry.valid){
		if(entry.type == FS_Directory){
			size_t driveSplit = path.find(FS_DRIVE_SEPARATOR);
			if(driveSplit != std::string::npos){
				auto pathPart = path.substr(driveSplit);
				if(pathPart == "" || pathPart == ":" || pathPart == ":/") return GetDefaultIcon(DefaultIcons::Drive, size);
			}
			return GetDefaultIcon(DefaultIcons::Folder, size);	
		}
		if(entry.type == FS_File){
			if(FileExtensionPredicate(".elx")(path)) return GetElxIcon(path, size);
			else{
				std::shared_ptr<gds::Surface> ret;
				auto app = registry::GetPathAssociation(path);
				if(!app.empty()){
					auto info = GetAppInfo(app);
					auto icon = info.defaultFileIcon;
					for(auto &fi : info.fileIcons){
						if(FileExtensionPredicate(fi.first)(path)){
							icon = fi.second;
							break;
						}
					}
					if(!icon.empty()) ret = GetIconFromFile(app, icon, size);
				}
				if(!ret) return GetDefaultIcon(DefaultIcons::File, size);
				return ret;
			}
		}else{
			return GetDefaultIcon(DefaultIcons::Device, size);
		}
	}else{
		return GetDefaultIcon(DefaultIcons::Unknown, size);
	}
}

AppInfo GetAppInfo(const std::string &filename){
	if(appInfoCache.exists(filename)) return appInfoCache.get(filename);
	auto h = resc::Resc_FileOpen(filename);
	if(h){
		auto ret = GetAppInfo(h);
		resc::Resc_Close(h);
		appInfoCache.put(filename, ret);
		return ret;
	}
	return AppInfo();
}

}
}
}