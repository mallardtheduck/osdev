#include <util/rpc.hpp>
#include <btos/registry.hpp>

namespace btos_api{
namespace registry{

inline void serialize(std::ostream &os, const PackageInfo &pi){
	rpc::serialize(os, pi.id);
	rpc::serialize(os, pi.name);
	rpc::serialize(os, pi.description);
	rpc::serialize(os, pi.path);
	rpc::serialize(os, pi.ver);
}

inline void deserialize(std::istream &is, PackageInfo &pi){
	rpc::deserialize(is, pi.id);
	rpc::deserialize(is, pi.name);
	rpc::deserialize(is, pi.description);
	rpc::deserialize(is, pi.path);
	rpc::deserialize(is, pi.ver);
}

inline void serialize(std::ostream &os, const FeatureInfo &fi){
    rpc::serialize(os, fi.id);
    rpc::serialize(os, fi.package);
    rpc::serialize(os, fi.name);
    rpc::serialize(os, fi.description);
    rpc::serialize(os, fi.type);
    rpc::serialize(os, fi.ver);
    rpc::serialize(os, fi.path);
    rpc::serialize(os, fi.file);
    rpc::serialize(os, fi.flags);
}

inline void deserialize(std::istream &is, FeatureInfo &fi){
    rpc::deserialize(is, fi.id);
    rpc::deserialize(is, fi.package);
    rpc::deserialize(is, fi.name);
    rpc::deserialize(is, fi.description);
    rpc::deserialize(is, fi.type);
    rpc::deserialize(is, fi.ver);
    rpc::deserialize(is, fi.path);
    rpc::deserialize(is, fi.file);
    rpc::deserialize(is, fi.flags);
}

}
}
