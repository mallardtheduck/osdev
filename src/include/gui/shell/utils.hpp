#ifndef _SHELL_UTILS_HPP
#define _SHELL_UTILS_HPP

#include <memory>
#include <string>
#include <gds/surface.hpp>

namespace btos_api{
namespace gui{
namespace shell{

enum class DefaultIcons{
	Folder, FolderOpen, File, Executable, Computer, Drive, Device, Unknown
};

std::shared_ptr<gds::Surface> GetDefaultIcon(DefaultIcons icon, size_t size);
std::shared_ptr<gds::Surface> GetPathIcon(const std::string &path, size_t size);
std::shared_ptr<gds::Surface> GetIconFromFile(const std::string &filename, const std::string iconName, size_t size);
std::shared_ptr<gds::Surface> GetElxIcon(const std::string &filename, size_t size);

std::string TitleCase(const std::string &text);
std::string PathItemTitle(const std::string &path);
std::vector<std::string> SplitPath(const std::string &path);
std::string CombinePath(const std::vector<std::string> &parts);

template<typename T, typename ...Ts> std::string CombinePath(T a, Ts... args){
	return CombinePath({a, args...});
}

std::string FormatSize(bt_filesize_t size);

std::vector<bt_directory_entry> GetItemsForPath(const std::string &path, std::function<bool(const bt_directory_entry &e)> filter = nullptr);

class DirectoryEntryComparator{
public:
	enum class SortBy{
		Name, Size
	};

	DirectoryEntryComparator(SortBy order = SortBy::Name, bool directoriesFirst = true);
	bool operator()(const bt_directory_entry &a, const bt_directory_entry &b);
private:
	SortBy order;
	bool directoriesFirst;
};

class FileExtensionPredicate{
private:
	std::vector<std::string> extensions;
public:
	explicit FileExtensionPredicate(const std::string &extension);
	FileExtensionPredicate(const std::vector<std::string> &extensions);
	FileExtensionPredicate(const std::initializer_list<const char*> &extensions);
	
	bool operator()(const bt_directory_entry &entry);
	bool operator()(const std::string &filename);
};

}
}
}

#endif