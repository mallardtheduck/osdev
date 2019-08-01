#ifndef _IDIALOG_HPP
#define _IDIALOG_HPP

#include <wm/window.hpp>

namespace btos_api{
namespace gui{
	
template<typename T> class IDialog{
public:
	virtual T Show(wm::Window *parent) = 0;
	virtual ~IDialog(){}
};

}
}

#endif