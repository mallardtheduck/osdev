#ifndef _PACKAGEFILE_HPP
#define _PACKAGEFILE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <btos/registry.hpp>
#include "tar.hpp"

class PackageFile{
private:
	std::ifstream stream;
	btos_api::registry::PackageInfo packageInfo;
	std::vector<btos_api::registry::FeatureInfo> features;
	
	void Parse();
public:
	PackageFile(const std::string &path);
	
	btos_api::registry::PackageInfo GetInfo();
	std::vector<btos_api::registry::FeatureInfo> GetFeatures();
	
	uint64_t Install(const std::string &path);
};

#endif