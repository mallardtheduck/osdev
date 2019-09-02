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

struct FileTypeInfo{
    int64_t id;
    int64_t package;
    std::string extension;
    std::string mimeType;
};

struct AssociationInfo{
    int64_t id;
    int64_t package;
    int64_t feature;
    int64_t fileType;
    std::string description;
    std::string cmdTemplate;
};

namespace RPCID{
    const uint32_t GetAllPackages = 1;
    const uint32_t GetPackageById = 2;
    const uint32_t GetPackageByName = 3;
    const uint32_t GetFeatures = 4;
    const uint32_t GetFeatureById = 5;
    const uint32_t GetFeatureByName = 6;
    const uint32_t GetFeaturesByType = 7;
    const uint32_t GetFeatureAssociation = 8;
    const uint32_t GetPathAssociation = 9;
    const uint32_t GetPackageByPath = 10;
    const uint32_t GetSubPackages = 11;

    const uint32_t InstallPackage = 101;
    const uint32_t InstallFeature = 102;
    const uint32_t InstallFileType = 103;
    const uint32_t InstallAssociation = 104;

    const uint32_t UpdatePackage = 201;
    const uint32_t UpdateFeature = 201;
    
    const uint32_t DeletePackage = 301;
    const uint32_t DeleteFeature = 302;

    const uint32_t RunScript = 900;
    const uint32_t BackupRegistry = 901;
};

std::vector<std::string> GetAllPackages();
PackageInfo GetPackageById(int64_t id);
PackageInfo GetPackageByName(const std::string &name);
std::vector<std::string> GetFeatures(int64_t pkgid);
FeatureInfo GetFeatureById(int64_t id);
FeatureInfo GetFeatureByName(const std::string &name);
std::vector<std::string> GetFeaturesByType(const std::string &type);
std::string GetFeatureAssociation(const std::string &path);
std::string GetPathAssociation(const std::string &path);
PackageInfo GetPackageByPath(const std::string &path);
std::vector<std::string> GetSubPackages(int64_t pkgid);

int64_t InstallPackage(const PackageInfo &info);
int64_t InstallFeature(const FeatureInfo &info);
int64_t InstallFileType(const FileTypeInfo &info);
int64_t InstallAssociation(const AssociationInfo &info);

void UpdatePackage(const PackageInfo &info);
void UpdateFeature(const FeatureInfo &info);

void DeletePackage(int64_t pkgid);
void DeleteFeature(int64_t featid);

std::vector<int> RunScript(const std::vector<std::string> &sql);
void BackupRegistry(const std::string &path);

std::string GetFeaturePath(uint64_t id);

}
}

#endif