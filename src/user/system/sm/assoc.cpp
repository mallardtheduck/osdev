#include <sqlitepp.hpp>
#include <btos.h>
#include <btos/envvars.hpp>

using std::string;

static const string dbPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSION/ASSOC.DB");

sqlitepp::db db(dbPath, false);

static void InitDB(){
	if(db.is_open()) return;
	auto st = bt_stat(dbPath.c_str());
	db.open();
	if(st.type == FS_Invalid){
		sqlitepp::query(db, "CREATE TABLE apps(id INTEGER PRIMARY KEY, path VARCHAR(1024), desc VARCHAR(255))").exec();
		sqlitepp::query(db, "CREATE TABLE exts(id INTEGER PRIMARY KEY, ext VARCHAR(128), mimeType VARCHAR(128)").exec();
		sqlitepp::query(db, "CREATE TABLE assocs(id INTEGER PRIMARY KEY, desc VARCHAR(255), extid INTEGER REFERENCES exts(id), appid INTEGER REFERENCES apps(id))").exec();
		sqlitepp::query(db, "CREATE TABLE defaults(id INTEGER PRIMARY KEY, extid INTEGER REFRENCES ext(id), associd INTEGER REFERENCES assocs(id))").exec();
	}
}

string GetAssociation(const string &ext){
	InitDB();
	static sqlitepp::query defaultQ = {db, "SELECT apps.path AS path FROM exts JOIN defaults USING (defaults.extid) JOIN asscos USING (exts.associd) JOIN apps USING (assocs.appid) WHERE exts.ext = @ext"};
	defaultQ.bind("@ext", ext);
	auto res1 = defaultQ.store();
	if(res1.num_rows()){
		return res1[0]["path"];
	}
	
	static sqlitepp::query firstQ = {db, "SELECT apps.path AS path FROM exts JOIN assocs USING (assocs.extid) JOIN apps USING (assocs.appid) WHERE exts.ext = @ext"};
	firstQ.bind("@ext", ext);
	auto res2 = defaultQ.store();
	if(res2.num_rows()){
		return res2[0]["path"];
	}
	
	return "";
}
