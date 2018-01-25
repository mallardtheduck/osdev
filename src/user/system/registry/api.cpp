#include <util/rpc.hpp>
#include <btos/imessagehandler.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "tables.hpp"
#include "api_types.hpp"
#include "registry.hpp"

using std::vector;
using std::string;
using std::shared_ptr;

namespace btos_api{
namespace registry{

PackageInfo ToInfo(const Package &pkg){
	PackageInfo ret;
	ret.id = pkg.id;
	ret.name = pkg.name;
	ret.description = pkg.description;
	ret.path = pkg.path;
	ret.ver = pkg.ver;
	return ret;
}

FeatureInfo ToInfo(const Feature &feat){
	FeatureInfo fi;
	fi.id = feat.id;
	fi.package = feat.package.key;
	fi.name = feat.name;
	fi.description = feat.description;
	fi.type = feat.type;
	fi.ver = feat.ver;
	fi.path = feat.path;
	fi.file = feat.file;
	fi.flags = feat.flags;
	return fi;
}

vector<string> GetAllPackages(){
	auto pkgs = sqlentity::GetAll<Package>(db);
	vector<string> ret;
	for(auto &p : pkgs){
		ret.push_back(p.name);
	}
	return ret;
}

PackageInfo GetPackageById(int64_t id){
	auto pkg = sqlentity::GetByKey<Package>(db, id);
	return ToInfo(pkg);
}

PackageInfo GetPackageByName(const string &name){
	auto pkg = sqlentity::GetWhere<Package>(db, "name = @name", {{"name", name}});
	return ToInfo(pkg);
}

vector<string> GetFeatures(int64_t pkgid){
	auto pkg = sqlentity::GetByKey<Package>(db, pkgid);
	auto feats = pkg.Features(db);
	vector<string> ret;
	for(auto &f : feats){
		ret.push_back(f.name);
	}
	return ret;
}

int64_t InstallPackage(const PackageInfo &info){
	Package pkg;
	pkg.name = info.name;
	pkg.description = info.description;
	pkg.path = info.path;
	pkg.ver = info.ver;
	pkg.Save(db);
	return pkg.id;
}

int64_t InstallFeature(const FeatureInfo &info){
	Feature feat;
	feat.package.key = info.package;
	feat.name = info.name;
	feat.description = info.description;
	feat.type = info.type;
	feat.ver = info.ver;
	feat.path = info.path;
	feat.file = info.file;
	feat.flags = info.flags;
	feat.Save(db);
	return feat.id;
}

void UpdatePackage(const PackageInfo &info){
	auto pkg = sqlentity::GetByKey<Package>(db, info.id);
	pkg.name = info.name;
	pkg.description = info.description;
	pkg.path = info.path;
	pkg.ver = info.ver;
	pkg.Save(db);
}

void UpdateFeature(const FeatureInfo &info){
	auto feat = sqlentity::GetByKey<Feature>(db, info.id);
	feat.package.key = info.package;
	feat.name = info.name;
	feat.description = info.description;
	feat.type = info.type;
	feat.ver = info.ver;
	feat.path = info.path;
	feat.file = info.file;
	feat.flags = info.flags;
	feat.Save(db);
}

FeatureInfo GetFeatureById(int64_t id){
	auto feat = sqlentity::GetByKey<Feature>(db, id);
	return ToInfo(feat);
}

FeatureInfo GetFeatureByName(const string &name){
	auto feat = sqlentity::GetWhere<Feature>(db, "name = @name", {{"name", name}});
	return ToInfo(feat);
}

vector<string> GetFeaturesByType(const string &type){
	vector<string> ret;
	auto feats = sqlentity::GetAllWhere<Feature>(db, "type = @type", {{"type", type}});
	for(auto &f : feats){
		ret.push_back(f.name);
	}
	return ret;
}

string GetFeatureAssociation(const string &path){
	auto feat = GetAssociation(path);
	return feat.name;
}

string GetPathAssociation(const string &path){
	auto feat = GetAssociation(path);
	if(feat.id > 0){
		auto pkg = feat.package.Get(db);
		if(pkg.id > 0){
			return pkg.path + feat.path + feat.file;
		}
	}
	return "";
}

PackageInfo GetPackageByPath(const string &path){
	auto pkg = sqlentity::GetWhere<Package>(db, "path LIKE @path", {{"path", path}});
	return ToInfo(pkg);
}

vector<string> GetSubPackages(int64_t pkgid){
	auto pkg = sqlentity::GetByKey<Package>(db, pkgid);
	string pattern = pkg.path + "/%";
	auto pkgs = sqlentity::GetAllWhere<Package>(db, "path LIKE @path", {{"path", pattern}});
	vector<string> ret;
	for(auto &p : pkgs){
		ret.push_back(p.name);
	}
	return ret;
}

void DeletePackage(int64_t pkgid){
	auto pkg = sqlentity::GetByKey<Package>(db, pkgid);
	pkg.Delete(db);
}

void DeleteFeature(int64_t pkgid){
	auto feat = sqlentity::GetByKey<Feature>(db, pkgid);
	feat.Delete(db);
}

vector<int> RunScript(const vector<string> &sql){
	vector<int> ret;
	for(auto &s : sql){
		if(s == "") ret.push_back(0);
		else ret.push_back(sqlitepp::query(db, s).exec());
		if(ret.back() == 100) ret.back() = 0;
	}
	return ret;
}

void BackupRegistry(const string &path){
	db.backup(path);
}

template<uint32_t id, typename F> void AddAPI(vector<shared_ptr<IMessageHandler>> &vec, F fn){
	shared_ptr<IMessageHandler> ptr { rpc::NewProcServer<id>(rpc::make_function(fn)) };
	vec.push_back(ptr);
}

vector<shared_ptr<IMessageHandler>> InitAPI(){
	vector<shared_ptr<IMessageHandler>> ret;
	AddAPI<RPCID::GetAllPackages>(ret, &GetAllPackages);
	AddAPI<RPCID::GetPackageById>(ret, &GetPackageById);
	AddAPI<RPCID::GetPackageByName>(ret, &GetPackageByName);
	AddAPI<RPCID::GetFeatures>(ret, &GetFeatures);
	AddAPI<RPCID::GetFeatureById>(ret, &GetFeatureById);
	AddAPI<RPCID::GetFeatureByName>(ret, &GetFeatureByName);
	AddAPI<RPCID::GetFeaturesByType>(ret, &GetFeaturesByType);
	AddAPI<RPCID::GetFeatureAssociation>(ret, &GetFeatureAssociation);
	AddAPI<RPCID::GetPathAssociation>(ret, &GetPathAssociation);
	AddAPI<RPCID::GetPackageByPath>(ret, &GetPackageByPath);
	AddAPI<RPCID::GetSubPackages>(ret, &GetSubPackages);

	AddAPI<RPCID::InstallPackage>(ret, &InstallPackage);
	AddAPI<RPCID::InstallFeature>(ret, &InstallFeature);

	AddAPI<RPCID::UpdatePackage>(ret, &UpdatePackage);
	AddAPI<RPCID::UpdateFeature>(ret, &UpdateFeature);
	
	AddAPI<RPCID::DeletePackage>(ret, &DeletePackage);
	AddAPI<RPCID::DeleteFeature>(ret, &DeleteFeature);

	AddAPI<RPCID::RunScript>(ret, &RunScript);
	AddAPI<RPCID::BackupRegistry>(ret, &BackupRegistry);
	return ret;
}

}
}
