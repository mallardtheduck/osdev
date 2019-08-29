#ifndef _APPVIEW_HPP
#define _APPVIEW_HPP

#include <memory>
#include <vector>
#include <string>

#include <gds/surface.hpp>

std::shared_ptr<btos_api::gds::Surface> LoadIcon(const char *path);

struct Category{
	std::string name;
	std::shared_ptr<btos_api::gds::Surface> icon16;
	std::shared_ptr<btos_api::gds::Surface> icon32;
};

struct App{
	std::string description;
	std::string path;
	std::shared_ptr<btos_api::gds::Surface> icon16;
	std::shared_ptr<btos_api::gds::Surface> icon32;
};

std::vector<Category> GetCategories();
std::vector<App> GetApps(const std::string &cat);

#endif