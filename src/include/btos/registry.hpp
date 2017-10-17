#ifndef _REGISTRY_HPP
#define _REGISTRY_HPP

#include <string>
#include <cstdint>
#include <vector>

namespace btos_api{
namespace registry{

struct PackageInfo{
	int64_t id;
	std::string name;
	std::string description;
	std::string path;
	std::string ver;
};

struct FeatureInfo{
    int64_t id;
    int64_t package;
    std::string name;
    std::string description;
    std::string type;
    std::string ver;
    std::string path;
    std::string file;
    int64_t flags;
};

namespace RPCID{
    const uint32_t GetAllPackages = 1;
    const uint32_t GetPackageById = 2;
    const uint32_t GetPackageByName = 3;
    const uint32_t GetFeatures = 4;
    const uint32_t GetFeatureById = 5;
    const uint32_t GetFeatureByName = 6;

    const uint32_t InstallPackage = 101;
    const uint32_t InstallFeature = 102;
};

std::vector<std::string> GetAllPackages();
PackageInfo GetPackageById(int64_t id);
PackageInfo GetPackageByName(const std::string &name);
std::vector<std::string> GetFeatures(int64_t pkgid);
FeatureInfo GetFeatureById(int64_t id);
FeatureInfo GetFeatureByName(const std::string &name);

int64_t InstallPackage(const PackageInfo &info);
int64_t InstallFeature(const FeatureInfo &info);

}
}

#endif