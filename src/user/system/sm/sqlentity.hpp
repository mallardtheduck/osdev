#ifndef _SQLENTITY_HPP
#define _SQLENTITY_HPP

#include <sqlitepp.hpp>

#include <map>
#include <memory>
#include <cstring>
#include <sstream>
#include <type_traits>

template<typename T> std::string to_string(const T &n){
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

template<> std::string to_string<>(const std::string &s){
	return s;
}

class IVarBind{
public:
	virtual void DBBind(sqlitepp::query &q, const std::string &name) = 0;
    virtual void DBRead(sqlitepp::field_type &f) = 0;
    virtual void AssignKey(int64_t id) = 0;
    virtual int64_t KeyValue() = 0;
	virtual ~IVarBind() {} 
};

template<typename T> class VarBind : public IVarBind{
private:
	T *var;
	std::unique_ptr<char> atname;
public:
	VarBind(T& v) : var(&v) {};

	void DBBind(sqlitepp::query &q, const std::string &name){
		atname.reset(strdup(("@" + name).c_str()));
		q.bind(atname.get(), to_string(*var));
	}

	void DBRead(sqlitepp::field_type &f){
		*var = static_cast<T>(f);
    }
    
    void AssignKey(int64_t id);
    int64_t KeyValue();
};

template<typename T> void VarBind<T>::AssignKey(int64_t) {
    //Key must be int64_t
}
template<> void VarBind<int64_t>::AssignKey(int64_t id){
    *var = id;
}

template<typename T> int64_t VarBind<T>::KeyValue() {
    //Key must be int64_t
    return -1;
}
template<> int64_t VarBind<int64_t>::KeyValue(){
    return *var;
}

class TableBind{
private:
	std::string table;
	std::string key;
	std::map<std::string, std::shared_ptr<IVarBind>> fields;

public:
	void SetTable(const std::string &t){
		table = t;
	}
	std::string GetTable(){
		return table;
	}

	void SetKey(const std::string &k){
		key = k;
	}

	bool IsKey(const std::string &f){
		return f == key;
    }
    
    std::string GetKey(){
        return key;
    }

	template<typename T> void BindVar(const std::string &name, T &var){
		std::shared_ptr<IVarBind> p = std::make_shared<VarBind<T>>(var);
		fields.insert(std::make_pair(name, p));
	}

	std::vector<std::string> GetFieldList(){
		std::vector<std::string> ret;
		for(auto &f : fields) ret.push_back(f.first);
		return ret;
	}

	void DBBind(sqlitepp::query &q, bool includeKey = false){
		for(auto &f : fields){
			if(!includeKey || f.first != key) f.second->DBBind(q, f.first);
		}
    }

    void DBRead(sqlitepp::row &r){
        for(auto &f : r){
            if(fields.find(f.name()) != fields.end()) fields[f.name()]->DBRead(f);
        }
    }
    
    void AssignKey(int64_t id){
        if(!key.empty() && fields.find(key) != fields.end()){
            fields[key]->AssignKey(id);
        }
    }

    int64_t GetKeyValue(){
        if(!key.empty() && fields.find(key) != fields.end()){
            return fields[key]->KeyValue();
        }
        return -1;
    }

    void DBBindKey(sqlitepp::query &q){
        if(!key.empty() && fields.find(key) != fields.end()){
            fields[key]->DBBind(q, key);
        }
    }

    void Clear(){
        table.clear();
        key.clear();
        fields.clear();
    }
};

class BoundEntity{
private:
	bool bound = false;

	void Bound(){
		if(!bound) Bind();
		bound = true;
    }
    
    void MakeSelect(std::stringstream &ss){
        ss << "SELECT ";
        auto fields = binder.GetFieldList();
		bool firstField = true;
		for(auto &f : fields){
			if(!firstField)	ss << ", ";
			else firstField = false;
			ss << f;
        }
        ss << " FROM " << binder.GetTable();
    }
public:
	TableBind binder;

    BoundEntity() = default;
    BoundEntity(const BoundEntity &){
        binder.Clear();
        bound = false;
    }
    BoundEntity(const BoundEntity &&){
        binder.Clear();
        bound = false;
    }

	virtual void Bind() = 0;

    virtual std::string InsertSQL(){
        Bound();
        std::stringstream ss;
		ss << "INSERT INTO " << binder.GetTable() << " (";
		auto fields = binder.GetFieldList();
		bool firstField = true;
		for(auto &f : fields){
			if(binder.IsKey(f)) continue;
			if(!firstField)	ss << ", ";
			else firstField = false;
			ss << f;
		}
		ss << ") VALUES (";
		firstField = true;
		for(auto &f : fields){
			if(binder.IsKey(f)) continue;
			if(!firstField)	ss << ", ";
			else firstField = false;
			ss << "@" << f;
		}
        ss << ")";
        return ss.str();
    }

	virtual void Insert(sqlitepp::db &db){
		Bound();
		sqlitepp::query insertQ(db, InsertSQL());
		binder.DBBind(insertQ);
		insertQ.exec();
		auto id = insertQ.insert_id();
		binder.AssignKey(id);
    }

    virtual std::string UpdateSQL(){
        Bound();
        std::stringstream ss;
        ss << "UPDATE " << binder.GetTable() << " ";
        auto fields = binder.GetFieldList();
        bool firstField = true;
        for(auto &f : fields){
            if(binder.IsKey(f)) continue;
            if(firstField) ss << "SET ";
            else ss << ", ";
            firstField = false;
            ss << f << "= @" << f;
        }
        ss << " WHERE " << binder.GetKey() << " = @" << binder.GetKey();
        return ss.str();
    }

    virtual void Update(sqlitepp::db &db){
        Bound();
        sqlitepp::query updateQ(db, UpdateSQL());
        binder.DBBind(updateQ, true);
        updateQ.exec();
    }

    virtual void Save(sqlitepp::db &db){
        Bound();
        if(binder.GetKeyValue() > 0) Update(db);
        else Insert(db);
    }

    virtual std::string GetByKeySQL(){
        Bound();
        std::stringstream ss;
        MakeSelect(ss);
        auto keyField = binder.GetKey();
        ss << " WHERE " << keyField << " = @" << keyField;
        ss << " LIMIT 1";
        return ss.str();
    }

    virtual void GetByKey(sqlitepp::db &db, uint64_t id){
        Bound();
        sqlitepp::query selectQ(db, GetByKeySQL());
        auto keyField = binder.GetKey();
        std::unique_ptr<char> atKey(strdup(("@" + keyField).c_str()));
        selectQ.bind(atKey.get(), to_string(id));

        auto res = selectQ.store();
        if(res.size() > 0){
            auto &row = res.front();
            binder.DBRead(row);
        }
    }

    virtual void ReadRow(sqlitepp::row &row){
        Bound();
        binder.DBRead(row);
    }

    virtual std::string GetWhereSQL(const std::string &where){
        Bound();
        std::stringstream ss;
        MakeSelect(ss);
        ss << " WHERE " << where << " ";
        return ss.str();
    }

    virtual void GetWhere(sqlitepp::db &db, const std::string &where, 
        std::map<std::string, std::string> vars = std::map<std::string, std::string>()
    ){
        Bound();
        sqlitepp::query selectQ(db, GetWhereSQL(where));

        std::vector<std::shared_ptr<char>> atvars;
        for(auto &v : vars){
            std::shared_ptr<char> atKey(strdup(("@" + v.first).c_str()));
            selectQ.bind(atKey.get(), v.second);
            atvars.push_back(atKey);
        }
        
        auto row = selectQ.use();
        binder.DBRead(row);
        selectQ.use_abort();
    }

};

template<typename T> T GetByKey(sqlitepp::db &db, int64_t key){
    static_assert(std::is_base_of<BoundEntity, T>::value, "Type is not a BoundEntity!");
    static_assert(std::is_default_constructible<T>::value, "Type not default constructible!");
    T ret;
    ret.GetByKey(db, key);
    return ret;
}

template<typename T> T GetWhere(sqlitepp::db &db, const std::string &where,
    std::map<std::string, std::string> vars = std::map<std::string, std::string>()
){
    static_assert(std::is_base_of<BoundEntity, T>::value, "Type is not a BoundEntity!");
    static_assert(std::is_default_constructible<T>::value, "Type not default constructible!");
    T ret;
    ret.GetWhere(db, where, vars);
    return ret;
}

template<typename T> std::vector<T> GetAllWhere(sqlitepp::db &db, const std::string &where,
    std::map<std::string, std::string> vars = std::map<std::string, std::string>()
){
    static_assert(std::is_base_of<BoundEntity, T>::value, "Type is not a BoundEntity!");
    static_assert(std::is_default_constructible<T>::value, "Type not default constructible!");

    T sug;
    sqlitepp::query selectQ(db, sug.GetWhereSQL(where));
    
    std::vector<std::shared_ptr<char>> atvars;
    for(auto &v : vars){
        std::shared_ptr<char> atKey(strdup(("@" + v.first).c_str()));
        selectQ.bind(atKey.get(), v.second);
        atvars.push_back(atKey);
    }
    
    std::vector<T> ret;
    auto row = selectQ.use();
    while(!row.empty()){
        T t;
        t.ReadRow(row);
        row = selectQ.use_next();
    }
    return ret;
}

template<typename T> std::vector<T> GetAll(sqlitepp::db &db){
    return GetAllWhere<T>(db, "1 = 1");
}

#endif