#ifndef _PACKAGEFILE_HPP
#define _PACKAGEFILE_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <btos/registry.hpp>
#include "tar.hpp"

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
	
	InstallStatus Install(const std::string &path);
	bool CheckVersion(InstallStatus &status);
	bool CheckPathConflicts(InstallStatus &status, const std::string &path);
	bool CheckFeatureConflicts(InstallStatus &status);
	
	bool ExtractFiles(InstallStatus &status, const std::string &path);
	bool ImportInfo(InstallStatus &status, const std::string &path);
	
	bool RunHook(InstallStatus &status, const std::string &hook);
};

#endif