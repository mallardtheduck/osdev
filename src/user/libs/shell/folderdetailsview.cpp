#include <gui/shell/folderdetailsview.hpp>

#include <gui/shell/utils.hpp>
#include <btos/directory.hpp>

#include <algorithm>

namespace btos_api{
namespace gui{
namespace shell{
	
static const size_t folderIconSize = 16;
	
FolderDetailsView::FolderDetailsView(const gds::Rect &r, const std::string &p, bool multiSelect) : 
DetailList(r, {"Name", "Type", "Size"}, false, folderIconSize, multiSelect), path(p), sortOrder(DirectoryEntryComparator())
{
	Update();
}

static std::vector<std::string> MakeItem(const bt_directory_entry &e){
	std::vector<std::string> ret;
	ret.push_back(TitleCase(e.filename));
	switch(e.type){
		case FS_File:
			ret.push_back("File");
			break;
		case FS_Directory:
			ret.push_back("Directory");
			break;
		case FS_Link:
			ret.push_back("Link");
			break;
		case FS_Device:
			ret.push_back("Device node");
			break;
		default:
			ret.push_back("ERROR!");
			break;
	}
	ret.push_back(FormatSize(e.size));
	return ret;
}

void FolderDetailsView::Update(){
	entries.clear();
	auto dir = Directory(path.c_str(), FS_Read);
	for(auto d : dir){
		if(!filter || filter(d)) entries.push_back(d);
	}
	
	std::sort(entries.begin(), entries.end(), sortOrder);
	
	auto &items = Items();
	items.clear();
	for(auto &e : entries){
		items.push_back(MakeItem(e));
	}
	for(size_t i = 0; i < items.size(); ++i){
		auto folderPath = path;
		if(folderPath.back() != FS_PATH_SEPARATOR) folderPath += FS_PATH_SEPARATOR;
		SetItemIcon(i, GetPathIcon(folderPath + entries[i].filename, folderIconSize));
	}
	
	Refresh();
}

std::string FolderDetailsView::GetPath(){
	return path;
}

void FolderDetailsView::SetPath(const std::string &p){
	path = p;
	Update();
}

void FolderDetailsView::SetSortOrder(std::function<bool(const bt_directory_entry &a, const bt_directory_entry &b)> order){
	sortOrder = order;
}

bt_directory_entry FolderDetailsView::GetSelectedEntry(){
	auto index = GetValue();
	if(index < entries.size()) return entries[index];
	else return invalid_directory_entry;
}

void FolderDetailsView::SetFilter(std::function<bool(const bt_directory_entry &e)> f){
	filter = f;
	Update();
}
	
}
}
}