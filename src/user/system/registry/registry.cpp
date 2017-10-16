#include <iostream>
#include <btos.h>
#include <btos/envvars.hpp>
#include <util/sqlentity.hpp>
#include <util/rpc.hpp>

#include "tables.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;

using namespace sqlentity;

static const string dbPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/REGISTRY.DB");

sqlitepp::db db(dbPath, false);

static void InitDB(){
	if(db.is_open()) return;
	db.open();
	if(!db.is_open()){
		cout << "Could not open " << dbPath << endl;
	}
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS package(id INTEGER PRIMARY KEY, path TEXT, name TEXT, descr TEXT, ver TEXT)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS feature(id INTEGER PRIMARY KEY, pkgid INTEGER REFERENCES package(id), type TEXT, name TEXT, ver TEXT, descr TEXT, path TEXT, file TEXT, flags INTEGER)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS feature_req(id INTEGER PRIMARY KEY, featid INTEGER REFERENCES feature(id), reqid INTEGER REFERENCES feature(id))").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS ext(id INTEGER PRIMARY KEY, pkgid INTEGER REFERENCES package(id), ext TEXT, mimeType TEXT)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS assoc(id INTEGER PRIMARY KEY, pkgid INTEGER REFERENCES package(id), featid INTEGER REFERENCES feature(id), extid INTEGER REFERENCES ext(id), descr TEXT, template TEXT)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS default_assoc(id INTEGER PRIMARY KEY, extid INTEGER REFERENCES ext(id), associd INTEGER REFERENCES assoc(id))").exec();
}

static size_t suffixMatch(const string &a, const string &b){
	size_t ret = 0;
	if(a.length() && b.length()){
		for(ptrdiff_t ai = a.length() - 1, bi = b.length() - 1; ai >= 0 && bi >= 0; --ai, --bi){
			if(a[ai] == b[bi]) ++ret;
			else break;
		}
	}
	return ret;
}

string GetAssociation(const string &path){
	InitDB();
	auto exts = GetAll<FileType>(db);
	FileType ext;
	size_t len = 0;
	for(const auto &e : exts){
		auto c = suffixMatch(path, e.extension);
		if(c == e.extension.length() && c > len){
			len = c;
			ext = e;
		}
	}
	
	if(ext.id > 0){
		Association assoc;
		auto defaults = ext.Defaults(db);
		if(!defaults.empty()) assoc = defaults.front().association.Get(db);
		else{
			auto assocs = ext.Associations(db);
			if(!assocs.empty()) assoc = assocs.front();
		}
		
		if(assoc.id > 0){
			auto feature = assoc.feature.Get(db);
			auto package = feature.package.Get(db);
			return package.path + feature.path + feature.file;
		}
	}
	return "";
}

void RegTest(){
	InitDB();
	auto pkg = GetWhere<Package>(db, "name = 'test'");
	if(pkg.id == -1){
		pkg.name = "test";
		pkg.description = "Test Package";
		pkg.path = "HDD:/TEST";
		pkg.Save(db);
	}
	auto feat = GetWhere<Feature>(db, "name = 'test'");
	if(feat.id == -1){
		feat.name = "test";
		feat.package = pkg;
		feat.description = "Test Feature";
		feat.path = "/";
		feat.type = "cmd";
		feat.file = "test.elx";
		feat.Save(db);
	}
	auto ext = GetWhere<FileType>(db, "mimeType = 'test/test'");
	if(ext.id == -1){
		ext.extension = ".test";
		ext.mimeType = "test/test";
		ext.package = pkg;
		ext.Save(db);
	}
	auto assoc = GetWhere<Association>(db, "featid = @featid", {{"featid", to_string(feat.id)}});
	if(assoc.id == -1){
		assoc.feature = feat;
		assoc.package = pkg;
		assoc.fileType = ext;
		assoc.description = "Test Association";
		assoc.cmdTemplate = "$";
		assoc.Save(db);
	}
	cout << ".test : " << GetAssociation("file.test") << endl;
	delete rpc::NewProcServer<0>(rpc::make_function(&GetAssociation));
	rpc::ProcClient<0, std::string, std::string> client(0);
}

int main(){
	RegTest();
	return 0;
}
