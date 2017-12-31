#include <btos/registry.hpp>

using std::vector;
using std::string;

namespace btos_api{
namespace registry{

string GetFeaturePath(uint64_t id){
    auto feat = GetFeatureById(id);
    auto pkg = GetPackageById(feat.package);
    if(feat.path.empty() || feat.path.back() != '/') feat.path += '/';
	return pkg.path + feat.path + feat.file;
}

}
}