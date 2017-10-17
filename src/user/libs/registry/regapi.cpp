#include <btos/registry.hpp>
#include <util/rpc.hpp>
#include "../../system/registry/api_types.hpp"

using std::vector;
using std::string;

namespace btos_api{
namespace registry{

static bt_pid_t pid;

vector<string> GetAllPackages(){
    return rpc::MakeClient<RPCID::GetAllPackages>(pid, GetAllPackages)();
}

PackageInfo GetPackageById(int64_t id){
    return rpc::MakeClient<RPCID::GetPackageById>(pid, GetPackageById)(id);
}

PackageInfo GetPackageByName(const string &name){
    return rpc::MakeClient<RPCID::GetPackageByName>(pid, GetPackageByName)(name);
}

vector<string> GetFeatures(int64_t pkgid){
    return rpc::MakeClient<RPCID::GetFeatures>(pid, GetFeatures)(pkgid);
}

FeatureInfo GetFeatureById(int64_t id){
    return rpc::MakeClient<RPCID::GetFeatureById>(pid, GetFeatureById)(id);
}

FeatureInfo GetFeatureByName(const string &name){
    return rpc::MakeClient<RPCID::GetFeatureByName>(pid, GetFeatureByName)(name);
}

int64_t InstallPackage(const PackageInfo &info){
    return rpc::MakeClient<RPCID::InstallPackage>(pid, InstallPackage)(info);
}

int64_t InstallFeature(const FeatureInfo &info){
    return rpc::MakeClient<RPCID::InstallFeature>(pid, InstallFeature)(info);
}


}
}
