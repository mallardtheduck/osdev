#ifndef _CALC_HPP
#define _CALC_HPP

#include <memory>
#include <gds/libgds.h>

std::shared_ptr<btos_api::gds::Surface> LoadPNG(const char *path);

#endif