#define BTOS_NO_USING

#include "appview.hpp"
#include <btos/registry.hpp>
#include <gui/shell/utils.hpp>

#include <algorithm>
#include <map>

#include <util/tinyformat.hpp>

namespace reg = btos_api::registry;
namespace sh = btos_api::gui::shell;

static std::shared_ptr<btos_api::gds::Surface> GetCategoryIcon(const std::string &name, uint32_t size){
	std::string iconname;
	if(name == "Configuration" || name == "Settings" || name == "System"){
		iconname = "cat_config";
	}else if(name == "Games"){
		iconname = "cat_games";
	}else if(name == "Graphics" || name == "Design"){
		iconname = "cat_graphics";
	}else if(name == "Mulitmedia" || name == "Video" || name == "Audio"){
		iconname = "cat_media";
	}else if(name == "Network" || name == "Internet"){
		iconname = "cat_net";
	}else if(name == "Office" || name == "Applications" || name == "Editors"){
		iconname = "cat_office";
	}else if(name == "Tests"){
		iconname = "cat_tests";
	}else if(name == "Tools" || name == "Utilities"){
		iconname = "cat_tools";
	}else{
		iconname = "category";
	}
	return LoadIcon(tfm::format("icons/%s_%s.png", iconname, size).c_str());
}

static std::map<std::string, Category> categoryCache;
static std::map<std::string, App> appCache;

static void PopulateAppCache(){
	auto feats = reg::GetFeaturesByType("app");
	for(auto &f : feats){
		if(appCache.find(f) == appCache.end()){
			auto feat = reg::GetFeatureByName(f);
			auto path = reg::GetFeaturePath(feat.id);
			auto appInfo = sh::GetAppInfo(path);
			
			App app;
			app.description = appInfo.name;
			app.category = appInfo.category;
			if(app.description.empty()) app.description = feat.description;
			app.path = path;
			app.icon16 = sh::GetPathIcon(path, 16);
			app.icon32 = sh::GetPathIcon(path, 32);
			appCache[f] = app;
		}
	}
}

static void PopulateCategoryCache(){
	PopulateAppCache();
	for(auto &pair : appCache){
		if(categoryCache.find(pair.second.category) == categoryCache.end()){
			Category cat;
			cat.name = pair.second.category;
			cat.icon16 = GetCategoryIcon(cat.name, 16);
			cat.icon32 = GetCategoryIcon(cat.name, 32);
			categoryCache[cat.name] = cat;
		}
	}
}

std::vector<Category> GetCategories(){
	PopulateCategoryCache();
	std::vector<Category> ret;
	std::transform(categoryCache.begin(), categoryCache.end(), std::back_inserter(ret), 
		[](const std::pair<std::string, Category> &pair){
			return pair.second;
		}
	);
	std::sort(ret.begin(), ret.end(), [](const Category &a, const Category &b){
		if(a.name.empty() && !b.name.empty()) return false;
		if(!a.name.empty() && b.name.empty()) return true;
		return a.name < b.name;
	});
	return ret;
}

std::vector<App> GetApps(const std::string &cat){
	PopulateAppCache();
	std::vector<App> ret;
	for(auto &pair : appCache){
		if(pair.second.category == cat) ret.push_back(pair.second);
	}
	std::sort(ret.begin(), ret.end(), [](const App &a, const App &b){
		return a.description < b.description;
	});
	return ret;
}