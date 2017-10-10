#include <iostream>
#include "sqlentity.hpp"
#include <btos.h>
#include <btos/envvars.hpp>

using std::string;
using std::cout;
using std::endl;

using namespace sqlentity;

static const string dbPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/REGISTRY.DB");

sqlitepp::db db(dbPath, false);

struct Package : public BoundEntity{
	int64_t id = -1;
	string name;
	string path;
	string description;
	string ver;

	void Bind(){
		binder.SetTable("package");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("name", name);
		binder.BindVar("path", path);
		binder.BindVar("descr", description);
		binder.BindVar("ver", ver);
	}
};

struct Feature : public BoundEntity{
	int64_t id = -1;
	Reference<Package> package;
	string type;
	string name;
	string ver;
	string description;
	string path;
	string file;
	int64_t flags;

	void Bind(){
		binder.SetTable("feature");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("pkgid", package);
		binder.BindVar("type", type);
		binder.BindVar("name", name);
		binder.BindVar("ver", ver);
		binder.BindVar("descr", description);
		binder.BindVar("path", path);
		binder.BindVar("file", file);
		binder.BindVar("flags", flags);
	}
};

struct FeatureRequirement : public BoundEntity{
	int64_t id = -1;
	Reference<Feature> feature;
	Reference<Feature> requires;

	void Bind(){
		binder.SetTable("feature_req");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("featid", feature);
		binder.BindVar("reqid", requires);
	}
};

struct FileType : public BoundEntity{
	int64_t id = -1;
	Reference<Package> package;
	string extension;
	string mimeType;

	void Bind(){
		binder.SetTable("ext");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("pkgid", package);
		binder.BindVar("ext", extension);
		binder.BindVar("mimeType", mimeType);
	}
};

struct Association : public BoundEntity{
	int64_t id = -1;
	Reference<Package> package;
	Reference<Feature> feature;
	Reference<FileType> fileType;
	string description;
	string cmdTemplate;

	void Bind(){
		binder.SetTable("assoc");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("pkgid", package);
		binder.BindVar("featid", feature);
		binder.BindVar("extid", fileType);
		binder.BindVar("descr", description);
		binder.BindVar("template", cmdTemplate);
	}
};

struct DefaultAssociation : public BoundEntity{
	int64_t id = -1;
	Reference<FileType> fileType;
	Reference<Association> association;

	void Bind(){
		binder.SetTable("default_assoc");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("extid", fileType);
		binder.BindVar("associd", association);
	}
};

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
	int64_t extid = -1;
	size_t len = 0;
	for(const auto &e : exts){
		auto c = suffixMatch(path, e.extension);
		if(c == e.extension.length() && c > len){
			len = c;
			extid = e.id;
		}
	}
	
	if(extid > 0){
		Association assoc;
		auto defaultAssoc = GetWhere<DefaultAssociation>(db, "extid = @ext", {{"ext", to_string(extid)}});
		if(defaultAssoc.id > 0) assoc = defaultAssoc.association.Get(db);
		else{
			assoc = GetWhere<Association>(db, "extid = @ext", {{"ext", to_string(extid)}});
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
}

int main(){
	RegTest();
	return 0;
}
