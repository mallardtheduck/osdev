#ifndef _NOTEPAD_HPP
#define _NOTEPAD_HPP

#include <memory>
#include <gds/surface.hpp>

std::shared_ptr<btos_api::gds::Surface> LoadIcon(const char *path);

#endif