#define BTOS_NO_USING

#include "appview.hpp"
#include <btos/registry.hpp>
#include <gui/shell/utils.hpp>

#include <algorithm>

namespace reg = btos_api::registry;
namespace sh = btos_api::gui::shell;

std::vector<Category> GetCategories(){
	std::vector<Category> ret;
	std::vector<std::string> catNames;
	auto feats = reg::GetFeaturesByType("app");
	for(auto &f : feats){
		auto feat = reg::GetFeatureByName(f);
		auto path = reg::GetFeaturePath(feat.id);
		auto appInfo = sh::GetAppInfo(path);
		if(std::find(catNames.begin(), catNames.end(), appInfo.category) == catNames.end()){
			catNames.push_back(appInfo.category);
			Category cat;
			cat.name = appInfo.category;
			cat.icon16 = LoadIcon("icons/category_16.png");
			cat.icon32 = LoadIcon("icons/category_32.png");
			ret.push_back(cat);
		} 
	}
	std::sort(ret.begin(), ret.end(), [](const Category &a, const Category &b){
		if(a.name.empty() && !b.name.empty()) return false;
		if(!a.name.empty() && b.name.empty()) return true;
		return a.name < b.name;
	});
	return ret;
}

std::vector<App> GetApps(const std::string &cat){
	std::vector<App> ret;
	auto feats = reg::GetFeaturesByType("app");
	for(auto &f : feats){
		auto feat = reg::GetFeatureByName(f);
		auto path = reg::GetFeaturePath(feat.id);
		auto appInfo = sh::GetAppInfo(path);
		
		if(appInfo.category == cat){
			App app;
			app.description = appInfo.name;
			if(app.description.empty()) app.description = feat.description;
			app.path = path;
			app.icon16 = sh::GetPathIcon(path, 16);
			app.icon32 = sh::GetPathIcon(path, 32);
			ret.push_back(app);
		}
	}
	std::sort(ret.begin(), ret.end(), [](const App &a, const App &b){
		return a.description < b.description;
	});
	return ret;
}