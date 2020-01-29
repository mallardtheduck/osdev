#ifndef _IDIALOG_HPP
#define _IDIALOG_HPP

#include <wm/window.hpp>
#include <wm/eventloop.hpp>
#include <gds/geom.hpp>
#include <util/maybe_owned_ptr.hpp>

namespace btos_api{
namespace gui{
	
gds::Point DialogPosition(wm::Window *parent, const wm::Window &form);
maybe_owned_ptr<wm::EventLoop> DialogEventLoop(wm::Window *parent);

template<typename T> class IDialog{
public:
	virtual T Show(wm::Window *parent) = 0;
	virtual ~IDialog(){}
};

}
}

#endif