#include <gui/iconview.hpp>

namespace btos_api{
namespace gui{
namespace shell{

class FolderIconView : public IconView{
private:
	std::vector<bt_directory_entry> entries;
	std::string path;
public:
	FolderIconView(const gds::Rect &r, const std::string &path, bool multiSelect = false);
	
	void Update();
	
	std::string GetPath();
	void SetPath(const std::string &path);
	
	bt_directory_entry GetSelectedEntry();
};

}
}
}