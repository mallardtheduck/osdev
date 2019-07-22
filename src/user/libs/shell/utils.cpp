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
		if(entry.type == FS_Directory){
			size_t driveSplit = path.find(FS_DRIVE_SEPARATOR);
			if(driveSplit != std::string::npos){
				auto pathPart = path.substr(driveSplit);
				if(pathPart == "" || pathPart == ":" || pathPart == ":/") return GetDefaultIcon(DefaultIcons::Drive, size);
			}
			return GetDefaultIcon(DefaultIcons::Folder, size);	
		}
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

std::string TitleCase(const std::string &text){
	std::string ret;
	bool capNext = true;
	for(size_t i = 0; i < text.length(); ++i){
		auto c = text[i];
		if(capNext) ret += std::toupper(c);
		else ret += std::tolower(c);
		capNext = (c == ' ');
	}
	return ret;
}

DirectoryEntryComparator::DirectoryEntryComparator(SortBy o, bool dF)
: order(o), directoriesFirst(dF)
{}

bool DirectoryEntryComparator::operator()(const bt_directory_entry &a, const bt_directory_entry &b){
	if(directoriesFirst){
		if(a.type == FS_Directory && b.type != FS_Directory) return true;
		if(a.type != FS_Directory && b.type == FS_Directory) return false;
	}
	switch(order){
		case SortBy::Name:{
			std::string aname = a.filename;
			std::string bname = b.filename;
			return std::lexicographical_compare(aname.begin(), aname.end(), bname.begin(), bname.end(), 
				[](char a, char b){
					return std::tolower(a) < std::tolower(b);	
				}
			);
		}
		case SortBy::Size:
			return a.size < b.size;
		default:
			return false;
	}
}

}
}
}