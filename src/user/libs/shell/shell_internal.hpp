#ifndef _SHELL_INTERNAL_HPP
#define _SHELL_INTERNAL_HPP

#include <gds/surface.hpp>
#include <memory>

namespace btos_api{
namespace gui{
namespace shell{

std::shared_ptr<gds::Surface> LoadIcon(const char *path);

}
}
}
#endif