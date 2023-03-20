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
	entries = GetItemsForPath(path, filter);
	
	std::sort(entries.begin(), entries.end(), sortOrder);
	
	auto &items = Items();
	items.clear();
	for(auto &e : entries){
		items.push_back(PathItemTitle(CombinePath({path, e.filename})));
	}
	for(size_t i = 0; i < items.size(); ++i){
		SetItemIcon(i, GetPathIcon(CombinePath({path, entries[i].filename}), folderIconSize));
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
	static bt_directory_entry invalid_directory_entry = {false, 0, {'\0'}, 0, FS_Invalid};
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