#include <map>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <cstring>
#include <functional>

#define BTOS_NO_USING
#include <btos.h>
#include <btos/directory.hpp>
#include <btos/table.hpp>

#include <gui/shell/utils.hpp>

#include <util/tinyformat.hpp>
#include <btos/registry.hpp>
#include <btos/process.hpp>

namespace btos_api{
namespace gui{
namespace shell{

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

bt_pid_t Launch(const std::string &path){
	auto app = registry::GetPathAssociation(path);
	if(!app.empty()){
		Process p = Process::Spawn(app, {path});
		return p.GetPID();
	}
	return 0;
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

template<typename R, typename T> static R rangeConvert(const T &range){
	R ret;
	for(auto &v : range) ret.insert(ret.end(), v);
	return ret;
}

FileExtensionPredicate::FileExtensionPredicate(const std::string &e) : FileExtensionPredicate(std::vector<std::string>{e}) {}
FileExtensionPredicate::FileExtensionPredicate(const std::vector<std::string> &exts) : extensions(exts) {}
FileExtensionPredicate::FileExtensionPredicate(const std::initializer_list<const char*> &exts) : 
	extensions(rangeConvert<std::vector<std::string>>(exts)) {}
	
bool FileExtensionPredicate::operator()(const bt_directory_entry &entry){
	if(entry.type == FS_Directory) return true;
	
	std::string filename = entry.filename;
	return operator()(filename);
}

bool FileExtensionPredicate::operator()(const std::string &filename){
	for(auto &ext : extensions){
		if(filename.length() > ext.length()){
			auto extPart = filename.substr(filename.length() - ext.length());
			if(std::equal(extPart.begin(), extPart.end(), ext.begin(), [](char a, char b){
				return std::tolower(a) == std::tolower(b);
			})) return true;
		}
	}
	return false;
}

}
}
}