#ifndef _PACKAGEFILE_HPP
#define _PACKAGEFILE_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <functional>
#include <btos/registry.hpp>
#include "tar.hpp"

struct InstallProgress{
	size_t steps;
	size_t step;
	std::string desc;
};

typedef std::function<void(const InstallProgress &)> ProgressFunc;
static const auto nullProgressFn = [](const InstallProgress &){};

class PackageFile{
public:
	struct ContentFile{
		std::string path;
		uint64_t offset;
		uint64_t size;
		uint32_t type;
	};
	struct InstallStatus{
		bool success;
		uint64_t package_id;
		std::vector<std::string> messages;
	};
	typedef ::InstallProgress InstallProgress;
	
private:
	std::ifstream stream;
	btos_api::registry::PackageInfo packageInfo;
	std::vector<btos_api::registry::FeatureInfo> features;
	std::string contentPath;
	std::vector<ContentFile> content;
	std::map<std::string, std::string> hooks;
	
	void Parse();
	void ParseContent();
public:
	PackageFile(const std::string &path);
	
	btos_api::registry::PackageInfo GetInfo();
	std::vector<btos_api::registry::FeatureInfo> GetFeatures();
	std::vector<ContentFile> GetContent();
	
	InstallStatus Install(const std::string &path, ProgressFunc progressFn = nullProgressFn);
	bool CheckVersion(InstallStatus &status);
	bool CheckPathConflicts(InstallStatus &status, const std::string &path);
	bool CheckFeatureConflicts(InstallStatus &status);
	
	bool ExtractFiles(InstallStatus &status, const std::string &path, ProgressFunc progressFn = nullProgressFn);
	bool ImportInfo(InstallStatus &status, const std::string &path);
	
	bool RunHook(InstallStatus &status, const std::string &hook, const std::string &path);
};

#endif