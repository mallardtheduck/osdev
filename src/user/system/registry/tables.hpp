#ifndef _TABLES_HPP
#define _TABLES_HPP

#include <util/sqlentity.hpp>

extern sqlitepp::db db;

struct Feature;
struct FeatureRequirement;
struct FileType;
struct Association;
struct DefaultAssociation;

class Package : public sqlentity::BoundEntity{
private:
	sqlentity::Child<Feature> features{"pkgid"};
	sqlentity::Child<FileType> fileTypes{"pkgid"};
	sqlentity::Child<Association> associations{"pkgid"};
public:
	int64_t id = -1;
	std::string name;
	std::string path;
	std::string description;
	std::string ver;

	void Bind(){
		binder.SetTable("package");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("name", name);
		binder.BindVar("path", path);
		binder.BindVar("descr", description);
		binder.BindVar("ver", ver);
		binder.BindChild(features);
		binder.BindChild(fileTypes);
		binder.BindChild(associations);
	}

	auto Features(sqlitepp::db &db) { return GetChildren(db, features); }
	auto FileTypes(sqlitepp::db &db) { return GetChildren(db, fileTypes); }
	auto Associations(sqlitepp::db &db) { return GetChildren(db, associations); }
};

class Feature : public sqlentity::BoundEntity{
private:
	sqlentity::Child<FeatureRequirement> requirements{"featid"};
	sqlentity::Child<FeatureRequirement> requiredBy{"reqid"};
public:
	int64_t id = -1;
	sqlentity::Reference<Package> package;
	std::string type;
	std::string name;
	std::string ver;
	std::string description;
	std::string path;
	std::string file;
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
		binder.BindChild(requirements);
		binder.BindChild(requiredBy);
	}

	auto Requirements(sqlitepp::db &db) { return GetChildren(db, requirements); }
	auto RequiredBy(sqlitepp::db &db) { return GetChildren(db, requiredBy); }
};

struct FeatureRequirement : public sqlentity::BoundEntity{
	int64_t id = -1;
	sqlentity::Reference<Feature> feature;
	sqlentity::Reference<Feature> requires;

	void Bind(){
		binder.SetTable("feature_req");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("featid", feature);
		binder.BindVar("reqid", requires);
	}
};

class FileType : public sqlentity::BoundEntity{
private:
	sqlentity::Child<Association> associations{"extid"};
	sqlentity::Child<DefaultAssociation> defaults{"extid"};
public:
	int64_t id = -1;
	sqlentity::Reference<Package> package;
	std::string extension;
	std::string mimeType;

	void Bind(){
		binder.SetTable("ext");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("pkgid", package);
		binder.BindVar("ext", extension);
		binder.BindVar("mimeType", mimeType);
		binder.BindChild(associations);
		binder.BindChild(defaults);
	}

	auto Associations(sqlitepp::db &db) { return GetChildren(db, associations); }
	auto Defaults(sqlitepp::db &db) { return GetChildren(db, defaults); }
};

struct Association : public sqlentity::BoundEntity{
	int64_t id = -1;
	sqlentity::Reference<Package> package;
	sqlentity::Reference<Feature> feature;
	sqlentity::Reference<FileType> fileType;
	std::string description;
	std::string cmdTemplate;

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

struct DefaultAssociation : public sqlentity::BoundEntity{
	int64_t id = -1;
	sqlentity::Reference<FileType> fileType;
	sqlentity::Reference<Association> association;

	void Bind(){
		binder.SetTable("default_assoc");
		binder.SetKey("id");
		binder.BindVar("id", id);
		binder.BindVar("extid", fileType);
		binder.BindVar("associd", association);
	}
};

#endif
