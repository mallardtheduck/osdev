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

vector<string> GetFeaturesByType(const string &type){
    SetPID();
    return rpc::MakeClient<RPCID::GetFeaturesByType>(pid, GetFeaturesByType)(type);
}

string GetFeatureAssociation(const string &path){
    SetPID();
    return rpc::MakeClient<RPCID::GetFeatureAssociation>(pid, GetFeatureAssociation)(path);
}

string GetPathAssociation(const string &path){
    SetPID();
    return rpc::MakeClient<RPCID::GetPathAssociation>(pid, GetPathAssociation)(path);
}

PackageInfo GetPackageByPath(const string &path){
	SetPID();
	return rpc::MakeClient<RPCID::GetPackageByPath>(pid, GetPackageByPath)(path);
}

vector<string> GetSubPackages(int64_t pkgid){
	SetPID();
	return rpc::MakeClient<RPCID::GetSubPackages>(pid, GetSubPackages)(pkgid);
}

int64_t InstallPackage(const PackageInfo &info){
    SetPID();
    return rpc::MakeClient<RPCID::InstallPackage>(pid, InstallPackage)(info);
}

int64_t InstallFeature(const FeatureInfo &info){
    SetPID();
    return rpc::MakeClient<RPCID::InstallFeature>(pid, InstallFeature)(info);
}

int64_t InstallFileType(const FileTypeInfo &info){
    SetPID();
    return rpc::MakeClient<RPCID::InstallFileType>(pid, InstallFileType)(info);
}

int64_t InstallAssociation(const AssociationInfo &info){
    SetPID();
    return rpc::MakeClient<RPCID::InstallAssociation>(pid, InstallAssociation)(info);
}

void UpdatePackage(const PackageInfo &info){
    SetPID();
    rpc::MakeClient<RPCID::UpdatePackage>(pid, UpdatePackage)(info);
}

void UpdateFeature(const FeatureInfo &info){
    rpc::MakeClient<RPCID::UpdateFeature>(pid, UpdateFeature)(info);
}

vector<int> RunScript(const vector<string> &sql){
    SetPID();
    return rpc::MakeClient<RPCID::RunScript>(pid, RunScript)(sql);
}

void BackupRegistry(const string &path){
    SetPID();
    rpc::MakeClient<RPCID::BackupRegistry>(pid, BackupRegistry)(path);
}

void DeletePackage(int64_t pkgid){
	SetPID();
	rpc::MakeClient<RPCID::DeletePackage>(pid, DeletePackage)(pkgid);
}

void DeleteFeature(int64_t featid){
	SetPID();
	rpc::MakeClient<RPCID::DeleteFeature>(pid, DeleteFeature)(featid);
}


}
}
