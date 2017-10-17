#include "tables.hpp"
#include "api_types.hpp"
#include <util/rpc.hpp>
#include <btos/imessagehandler.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <memory>

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

FeatureInfo GetFeatureById(int64_t id){
	auto feat = sqlentity::GetByKey<Feature>(db, id);
	return ToInfo(feat);
}

FeatureInfo GetFeatureByName(const std::string &name){
	auto feat = sqlentity::GetWhere<Feature>(db, "name = @name", {{"name", name}});
	return ToInfo(feat);
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

	AddAPI<RPCID::InstallPackage>(ret, &InstallPackage);
	AddAPI<RPCID::InstallFeature>(ret, &InstallFeature);
	return ret;
}

}
}
