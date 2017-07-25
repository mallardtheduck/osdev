#include <sm/services.hpp>
#include <btos/ini.hpp>

using namespace std;

namespace btos_api{
namespace sm{

Process Service::Start(){
	return Process::Spawn(path);
}

string Service::Name(){
	return name;
}

string Service::Path(){
	return path;
}

}
}
