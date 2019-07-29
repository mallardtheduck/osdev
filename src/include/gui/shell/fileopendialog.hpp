#ifndef _FILEOPENDIALOG_HPP
#define _FILEOPENDIALOG_HPP

#include <string>
#include <functional>

#define BTOS_NO_USING
#include <btos.h>

#include <wm/window.hpp>

namespace btos_api{
namespace gui{
namespace shell{

class FileOpenDialog{
private:
	std::string path;
	std::function<bool(const bt_directory_entry &e)> filter;
public:
	FileOpenDialog(const std::string &path = "", std::function<bool(const bt_directory_entry &e)> filter = nullptr);
	
	std::string Show(wm::Window *parent);
};

}
}
}

#endif