#ifndef _RPC_HPP
#define _RPC_HPP

#include <btos/imessagehandler.hpp>
#include <sstream>
#include <type_traits>
#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include <map>

#include "rpc_serialization.hpp"

namespace rpc{

    const uint32_t MessageType_Continue = 0xFFFFFFFF;

    template<uint32_t msgtype, typename R, typename ...Ps> class ProcClient{
    private:
        bt_pid_t pid;
    public:
        ProcClient(bt_pid_t p) : pid(p) {}

        R operator()(Ps... ps){
            std::stringstream pss;
            serialize(pss, ps...);
            auto data = pss.str();
            int msgno = data.size() / BT_MSG_MAX;
            bt_msg_header msg;
            while(msgno >= 0){
                size_t len = std::min(BT_MSG_MAX, data.size());
                msg.flags = 0;
                msg.type = msgtype;
                msg.to = pid;
                msg.length = len;
                msg.source = msgno--;
                msg.content = (void*)data.c_str();
                msg.id = bt_send(msg);
                if(msgno >= 0) data = data.substr(len);
            }

            bt_msg_header reply;
            bt_msg_filter filter;
            std::stringstream rss;
            bool more_data = true;
            while(more_data){
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
                
                std::vector<char> replyData(reply.length);
                bt_msg_content(&reply, &replyData[0], reply.length);
                rss.write(&replyData[0], replyData.size());
                if(reply.type == MessageType_Continue){
                    msg.flags = bt_msg_flags::Reply;
                    msg.reply_id = reply.id;
                    msg.type = MessageType_Continue;
                    msg.to = pid;
                    msg.length = 0;
                    msg.content = nullptr;
                    msg.id = bt_send(msg);
                    more_data = true;
                }else{
                    more_data = false;
                }
            }
            rss.seekg(0);
            R ret;
            deserialize(rss, ret);
            return ret;
        }
    };

    template<uint32_t msgtype, typename R, typename ...Ps>
    ProcClient<msgtype, R, Ps...> MakeClient(bt_pid_t pid, R(*)(Ps...)){
        return ProcClient<msgtype, R, Ps...>(pid);
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
        std::map<bt_pid_t, std::stringstream> buffers;
        std::map<uint64_t, std::string> return_buffers;
    public:
        ProcServer(std::function<R(Ps...)> f) : fn(f) {}

        bool HandleMessage(const btos_api::Message &msg){
            if(msg.Type() == msgtype){
                std::stringstream &pss = buffers[msg.From()];
                pss.write((const char*)msg.Content(), msg.Length());
                if(msg.Source() == 0){
                    pss.seekg(0);
                    auto ps = deserializeAll<Ps...>(pss);
                    buffers.erase(msg.From());
                    R r = TupleCall(fn, ps);
                    std::stringstream rss;
                    serialize(rss, r);
                    auto rdata = rss.str();
                    if(rdata.size() > BT_MSG_MAX){
                        auto cur = rdata.substr(0, BT_MSG_MAX);
                        auto rest = rdata.substr(BT_MSG_MAX);
                        auto id = msg.SendReply((void*)cur.c_str(), cur.size(), MessageType_Continue);
                        return_buffers[id] = rest;
                    }else{
                        msg.SendReply((void*)rdata.c_str(), rdata.size());
                    }
                }
            }else if(msg.Type() == MessageType_Continue && return_buffers.find(msg.ReplyTo()) != return_buffers.end()){
                auto rdata = return_buffers[msg.ReplyTo()];
                return_buffers.erase(msg.ReplyTo());
                if(rdata.size() > BT_MSG_MAX){
                    auto cur = rdata.substr(0, BT_MSG_MAX);
                    auto rest = rdata.substr(BT_MSG_MAX);
                    auto id = msg.SendReply((void*)cur.c_str(), cur.size(), MessageType_Continue);
                    return_buffers[id] = rest;
                }else{
                    msg.SendReply((void*)rdata.c_str(), rdata.size());
                }
            }
            return true;
        }
    };

	template<uint32_t msgtype, typename R> class ProcServer<msgtype, R> : public btos_api::IMessageHandler{
    private:
        std::function<R()> fn;
        std::map<uint64_t, std::string> return_buffers;
    public:
        ProcServer(std::function<R()> f) : fn(f) {}

        bool HandleMessage(const btos_api::Message &msg){
            if(msg.Type() == msgtype){
                R r = TupleCall(fn, std::make_tuple());
                std::stringstream rss;
                serialize(rss, r);
                auto rdata = rss.str();
                if(rdata.size() > BT_MSG_MAX){
                    auto cur = rdata.substr(0, BT_MSG_MAX);
                    auto rest = rdata.substr(BT_MSG_MAX);
                    auto id = msg.SendReply((void*)cur.c_str(), cur.size(), MessageType_Continue);
                    return_buffers[id] = rest;
                }else{
                    msg.SendReply((void*)rdata.c_str(), rdata.size());
                }
            }else if(msg.Type() == MessageType_Continue && return_buffers.find(msg.ReplyTo()) != return_buffers.end()){
                auto rdata = return_buffers[msg.ReplyTo()];
                return_buffers.erase(msg.ReplyTo());
                if(rdata.size() > BT_MSG_MAX){
                    auto cur = rdata.substr(0, BT_MSG_MAX);
                    auto rest = rdata.substr(BT_MSG_MAX);
                    auto id = msg.SendReply((void*)cur.c_str(), cur.size(), MessageType_Continue);
                    return_buffers[id] = rest;
                }else{
                    msg.SendReply((void*)rdata.c_str(), rdata.size());
                }
            }
            return true;
        }
    };

    template<uint32_t msgtype, typename R, typename ...Ps> auto NewProcServer(std::function<R(Ps...)> fn){
        return new ProcServer<msgtype, R, Ps...>(fn);
    }

    template<typename R, typename ...Ps> std::function<R(Ps...)> make_function(R(*fn)(Ps...)){
        return std::function<R(Ps...)>(fn);
    }
}

#endif
