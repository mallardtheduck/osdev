#ifndef _REGISTRY_INTERNAL_HPP
#define _REGISTRY_INTERNAL_HPP

#include <btos/messageloop.hpp>

#include <vector>
#include <memory>

#include "tables.hpp"

extern btos_api::MessageLoop msgloop;

Feature GetAssociation(const std::string &path);

namespace btos_api{
namespace registry{
extern std::vector<std::shared_ptr<IMessageHandler>> InitAPI();
}
}

#endif