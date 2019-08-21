#ifndef _FOLDER_HPP
#define _FOLDER_HPP

#define BTOS_NO_USING

#include <memory>
#include <string>
#include <wm/window.hpp>
#include <gds/surface.hpp>

std::shared_ptr<btos_api::gds::Surface> LoadIcon(const char *path);
void CopyMove(const std::string from, const std::string to, bool move, btos_api::wm::Window *parent);

#endif