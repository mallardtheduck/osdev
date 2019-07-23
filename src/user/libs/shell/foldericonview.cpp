#include <gui/shell/foldericonview.hpp>
#include <gui/shell/utils.hpp>
#include <btos/directory.hpp>

#include <algorithm>

namespace btos_api{
namespace gui{
namespace shell{
	
static const size_t folderIconSize = 32;
	
FolderIconView::FolderIconView(const gds::Rect &r, const std::string &p, bool multiSelect) : 
IconView(r, folderIconSize, multiSelect), path(p), sortOrder(DirectoryEntryComparator())
{
	Update();
}

void FolderIconView::Update(){
	entries.clear();
	auto dir = Directory(path.c_str(), FS_Read);
	for(auto d : dir){
		if(!filter || filter(d)) entries.push_back(d);
	}
	
	std::sort(entries.begin(), entries.end(), sortOrder);
	
	auto &items = Items();
	items.clear();
	for(auto &e : entries){
		items.push_back(TitleCase(e.filename));
	}
	for(size_t i = 0; i < items.size(); ++i){
		auto folderPath = path;
		if(folderPath.back() != FS_PATH_SEPARATOR) folderPath += FS_PATH_SEPARATOR;
		SetItemIcon(i, GetPathIcon(folderPath + entries[i].filename, folderIconSize));
	}
	
	Refresh();
}

std::string FolderIconView::GetPath(){
	return path;
}

void FolderIconView::SetPath(const std::string &p){
	path = p;
	Update();
}

void FolderIconView::SetSortOrder(std::function<bool(const bt_directory_entry &a, const bt_directory_entry &b)> order){
	sortOrder = order;
}

bt_directory_entry FolderIconView::GetSelectedEntry(){
	auto index = GetValue();
	if(index < entries.size()) return entries[index];
	else return invalid_directory_entry;
}

void FolderIconView::SetFilter(std::function<bool(const bt_directory_entry &e)> f){
	filter = f;
	Update();
}
	
}
}
}