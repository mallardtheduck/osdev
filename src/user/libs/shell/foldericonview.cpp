#include <gui/shell/foldericonview.hpp>
#include <gui/shell/utils.hpp>
#include <btos/directory.hpp>

#include <algorithm>

namespace btos_api{
namespace gui{
namespace shell{
	
static const size_t folderIconSize = 32;

static std::string TitleCase(const std::string &text){
	std::string ret;
	for(size_t i = 0; i < text.length(); ++i){
		if(i == 0) ret += std::toupper(text[i]);
		else ret += std::tolower(text[i]);
	}
	return ret;
}
	
FolderIconView::FolderIconView(const gds::Rect &r, const std::string &p, bool multiSelect) : 
IconView(r, folderIconSize, multiSelect), path(p)
{
	Update();
}

void FolderIconView::Update(){
	entries.clear();
	auto dir = Directory(path.c_str(), FS_Read);
	for(auto d : dir) entries.push_back(d);
	
	std::sort(entries.begin(), entries.end(), [](const bt_directory_entry &a, const bt_directory_entry &b){
		if(a.type == FS_Directory && b.type != FS_Directory) return true;
		if(a.type != FS_Directory && b.type == FS_Directory) return false;
		std::string aname = a.filename;
		std::string bname = b.filename;
		return std::lexicographical_compare(aname.begin(), aname.end(), bname.begin(), bname.end(), 
			[](char a, char b){
				return std::tolower(a) < std::tolower(b);	
			}
		);
	});
	
	auto &items = Items();
	items.clear();
	for(auto &e : entries){
		items.push_back(TitleCase(e.filename));
	}
	for(size_t i = 0; i < items.size(); ++i){
		SetItemIcon(i, GetPathIcon(path + "/" + entries[i].filename, folderIconSize));
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

bt_directory_entry FolderIconView::GetSelectedEntry(){
	auto index = GetValue();
	if(index < entries.size()) return entries[index];
	else return invalid_directory_entry;
}
	
}
}
}