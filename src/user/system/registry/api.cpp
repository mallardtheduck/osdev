#include "tables.hpp"
#include <util/rpc.hpp>
#include <btos/imessagehandler.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <memory>

using std::vector;
using std::string;
using std::shared_ptr;

struct PackageInfo{
	int64_t id;
	string name;
	string description;
	string path;
	string ver;
};

PackageInfo ToInfo(const Package &pkg){
	PackageInfo ret;
	ret.id = pkg.id;
	ret.name = pkg.name;
	ret.description = pkg.description;
	ret.ver = pkg.ver;
	return ret;
}

void serialize(std::ostream &os, const PackageInfo &pi){
	rpc::serialize(os, pi.id);
	rpc::serialize(os, pi.name);
	rpc::serialize(os, pi.description);
	rpc::serialize(os, pi.path);
	rpc::serialize(os, pi.ver);
}

void deserialize(std::istream &is, PackageInfo &pi){
	rpc::deserialize(is, pi.id);
	rpc::deserialize(is, pi.name);
	rpc::deserialize(is, pi.description);
	rpc::deserialize(is, pi.path);
	rpc::deserialize(is, pi.ver);
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

int64_t InstallPackage(const PackageInfo &info){
	Package pkg;
	pkg.id = info.id;
	pkg.name = info.name;
	pkg.description = info.description;
	pkg.ver = info.ver;
	pkg.Save(db);
	return pkg.id;
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
	return ret;
}
