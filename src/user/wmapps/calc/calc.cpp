#define BTOS_NO_USING

#include <btos/resc.h>
#include <unistd.h>

#include "calc_resc.tar.h"
#include "stdmode.hpp"
#include "calc.hpp"

namespace gds = btos_api::gds;
namespace resc = btos_api::resc;

resc::RescHandle rsc;

std::shared_ptr<gds::Surface> LoadPNG(const char *path){
	auto fd = resc::Resc_OpenResc(rsc, path);
	auto ret = GDS_LoadPNG(fd);
	close(fd);
	return std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
}

int main(){
	rsc = resc::Resc_LocalOpen(calc_resc_data, calc_resc_size);
	
	StandardMode m;
	m.Show();
	
	resc::Resc_Close(rsc);
	return 0;
}