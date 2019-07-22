#ifndef _FOLDERICONVIEW_HPP
#define _FOLDERICONVIEW_HPP

#include <gui/iconview.hpp>

namespace btos_api{
namespace gui{
namespace shell{

class FolderIconView : public IconView{
private:
	std::vector<bt_directory_entry> entries;
	std::string path;
	std::function<bool(const bt_directory_entry &a, const bt_directory_entry &b)> sortOrder;
public:
	FolderIconView(const gds::Rect &r, const std::string &path, bool multiSelect = false);
	
	void Update();
	
	std::string GetPath();
	void SetPath(const std::string &path);
	
	void SetSortOrder(std::function<bool(const bt_directory_entry &a, const bt_directory_entry &b)> order);
	
	bt_directory_entry GetSelectedEntry();
};

}
}
}

#endif