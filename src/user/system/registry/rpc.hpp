#ifndef _RPC_HPP
#define _RPC_HPP

#include <btos/imessagehandler.hpp>
#include <sstream>
#include <type_traits>
#include <iostream>
#include <vector>
#include <functional>
#include <tuple>

namespace rpc{
    template<typename T> void serialize(std::ostream &os, const T &val){
        static_assert(std::is_fundamental<T>::value, "Non-fundamental types need custom serialization!");
        os.write((const char*)&val, sizeof(val));
    }
    template<> void serialize(std::ostream &os, const std::string &str){
        serialize(os, str.size());
        for(auto c : str){
            serialize(os, c);
        }
    }

    void serialize(std::ostream &){}

    template<typename T, typename ...Ts> void serialize(std::ostream &os, T v, Ts... vs){
        serialize(os, v);
        serialize(os, vs...);
    }

    template<typename T> void deserialize(std::istream &is, T &val){
        static_assert(std::is_fundamental<T>::value, "Non-fundamental types need custom deserialization!");
        is.read((char*)&val, sizeof(val));
    }
    template<> void deserialize(std::istream &is, std::string &val){
        size_t size;
        deserialize(is, size);
        val = "";
        for(size_t i = 0; i < size; ++i){
            char c;
            deserialize(is, c);
            val += c;
        }
    }

    template<uint32_t msgtype, typename R, typename ...Ps> class ProcClient{
    private:
        bt_pid_t pid;
    public:
        ProcClient(bt_pid_t p) : pid(p) {}

        R operator()(Ps... ps){
            std::stringstream pss;
            serialize(pss, ps...);
            auto data = pss.str();
            bt_msg_header msg;
            msg.flags = 0;
            msg.type = msgtype;
            msg.to = pid;
            msg.length = data.size();
            msg.content = data.c_str();
            msg.id = bt_send(msg);

            bt_msg_header reply;
            bt_msg_filter filter;
            filter.flags = bt_msg_filter_flags::Reply;
            filter.reply_to = msg.id;
            reply = bt_recv_filtered(filter);
            while(reply.reply_id != msg.id){
                std::stringstream ss;
                ss << "RPC: Spurious message!" << std::endl;
                ss << "Message id: " << reply.id << std::endl;
                ss << "From : " << reply.from << std::endl;
                ss << "Flags : " << reply.flags << std::endl;
                ss << "Reply ID: " << reply.reply_id << " (Waiting for: " << msg.id << ")" << std::endl;
                bt_zero(ss.str().c_str());
                bt_next_msg_filtered(&reply, filter);
            }
            
            std::vector<char> replyData{ reply.length };
            bt_msg_content(&reply, &replyData[0], reply.length);
            std::stringstream rss;
            rss.write(&replyData[0], replyData.size());
            rss.seekg(0);
            R ret;
            deserialize(rss, ret);
            return ret;
        }
    };

    template<typename T, typename ...Ts> std::tuple<T, Ts...> deserializeAll(std::istream &is){
        typename std::remove_reference<T>::type v;
        deserialize(is, v);
        return std::tuple_cat(std::make_tuple(v), deserializeAll<Ts...>(is));
    }

    std::tuple<> deserializeAll(std::istream &){
        return std::make_tuple();
    }

    namespace TupleCall_detail{
        template <typename F, typename Tuple, bool Done, int Total, int... N> struct call_impl{
            template<typename E = void> static auto call(F f, Tuple && t ){
                return call_impl<F, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(f, std::forward<Tuple>(t));
            }
        };
    
        template <typename F, typename Tuple, int Total, int... N> struct call_impl<F, Tuple, true, Total, N...>{
            template<typename E = void> static auto call(F f, Tuple && t){
                return f(std::get<N>(std::forward<Tuple>(t))...);
            }
        };
    }
    
    template <typename F, typename Tuple> auto TupleCall(F f, Tuple && t){
        typedef typename std::decay<Tuple>::type ttype;
        return TupleCall_detail::call_impl<F, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(f, std::forward<Tuple>(t));
    }

    template<uint32_t msgtype, typename R, typename ...Ps> class ProcServer : public btos_api::IMessageHandler{
    private:
        std::function<R(Ps...)> fn;
    public:
        ProcServer(std::function<R(Ps...)> f) : fn(f) {}

        bool HandleMessage(const btos_api::Message &msg){
            if(msg.Type() == msgtype){
                std::stringstream pss;
                pss.write((const char*)msg.Content(), msg.Length());
                auto ps = deserializeAll<Ps...>(pss);
                R r = TupleCall(fn, ps);
                std::stringstream rss;
                serialize(rss, r);
                auto rdata = rss.str();
                msg.SendReply((void*)rdata.c_str(), rdata.size());
                return false;
            }
            return true;
        }
    };

    template<uint32_t msgtype, typename R, typename ...Ps> auto MakeProcServer(std::function<R(Ps...)> fn){
        return ProcServer<msgtype, R, Ps...>(fn);
    }

    template<typename R, typename ...Ps> std::function<R(Ps...)> make_function(R(*fn)(Ps...)){
        return std::function<R(Ps...)>(fn);
    }
}

#endif