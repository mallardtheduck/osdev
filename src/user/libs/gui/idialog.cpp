#include <gui/idialog.hpp>

namespace btos_api{
namespace gui{
	
gds::Point DialogPosition(wm::Window *parent, const wm::Window &form){
	auto info = form.Info();
	auto contentInfo = gds::Surface::Wrap(info.gds_id, false).Info();
	auto totalFormWidth = contentInfo.w + info.contentX;
	auto totalFormHeight = contentInfo.h + info.contentY;
	if(parent){
		auto pInfo = parent->Info();
		auto pContentInfo = gds::Surface::Wrap(pInfo.gds_id, false).Info();
		
		auto totalParentWidth = pContentInfo.w + pInfo.contentX;
		auto totalParentHeight = pContentInfo.h + pInfo.contentY;
		
		auto formOffsetX = (totalParentWidth - totalFormWidth) / 2;
		auto formOffsetY = (totalParentHeight - totalFormHeight) / 2;
		
		int32_t formX = pInfo.x + formOffsetX;
		int32_t formY = pInfo.y + formOffsetY;
		
		return {formX, formY};
	}else{
		auto smode = form.GetScreenMode();
		int32_t formX = (smode.width - totalFormWidth) / 2;
		int32_t formY = (smode.height - totalFormHeight) / 2;
		return {formX, formY};
	}
}

maybe_owned_ptr<wm::EventLoop> DialogEventLoop(wm::Window *parent){
	wm::EventLoop *loop = nullptr;
	if(parent) loop = wm::EventLoop::GetFor(*parent);
	if(!loop){
		return maybe_owned_ptr<wm::EventLoop>(new wm::EventLoop(), true);
	}else{
		return maybe_owned_ptr<wm::EventLoop>(loop, false);
	}
}

}
}