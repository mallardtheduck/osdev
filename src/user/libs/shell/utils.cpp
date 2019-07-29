#include <map>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <cstring>

#include <unistd.h>

#define BTOS_NO_USING
#include <btos.h>
#include <btos/resc.h>
#include <gds/libgds.h>
#include <btos/directory.hpp>
#include <btos/table.hpp>

#include <gui/shell/utils.hpp>

#include "shell_resc.tar.h"

#include <util/tinyformat.hpp>

namespace btos_api{
namespace gui{
namespace shell{

static std::map<std::string, std::shared_ptr<gds::Surface>> loadedIcons;

std::shared_ptr<gds::Surface> LoadIcon(const char *path){
	auto i = loadedIcons.find(path);
	if(i == loadedIcons.end()){
		auto r = resc::Resc_LocalOpen(shell_resc_data, shell_resc_size);
		auto fd = resc::Resc_OpenResc(r, path);
		auto ret = GDS_LoadPNG(fd);
		close(fd);
		resc::Resc_Close(r);
		auto s = std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
		i = loadedIcons.insert(loadedIcons.end(), std::make_pair(path, s));
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

static bool char_islower(char ch)
{
    return std::islower(static_cast<unsigned char>(ch));
}

static bool char_isupper(char ch)
{
    return std::isupper(static_cast<unsigned char>(ch));
}

static bool char_isspace(char ch)
{
    return std::isspace(static_cast<unsigned char>(ch));
}

std::string TitleCase(const std::string &text){
	if(std::any_of(text.begin(), text.end(), char_islower) && std::any_of(text.begin(), text.end(), char_isupper)) return text;
	
	std::string ret;
	bool capNext = true;
	for(size_t i = 0; i < text.length(); ++i){
		auto c = text[i];
		if(capNext) ret += std::toupper(c);
		else ret += std::tolower(c);
		capNext = char_isspace(c);
	}
	return ret;
}

std::string PathItemTitle(const std::string &path){
	if(path == "") return "Computer";
	
	auto parts = SplitPath(path);
	return TitleCase(parts.back());
}

std::vector<std::string> SplitPath(const std::string &path){
	std::vector<std::string> ret;
	if(path == "") return ret;
	
	size_t driveSplit = path.find(FS_DRIVE_SEPARATOR);
	if (driveSplit != std::string::npos) {
		driveSplit += 1;
		ret.push_back(path.substr(0, driveSplit) + FS_PATH_SEPARATOR);
	} else {
		driveSplit = 0;
	}
	size_t lPos = driveSplit;
	size_t curPos = driveSplit;
	while ((curPos = path.find(FS_PATH_SEPARATOR, lPos)) != std::string::npos) {
		if(lPos != curPos) ret.push_back(path.substr(lPos, curPos - lPos));
		lPos = curPos + 1;
	}
	if (lPos < path.length()) ret.push_back(path.substr(lPos));
	return ret;
}

std::string CombinePath(const std::vector<std::string> &parts){
	std::string ret;
	for(const auto &p : parts){
		if(!ret.empty() && ret.back() != FS_PATH_SEPARATOR) ret += FS_PATH_SEPARATOR;
		ret += p;
	}
	return ret;
}

std::string FormatSize(bt_filesize_t size){
	if(size < 1024ll) return tfm::format("%s bytes", size);
	if(size < (10 * 1024ll)) return tfm::format("%.1f KB", size / 1024.0);
	if(size < (1024ll * 1024ll)) return tfm::format("%s KB", size / 1024ll);
	if(size < (10 * 1024ll * 1024ll)) return tfm::format("%.1f MB", size / (1024.0 * 1024.0));
	if(size < (1024ll * 1024ll * 1024ll)) return tfm::format("%s MB", size / (1024ll * 1024ll));
	if(size < (10 * 1024 * 1024ll * 1024ll)) return tfm::format("%.1f GB", size / (1024.0 * 1024.0 * 1024.0));
	if(size < (1024ll * 1024ll * 1024ll * 1024ll)) return tfm::format("%s GB", size / (1024ll * 1024ll * 1024ll));
	if(size < (10 * 1024ll * 1024ll * 1024ll * 1024ll)) return tfm::format("%.1f TB", size / (1024.0 * 1024.0 * 1024.0 * 1024.0));
	if(size < (1024ll * 1024ll * 1024ll * 1024ll * 1024ll)) return tfm::format("%s TB", size / (1024ll * 1024ll * 1024ll * 1024ll));
	if(size < (10 * 1024ll * 1024ll * 1024ll * 1024ll * 1024ll)) return tfm::format("%.1f PB", size / (1024.0 * 1024.0 * 1024.0 * 1024.0 * 1024.0));
	return tfm::format("%s PB", size / (1024ll * 1024ll * 1024ll * 1024ll * 1024ll));
}

std::vector<bt_directory_entry> GetItemsForPath(const std::string &path, std::function<bool(const bt_directory_entry &e)> filter){
	std::vector<bt_directory_entry> entries;
	if(path == ""){
		uint64_t idCounter = 0;
		std::ifstream mountsFile("INFO:/MOUNTS");
		auto mounts = parsecsv(mountsFile);
		for(auto &r : mounts.rows){
			bt_directory_entry entry;
			entry.valid = true;
			std::string filename = r["name"] + ":/";
			strncpy(entry.filename, filename.c_str(), BT_MAX_SEGLEN);
			entry.type = FS_Directory;
			entry.size = 0;
			entry.id = ++idCounter;
			entries.push_back(entry);
		}
	}else{
		auto dir = Directory(path.c_str(), FS_Read);
		for(auto d : dir){
			if(!filter || filter(d)) entries.push_back(d);
		}
	}
	return entries;
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