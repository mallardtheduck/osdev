#ifndef _FOLDERSELECTDIALOG_HPP
#define _FOLDERSELECTDIALOG_HPP

#include <string>
#include <functional>

#define BTOS_NO_USING
#include <btos.h>

#include <wm/window.hpp>
#include <gui/idialog.hpp>

namespace btos_api{
namespace gui{
namespace shell{

class FolderSelectDialog : public IDialog<std::string>{
private:
	std::string defPath;
public:
	FolderSelectDialog(const std::string &path = "");
	
	std::string Show(wm::Window *parent) override;
};

}
}
}

#endif