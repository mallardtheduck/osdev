#include <map>
#include <algorithm>
#include <cctype>

#include <unistd.h>

#include <btos.h>
#include <btos/resc.h>
#include <gds/libgds.h>

#include <gui/shell/utils.hpp>

#include "shell_resc.tar.h"

#include <util/tinyformat.hpp>

namespace btos_api{
namespace gui{
namespace shell{

static std::map<std::string, std::shared_ptr<gds::Surface>> loadedIcons;

static std::shared_ptr<gds::Surface> LoadIcon(const char *path){
	auto i = loadedIcons.find(path);
	if(i == loadedIcons.end()){
		auto r = resc::Resc_LocalOpen(shell_resc_data, shell_resc_size);
		auto fd = resc::Resc_OpenResc(r, path);
		auto ret = GDS_LoadPNG(fd);
		close(fd);
		resc::Resc_Close(r);
		auto s = std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
		i = loadedIcons.insert(loadedIcons.end(), std::make_pair(path, s));
		tfm::printf("Loaded '%s' (%p)\n", path, s.get());
	}
	return i->second;
}

std::shared_ptr<gds::Surface> GetDefaultIcon(DefaultIcons icon, size_t size){
	std::string name = "icons/";
	switch(icon){
		case DefaultIcons::Folder:
			name += "folder";
			break;
		case DefaultIcons::FolderOpen:
			name += "folder_open";
			break;
		case DefaultIcons::File:
			name += "file";
			break;
		case DefaultIcons::Executable:
			name += "default";
			break;
		case DefaultIcons::Computer:
			name += "computer";
			break;
		case DefaultIcons::Drive:
			name += "hdd";
			break;
		case DefaultIcons::Device:
			name += "device";
			break;
		case DefaultIcons::Unknown:
			name += "error";
			break;
		default: return nullptr;
	}
	switch(size){
		case 16:
			name += "_16.png";
			break;
		case 32:
			name += "_32.png";
			break;
		default: return nullptr;
	}
	return LoadIcon(name.c_str());
}

std::shared_ptr<gds::Surface> GetPathIcon(const std::string &path, size_t size){
	auto entry = bt_stat(path.c_str());
	if(entry.valid){
		if(entry.type == FS_Directory) return GetDefaultIcon(DefaultIcons::Folder, size);
		if(entry.type == FS_File){
			bool isElx = false;
			if(path.length() > 4){
				auto ext = path.substr(path.length() - 4);
				std::string dotElx = ".elx";
				isElx = std::equal(ext.begin(), ext.end(), dotElx.begin(), [] (char a, char b){
					return std::tolower(a) == std::tolower(b);
				});
			}
			if(isElx) return GetDefaultIcon(DefaultIcons::Executable, size);
			else return GetDefaultIcon(DefaultIcons::File, size);
		}else{
			return GetDefaultIcon(DefaultIcons::Device, size);
		}
	}else{
		return GetDefaultIcon(DefaultIcons::Unknown, size);
	}
}

}
}
}