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

void CopyCut(Clipboard c, const ContentHeader &h, const std::vector<char> &data, bool linkedBack){
	SetPID();
	rpc::MakeClient<RPCID::CopyCut>(pid, CopyCut)(c, h, data, linkedBack);
}

std::vector<char> Paste(Clipboard c, uint64_t id){
	SetPID();
	return rpc::MakeClient<RPCID::Paste>(pid, Paste)(c, id);
}

}
}