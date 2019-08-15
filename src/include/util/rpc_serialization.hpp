#ifndef _RPC_SERIALIZATION_HPP
#define _RPC_SERIALIZATION_HPP

#include <tuple>
#include <iostream>

namespace rpc{
	template<typename T> void serialize(std::ostream &os, const T &val){
        static_assert(std::is_fundamental<T>::value, "Non-fundamental types need custom serialization!");
        os.write((const char*)&val, sizeof(val));
    }

    inline void serialize(std::ostream &os, const std::string &str){
        serialize(os, str.size());
        for(auto c : str){
            serialize(os, c);
        }
    }

	template<typename T> void serialize(std::ostream &os, const std::vector<T> &vec){
		serialize(os, vec.size());
		for(auto &v : vec){
			serialize(os, v);
		}
	}

    inline void serialize(std::ostream &){}

    template<typename T, typename ...Ts> void serialize(std::ostream &os, T v, Ts... vs){
        serialize(os, v);
        serialize(os, vs...);
    }

    template<typename T> void deserialize(std::istream &is, T &val){
        static_assert(std::is_fundamental<T>::value, "Non-fundamental types need custom deserialization!");
        is.read((char*)&val, sizeof(val));
    }

    inline void deserialize(std::istream &is, std::string &val){
        size_t size;
        deserialize(is, size);
        val = "";
        for(size_t i = 0; i < size; ++i){
            char c;
            deserialize(is, c);
            val += c;
        }
    }

	template<typename T> void deserialize(std::istream &is, std::vector<T> &vec){
		size_t size;
        deserialize(is, size);
		vec.clear();
		for(size_t i = 0; i < size; ++i){
            T v;
            deserialize(is, v);
            vec.push_back(v);
        }
	}
	
	template<typename T> auto deserializeAll(std::istream &is){
		typename std::remove_cv<typename std::remove_reference<T>::type>::type v;
        deserialize(is, v);
        return std::make_tuple(v);
    }

    template<typename T, typename Ta, typename ...Ts> auto deserializeAll(std::istream &is){
        typename std::remove_cv<typename std::remove_reference<T>::type>::type v;
        deserialize(is, v);
        return std::tuple_cat(std::make_tuple(v), deserializeAll<Ta, Ts...>(is));
    }

	inline auto deserializeAll(std::istream &){
		return std::make_tuple();
	}	
}

#endif
