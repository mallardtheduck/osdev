#ifndef _FOLDERDETAILSVIEW_HPP
#define _FOLDERDETAILSVIEW_HPP

#include <gui/detaillist.hpp>

namespace btos_api{
namespace gui{
namespace shell{

class FolderDetailsView : public DetailList{
private:
	std::vector<bt_directory_entry> entries;
	std::string path;
	std::function<bool(const bt_directory_entry &a, const bt_directory_entry &b)> sortOrder;
	std::function<bool(const bt_directory_entry &e)> filter;
	
	std::vector<std::string> MakeItem(const bt_directory_entry &e);
public:
	FolderDetailsView(const gds::Rect &r, const std::string &path, bool multiSelect = false);
	
	void Update();
	
	std::string GetPath();
	void SetPath(const std::string &path);
	
	void SetSortOrder(std::function<bool(const bt_directory_entry &a, const bt_directory_entry &b)> order);
	void SetFilter(std::function<bool(const bt_directory_entry &e)> filter);
	
	bt_directory_entry GetSelectedEntry();
};
	
}
}
}

#endif