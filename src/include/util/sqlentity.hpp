#ifndef _SQLENTITY_HPP
#define _SQLENTITY_HPP

#include <sqlitepp.hpp>

#include <map>
#include <memory>
#include <cstring>
#include <sstream>
#include <type_traits>
#include <iostream>

namespace sqlentity{

template<typename T> std::string to_string(const T &n){
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

template<> inline std::string to_string<>(const std::string &s){
	return s;
}

template<typename T> T GetByKey(sqlitepp::db &db, int64_t key);
template<typename T> std::vector<T> GetAllWhere(sqlitepp::db &db, const std::string &where,
    std::map<std::string, std::string> vars = std::map<std::string, std::string>()
);

template<typename T> class Reference{
public:
    int64_t key = -1;

    Reference<T> &operator=(const T &other){
        key = other.binder.GetKeyValue();
        return *this;
    }

    T Get(sqlitepp::db &db) const{
        return GetByKey<T>(db, key);
    }
};

template<typename T> class Child{
public:
	std::string field;

	explicit Child(const std::string &f) : field(f) {}
};

class IVarBind{
public:
	virtual void DBBind(sqlitepp::query &q, const std::string &name) = 0;
    virtual void DBRead(sqlitepp::field_type &f) = 0;
    virtual void AssignKey(int64_t id) = 0;
    virtual int64_t KeyValue() = 0;
	virtual void *GetPtr() = 0;
	virtual ~IVarBind() {} 
};

template<typename T> class VarBind : public IVarBind{
private:
	T *var;
    std::unique_ptr<char> atname;
    std::string value;

	friend class TableBind;
public:
	VarBind(T& v) : var(&v) {};

	void DBBind(sqlitepp::query &q, const std::string &name){
        atname.reset(strdup(("@" + name).c_str()));
        value = to_string(*var);
        q.bind(atname.get(), value);
	}

	void DBRead(sqlitepp::field_type &f){
		if(!f.is_null()) *var = static_cast<T>(f);
		else *var = T();
    }

	void *GetPtr(){
		return var;
	}
    
    void AssignKey(int64_t id);
    int64_t KeyValue();
};

template<typename T> void VarBind<T>::AssignKey(int64_t) {
    //Key must be int64_t
}
template<> inline void VarBind<int64_t>::AssignKey(int64_t id){
    *var = id;
}

template<typename T> int64_t VarBind<T>::KeyValue() {
    //Key must be int64_t
    return -1;
}
template<> inline int64_t VarBind<int64_t>::KeyValue(){
    return *var;
}

class IChildBind{
public:
	virtual ~IChildBind() {}
};

template<typename T> class ChildBind : public IChildBind{
private:
	std::string field;
public:
	ChildBind(const std::string &f) : field(f) {}
	
	std::vector<T> Get(sqlitepp::db &db, int64_t key){
		std::stringstream ss;
		ss << field << " = @" << field;
		auto where = ss.str();
		return GetAllWhere<T>(db, where, {{field, to_string(key)}});
	}
};

class TableBind{
private:
	std::string table;
	std::string key;
	std::map<std::string, std::shared_ptr<IVarBind>> fields;
	std::map<std::string, std::shared_ptr<IChildBind>> children;

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
    
    template<typename T> void BindVar(const std::string name, Reference<T> &var){
        BindVar(name, var.key);
    }

	template<typename T> void BindChild(const Child<T> &child){
		std::shared_ptr<IChildBind> p = std::make_shared<ChildBind<T>>(child.field);
		children.insert(std::make_pair(to_string(&child), p));
	}

	std::vector<std::string> GetFieldList(){
		std::vector<std::string> ret;
		for(auto &f : fields) ret.push_back(f.first);
		return ret;
	}

	void DBBind(sqlitepp::query &q, bool includeKey = false){
		for(auto &f : fields){
			if(includeKey || f.first != key) f.second->DBBind(q, f.first);
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

	std::shared_ptr<IChildBind> GetChildBind(std::string name){
		if(children.find(name) == children.end()) return {};
		return children[name];
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
	mutable TableBind binder;

    BoundEntity() = default;
    BoundEntity(const BoundEntity &){
        binder.Clear();
        bound = false;
    }
    BoundEntity(const BoundEntity &&){
        binder.Clear();
        bound = false;
    }

    BoundEntity &operator=(const BoundEntity &other){
        if(this != &other){
            binder.Clear();
            bound = false;
        }
        return *this;
    }

    BoundEntity &operator=(const BoundEntity &&other){
        if(this != &other){
            binder.Clear();
            bound = false;
        }
        return *this;
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

    virtual std::string DeleteSQL(){
        Bound();
        std::stringstream ss;
        ss << "DELETE FROM " << binder.GetTable();
        ss << " WHERE " << binder.GetKey() << " = @" << binder.GetKey();
        return ss.str();
    }

    virtual void Delete(sqlitepp::db &db){
        Bound();
        sqlitepp::query deleteQ(db, DeleteSQL());
        auto keyField = binder.GetKey();
        std::unique_ptr<char> atKey(strdup(("@" + keyField).c_str()));
        auto idstr = to_string(binder.GetKeyValue());
        deleteQ.bind(atKey.get(), idstr);
        deleteQ.exec();
        binder.AssignKey(-1);
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
        auto idstr = to_string(id);
        selectQ.bind(atKey.get(), idstr);

        auto row = selectQ.use();
        if(!row.empty()){
            binder.DBRead(row);
            selectQ.use_abort();
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
        if(!row.empty()){
            binder.DBRead(row);
            selectQ.use_abort();
        }
        atvars.clear();
    }

	template<typename T> std::vector<T> GetChildren(sqlitepp::db &db, const Child<T> &child){
		Bound();
		auto iChildBind = binder.GetChildBind(to_string(&child));
		if(!iChildBind) return {};
		auto childBind = dynamic_cast<ChildBind<T>*>(iChildBind.get());
		if(!childBind) return {};
		
		return childBind->Get(db, binder.GetKeyValue());
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
    std::map<std::string, std::string> vars
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
        ret.push_back(t);
        row = selectQ.use_next();
    }
    return ret;
}

template<typename T> std::vector<T> GetAll(sqlitepp::db &db){
    return GetAllWhere<T>(db, "1 = 1");
}

}
#endif
