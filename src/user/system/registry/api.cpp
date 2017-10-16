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

vector<FeatureInfo> GetFeatures(int64_t pkgid){
	auto pkg = sqlentity::GetByKey<Package>(db, pkgid);
	auto feats = pkg.Features(db);
	vector<FeatureInfo> ret;
	for(auto &f : feats){
		ret.push_back(ToInfo(f));
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

template<uint32_t id, typename F> void AddAPI(vector<shared_ptr<IMessageHandler>> &vec, F fn){
	shared_ptr<IMessageHandler> ptr { rpc::NewProcServer<id>(rpc::make_function(fn)) };
	vec.push_back(ptr);
}

vector<shared_ptr<IMessageHandler>> InitAPI(){
	vector<shared_ptr<IMessageHandler>> ret;
	AddAPI<1>(ret, &GetAllPackages);
	AddAPI<2>(ret, &GetPackageById);
	AddAPI<3>(ret, &GetPackageByName);
	AddAPI<4>(ret, &GetFeatures);
	AddAPI<100>(ret, &InstallPackage);
	AddAPI<101>(ret, &InstallFeature);
	return ret;
}
