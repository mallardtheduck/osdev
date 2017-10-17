#include <btos/registry.hpp>
#include <util/rpc.hpp>
#include "../../system/registry/api_types.hpp"

using std::vector;
using std::string;

namespace btos_api{
namespace registry{

bt_pid_t pid;

vector<string> GetAllPackages(){
    return rpc::MakeClient<RPCID::GetAllPackages>(pid, GetAllPackages)();
}

}
}
