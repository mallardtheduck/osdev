#include <sqlitepp.hpp>
#include <btos.h>
#include <btos/envvars.hpp>

using std::string;

static const string dbPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSION/ASSOC.DB");

sqlitepp::db db(dbPath, false);

static void InitDB(){
	if(db.is_open()) return;
	db.open();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS apps(id INTEGER PRIMARY KEY, path TEXT, desc TEXT)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS exts(id INTEGER PRIMARY KEY, ext TEXT, mimeType TEXT)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS assocs(id INTEGER PRIMARY KEY, desc TEXT, extid INTEGER REFERENCES exts(id), appid INTEGER REFERENCES apps(id))").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS defaults(id INTEGER PRIMARY KEY, extid INTEGER REFERENCES exts(id), associd INTEGER REFERENCES assocs(id))").exec();
}

string GetAssociation(const string &ext){
	InitDB();
	static sqlitepp::query defaultQ = {
		db, 
		"SELECT ap.path AS path \
		FROM exts e \
		INNER JOIN defaults d ON d.extid = e.id \
		INNER JOIN assocs ac ON d.associd = ac.id \
		INNER JOIN apps ap ON ac.appid = ap.id \
		WHERE exts.ext = @ext \
		LIMIT 1"	
	};
	defaultQ.bind("@ext", ext);
	auto res1 = defaultQ.store();
	if(res1.num_rows()){
		return res1[0]["path"];
	}
	
	static sqlitepp::query firstQ = {
		db, 
		"SELECT ap.path AS path \
		FROM exts e \
		INNER JOIN assocs ac ON e.id = ac.extid \
		INNER JOIN apps ap ON ac.appid = ap.id \
		WHERE exts.ext = @ext \
		LIMIT 1"
	};
	firstQ.bind("@ext", ext);
	auto res2 = defaultQ.store();
	if(res2.num_rows()){
		return res2[0]["path"];
	}
	
	return "";
}
