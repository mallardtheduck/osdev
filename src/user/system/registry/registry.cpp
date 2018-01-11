#include <iostream>
#include <btos.h>
#include <btos/envvars.hpp>
#include <btos/messageloop.hpp>
#include <util/sqlentity.hpp>
#include <util/rpc.hpp>

#include "tables.hpp"
#include "registry.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;

using namespace sqlentity;

MessageLoop msgloop;

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
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS feature_req(id INTEGER PRIMARY KEY, featid INTEGER REFERENCES feature(id), reqid INTEGER REFERENCES feature(id), minVersion TEXT)").exec();
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

Feature GetAssociation(const string &path){
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
			return feature;
		}
	}
	return {};
}

int main(){
	InitDB();
	auto api = btos_api::registry::InitAPI();
	for(auto &a : api){
		msgloop.AddHandler(a);
	}
	msgloop.RunLoop();
	return 0;
}
