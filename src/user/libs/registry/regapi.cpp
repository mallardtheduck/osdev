#include <btos/registry.hpp>
#include <util/rpc.hpp>
#include <btos/envvars.hpp>
#include "../../system/registry/api_types.hpp"

#include <cstdlib>

using std::vector;
using std::string;

namespace btos_api{
namespace registry{

static const string PID_VAR = "REGISTRY_PID";
static bt_pid_t pid = 0;

static void SetPID(){
    if(!pid){
        auto pidstring = GetEnv(PID_VAR);
        pid = strtoull(pidstring.c_str(), NULL, 0);
    }
}

vector<string> GetAllPackages(){
    SetPID();
    return rpc::MakeClient<RPCID::GetAllPackages>(pid, GetAllPackages)();
}

PackageInfo GetPackageById(int64_t id){
    SetPID();
    return rpc::MakeClient<RPCID::GetPackageById>(pid, GetPackageById)(id);
}

PackageInfo GetPackageByName(const string &name){
    SetPID();
    return rpc::MakeClient<RPCID::GetPackageByName>(pid, GetPackageByName)(name);
}

vector<string> GetFeatures(int64_t pkgid){
    SetPID();
    return rpc::MakeClient<RPCID::GetFeatures>(pid, GetFeatures)(pkgid);
}

FeatureInfo GetFeatureById(int64_t id){
    SetPID();
    return rpc::MakeClient<RPCID::GetFeatureById>(pid, GetFeatureById)(id);
}

FeatureInfo GetFeatureByName(const string &name){
    SetPID();
    return rpc::MakeClient<RPCID::GetFeatureByName>(pid, GetFeatureByName)(name);
}

int64_t InstallPackage(const PackageInfo &info){
    SetPID();
    return rpc::MakeClient<RPCID::InstallPackage>(pid, InstallPackage)(info);
}

int64_t InstallFeature(const FeatureInfo &info){
    SetPID();
    return rpc::MakeClient<RPCID::InstallFeature>(pid, InstallFeature)(info);
}


}
}
