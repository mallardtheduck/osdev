#include <gui/idialog.hpp>

namespace btos_api{
namespace gui{
	
gds::Point DialogPosition(wm::Window *parent, const wm::Window &form){
	auto info = form.Info();
	auto smode = form.GetScreenMode();
	auto contentInfo = gds::Surface::Wrap(info.gds_id, false).Info();
	int32_t totalFormWidth = contentInfo.w + info.contentX;
	int32_t totalFormHeight = contentInfo.h + info.contentY;
	if(parent){
		auto pInfo = parent->Info();
		auto pContentInfo = gds::Surface::Wrap(pInfo.gds_id, false).Info();
		
		int32_t totalParentWidth = pContentInfo.w + pInfo.contentX;
		int32_t totalParentHeight = pContentInfo.h + pInfo.contentY;
		
		int32_t formOffsetX = (totalParentWidth - totalFormWidth) / 2;
		int32_t formOffsetY = (totalParentHeight - totalFormHeight) / 2;
		
		int32_t formX = pInfo.x + formOffsetX;
		int32_t formY = pInfo.y + formOffsetY;

		if(formX + totalFormWidth > (int32_t)smode.width) formX = smode.width - totalFormWidth;
		if(formX < 0) formX = 0;

		if(formY + totalFormHeight > (int32_t)smode.height) formY = smode.height - totalFormHeight;
		if(formY < 0) formY = 0;
		
		return {formX, formY};
	}else{
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