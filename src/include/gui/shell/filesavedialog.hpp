#ifndef _FILESAVEDIALOG_HPP
#define _FILESAVEDIALOG_HPP

#include <string>
#include <functional>

#define BTOS_NO_USING
#include <btos.h>

#include <wm/window.hpp>
#include <gui/idialog.hpp>

namespace btos_api{
namespace gui{
namespace shell{

class FileSaveDialog : public IDialog<std::string>{
private:
	std::string filename;
	std::string defaultExt;
	std::string path;
	std::function<bool(const bt_directory_entry &e)> filter;
public:
	FileSaveDialog(const std::string &filename, const std::string &defaultExt, const std::string &path = "", std::function<bool(const bt_directory_entry &e)> filter = nullptr);
	
	std::string Show(wm::Window *parent) override;
};

}
}
}

#endif