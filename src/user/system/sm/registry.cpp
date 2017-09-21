#include <sqlitepp.hpp>
#include <btos.h>
#include <btos/envvars.hpp>

using std::string;

static const string dbPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/REGISTRY.DB");

sqlitepp::db db(dbPath, false);

static void InitDB(){
	if(db.is_open()) return;
	db.open();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS package(id INTEGER PRIMARY KEY, path TEXT, name TEXT, descr TEXT, ver TEXT").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS feature(id INTEGER PRIMARY KEY, pkgid INTEGER REFERENCES package(id), type TEXT, name TEXT, ver TEXT, descr TEXT, path TEXT, file TEXT, flags INTEGER)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS feature_reqs(featid INTEGER REFERENCES feature(id), reqid INTEGER REFERENCES feature(id))").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS ext(id INTEGER PRIMARY KEY, pkgid INTEGER REFERENCES package(id), ext TEXT, mimeType TEXT)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS assoc(id INTEGER PRIMARY KEY, pkgid INTEGER REFERENCES package(id), featid INTEGER REFERENCES feature(id), descr TEXT, template TEXT)").exec();
	sqlitepp::query(db, "CREATE TABLE IF NOT EXISTS default_assoc(extid INTEGER REFERENCES ext(id), associd INTEGER REFERENCES assoc(id))").exec();
}

static size_t suffixMatch(const string &a, const string &b){
	size_t ret = 0;
	if(a.length() && b.length()){
		for(size_t ai = a.length() - 1, bi = b.length() - 1; ai > 0 && bi > 0; --ai, --bi){
			if(a[ai] == b[bi]) ++ret;
			else break;
		}
	}
	return ret;
}

string GetAssociation(const string &path){
	InitDB();
	static sqlitepp::query extQ(db, "SELECT id, ext FROM ext");
	auto exts = extQ.store();
	string extid;
	size_t len = 0;
	for(const auto &e : exts){
		string ext = e["ext"];
		auto c = suffixMatch(path, ext);
		if(c > len){
			len = c;
			extid = string(e["id"]);
		}
	}
	
	if(!extid.empty()){
		static sqlitepp::query defaultQ(db, "SELECT associd FROM default_assoc WHERE extid = @ext LIMIT 1");
		defaultQ.bind("@ext", extid);
		string associd;
		auto defaultRes = defaultQ.store();
		if(!defaultRes.empty()) associd = string(defaultRes[0]["associd"]);
		else{
			static sqlitepp::query firstQ(db, "SELECT id FROM assoc WHERE extid = @ext LIMIT 1");
			defaultQ.bind("@ext", extid);
			auto firstRes = firstQ.store();
			if(!firstRes.empty()) associd = string(firstRes[0]["id"]);
		}
		
		if(!associd.empty()){
			static sqlitepp::query featureQ(db, 
				"SELECT f.type AS ftype, f.path AS fpath, f.file AS ffile, p.path AS ppath \
				FROM assoc a \
				INNER JOIN feature f ON a.featid = f.id \
				INNER JOIN package p ON a.pkgid = p.id \
				WHERE \
				a.associd = @assoc \
				LIMIT 1");
			featureQ.bind("@assoc", associd);
			auto featureRes = featureQ.store();
			if(!featureRes.empty()){
				auto &frow = featureRes[0];
				string ftype = frow["ftype"];
				if(ftype == "app" || ftype == "cmd"){
					string fpath = frow["fpath"];
					string ffile = frow["ffile"];
					string ppath = frow["ppath"];
					return ppath + fpath + ffile;
				}
			}
		}
	}
	return "";
}
