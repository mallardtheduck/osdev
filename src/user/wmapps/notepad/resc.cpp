#include "notepad.hpp"
#include "notepad_resc.tar.h"

#include <btos/resc.h>
#include <gds/libgds.h>
#include <unistd.h>

#include <map>

namespace gds = btos_api::gds;
namespace resc = btos_api::resc;

static std::map<std::string, std::shared_ptr<gds::Surface>> loadedIcons;

std::shared_ptr<gds::Surface> LoadIcon(const char *path){
	auto i = loadedIcons.find(path);
	if(i == loadedIcons.end()){
		auto r = resc::Resc_LocalOpen(notepad_resc_data, notepad_resc_size);
		auto fd = resc::Resc_OpenResc(r, path);
		auto ret = GDS_LoadPNG(fd);
		close(fd);
		resc::Resc_Close(r);
		auto s = std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
		i = loadedIcons.insert(loadedIcons.end(), std::make_pair(path, s));
	}
	return i->second;
}