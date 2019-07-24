#include <gui/shell/foldertreeview.hpp>
#include <gui/shell/utils.hpp>
#include <btos/directory.hpp>

#include <algorithm>

namespace btos_api{
namespace gui{
namespace shell{

TreeViewNode FolderTreeView::CreateNode(const std::string &path, bool open){
	const auto FTVNodeFunction = [&](TreeViewNode &node){
		auto path = nodePaths[node.id];
		
		std::vector<bt_directory_entry> entries = GetItemsForPath(path);
		std::sort(entries.begin(), entries.end(), sortOrder);
		
		node.children.clear();	
		for(const auto &d : entries){
			if(showFiles || d.type == FS_Directory){
				auto fullPath = CombinePath({path, d.filename});
				auto it = nodeCache.find(fullPath);
				if(it == nodeCache.end()){
					nodeCache[fullPath] = CreateNode(fullPath);
					it = nodeCache.find(fullPath);
				}
				node.children.push_back(it->second);
			}
		}
		node.open = true;
	};
	
	auto id = ++idCounter;
	while(nodePaths.find(id) != nodePaths.end()) id = ++idCounter;
	nodePaths[id] = path;
	
	auto name = PathItemTitle(path);
	auto icon = GetPathIcon(path, 16);
	auto openIcon = icon;
	if(icon == GetDefaultIcon(DefaultIcons::Folder, 16)){
		openIcon = GetDefaultIcon(DefaultIcons::FolderOpen, 16);
	}
	
	auto node = TreeViewNode(id, name, {}, icon, openIcon, open);
	node.onOpen = FTVNodeFunction;
	if(open) node.onOpen(node);
	return node;
}

FolderTreeView::FolderTreeView(const gds::Rect &r, const std::string &rP, bool sF)
:TreeView(r), rootPath(rP), showFiles(sF), sortOrder(DirectoryEntryComparator())
{
	Update();
}

void FolderTreeView::Update(){
	auto rootNode = CreateNode(rootPath, true);
	Items().clear();
	Items().push_back(rootNode);
	Refresh();
}

std::string FolderTreeView::GetRootPath(){
	return rootPath;
}

void FolderTreeView::SetRootPath(const std::string &path){
	rootPath = path;
	Update();
}

void FolderTreeView::SetSortOrder(std::function<bool(const bt_directory_entry &a, const bt_directory_entry &b)> order){
	sortOrder = order;
}

std::string FolderTreeView::GetSelectedPath(){
	auto value = GetValue();
	if(value){
		return nodePaths[value->id];
	}else{
		return "";
	}
}

void FolderTreeView::SetSelectedPath(const std::string &path){
	if(path.length() >= rootPath.length()){
		if(path == rootPath) SetValue(&Items()[0]);
		else if(rootPath == "" || path.substr(0, rootPath.length()) == rootPath){
			auto relPath = rootPath == "" ? path : path.substr(rootPath.length());
			auto parts = SplitPath(relPath);
			auto rootNode = CreateNode(rootPath, true);
			
			TreeViewNode *cNode = &rootNode;
			for(auto &p : parts){
				bool found = false;
				for(auto &c : cNode->children){
					if(c.text == TitleCase(p)){
						c.onOpen(c);
						cNode = &c;
						found = true;
						break;
					}
				}
				if(!found) break;
			}
			Items().clear();
			Items().push_back(std::move(rootNode));
			Refresh();
			SetValue(cNode);
		}
	}
}

}
}
}