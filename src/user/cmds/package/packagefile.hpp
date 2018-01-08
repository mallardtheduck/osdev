#ifndef _PACKAGEFILE_HPP
#define _PACKAGEFILE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <btos/registry.hpp>
#include "tar.hpp"

class PackageFile{
public:
	struct ContentFile{
		std::string path;
		uint64_t offset;
		uint64_t size;
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
	
	void Parse();
	void ParseContent();
public:
	PackageFile(const std::string &path);
	
	btos_api::registry::PackageInfo GetInfo();
	std::vector<btos_api::registry::FeatureInfo> GetFeatures();
	std::vector<ContentFile> GetContent();
	
	InstallStatus Install(const std::string &path);
};

#endif