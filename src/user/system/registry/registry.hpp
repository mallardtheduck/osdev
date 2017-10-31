#ifndef _REGISTRY_HPP
#define _REGISTRY_HPP

#include <btos/messageloop.hpp>

#include <vector>
#include <memory>

extern MessageLoop msgloop;

namespace btos_api{
namespace registry{
extern std::vector<std::shared_ptr<IMessageHandler>> InitAPI();
}
}

#endif