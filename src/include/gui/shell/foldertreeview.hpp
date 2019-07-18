#ifndef _FOLDERTREEVIEW_HPP
#define _FOLDERTREEVIEW_HPP

#include <gui/treeview.hpp>

namespace btos_api{
namespace gui{
namespace shell{
	
class FolderTreeView : public TreeView{
private:
	std::map<size_t, std::string> nodePaths;
	std::map<std::string, TreeViewNode> nodeCache;
	size_t idCounter = 0;
	std::string rootPath;
	bool showFiles;
	
	TreeViewNode CreateNode(const std::string &path, bool open = false);
public:
	FolderTreeView(const gds::Rect &r, const std::string &rootPath, bool showFiles = false);
		
	void Update();
	
	std::string GetRootPath();
	void SetRootPath(const std::string &path);
	
	std::string GetSelectedPath();
	void SetSelectedPath(const std::string &path);
};

}
}
}

#endif