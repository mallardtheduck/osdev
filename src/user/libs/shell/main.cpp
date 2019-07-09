#define BTOS_NO_USING

#include <gui/form.hpp>
#include <gui/iconview.hpp>
#include <gui/shell/utils.hpp>
#include <wm/eventloop.hpp>

#include <btos/directory.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;

int main(){
	auto form = std::make_shared<gui::Form>(gds::Rect{200, 200, 500, 300}, wm_WindowOptions::Default | wm_WindowOptions::NoExpand, "Shell Library Test");
	auto icv = std::make_shared<gui::IconView>(gds::Rect{10, 10, 480, 250}, 32, false);
	
	auto directory = btos_api::Directory("hdd:/", FS_Read);
	for(auto d : directory){
		auto icon = sh::GetPathIcon(std::string("hdd:/") + d.filename, 32);
		icv->Items().push_back(d.filename);
		icv->SetItemIcon(icv->Items().size() - 1, icon);
	}
	icv->Refresh();
	form->AddControl(icv);
	
	btos_api::wm::EventLoop e;
	e.AddWindow(form);
	e.RunLoop();
	
	return 0;
}