#include <btos/clipboard.hpp>
#include <util/rpc.hpp>
#include <sm/sm.h>

namespace btos_api{
namespace clipboard{

static bt_pid_t pid = 0;

static void SetPID(){
    if(!pid){
        pid = sm::SM_GetService("clipboard");
    }
}

ContentHeader GetContentHeader(Clipboard c){
	SetPID();
	return rpc::MakeClient<RPCID::GetContentHeader>(pid, GetContentHeader)(c);
}

uint64_t CopyCut(Clipboard c, const std::string &type, const std::vector<char> &data, bool linkedBack){
	SetPID();
	return rpc::MakeClient<RPCID::CopyCut>(pid, CopyCut)(c, type, data, linkedBack);
}

std::vector<char> Paste(Clipboard c, uint64_t id){
	SetPID();
	return rpc::MakeClient<RPCID::Paste>(pid, Paste)(c, id);
}

void Clear(Clipboard c, uint64_t id){
	SetPID();
	rpc::MakeClient<RPCID::Clear>(pid, Clear)(c, id);
}

}
}