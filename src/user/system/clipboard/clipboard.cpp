#include <util/rpc.hpp>
#include <btos/messageloop.hpp>
#include <btos/imessagehandler.hpp>

#include <btos/clipboard.hpp>

namespace btos_api{
namespace clipboard{
    
struct ClipboardContent{
    ContentHeader header;
    std::vector<char> data;
};

static std::map<Clipboard, ClipboardContent> content;
static uint64_t idCounter = 0;

ContentHeader GetContentHeader(Clipboard c){
    if(content.find(c) != content.end()) return content[c].header;
    else return {};
}

uint64_t CopyCut(Clipboard c, const std::string &type, const std::vector<char> &data, bool /*linkedBack*/){
    uint64_t id = ++idCounter;
    ClipboardContent cc;
    cc.header.id = id;
    cc.header.size = data.size();
    cc.header.type = type;
    cc.data = data;
    content[c] = cc;
    return id;
}

std::vector<char> Paste(Clipboard c, uint64_t id){
    if(content.find(c) != content.end() && content[c].header.id == id) return content[c].data;
    else return {};
}

void Clear(Clipboard c,uint64_t id){
    if(content.find(c) != content.end() && content[c].header.id == id) content.erase(c);
}

template<uint32_t id, typename F> void AddAPI(std::vector<std::shared_ptr<IMessageHandler>> &vec, F fn){
	std::shared_ptr<IMessageHandler> ptr { rpc::NewProcServer<id>(rpc::make_function(fn)) };
	vec.push_back(ptr);
}

std::vector<std::shared_ptr<IMessageHandler>> InitAPI(){
	std::vector<std::shared_ptr<IMessageHandler>> ret;
	AddAPI<RPCID::GetContentHeader>(ret, &GetContentHeader);
	AddAPI<RPCID::CopyCut>(ret, &CopyCut);
	AddAPI<RPCID::Paste>(ret, &Paste);
	AddAPI<RPCID::Clear>(ret, &Clear);
	return ret;
}


}
}

int main(){
    btos_api::MessageLoop msgloop;
    auto api = btos_api::clipboard::InitAPI();
	for(auto &a : api){
		msgloop.AddHandler(a);
	}
	msgloop.RunLoop();
	return 0;
}