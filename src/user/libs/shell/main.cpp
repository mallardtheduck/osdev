#define BTOS_NO_USING

#include <gui/form.hpp>
#include <gui/shell/foldericonview.hpp>
#include <gui/button.hpp>
#include <wm/eventloop.hpp>

#include <btos/directory.hpp>
#include <cmd/path.hpp>

#include <util/tinyformat.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;

int main(){
	std::string prevPath = "hdd:/";
	
	auto form = std::make_shared<gui::Form>(gds::Rect{200, 200, 500, 300}, wm_WindowOptions::Default | wm_WindowOptions::NoExpand, "Shell Library Test");
	auto icv = std::make_shared<sh::FolderIconView>(gds::Rect{10, 10, 480, 250}, prevPath);
	auto backBtn = std::make_shared<gui::Button>(gds::Rect{10, 260, 50, 30}, "Back");
	
	backBtn->OnAction([&]{
		icv->SetPath(prevPath);
	});
	
	icv->OnActivate([&]{
		auto entry = icv->GetSelectedEntry();
		if(entry.valid && entry.type == FS_Directory){
			prevPath = icv->GetPath();
			auto path = btos_api::cmd::parse_path(prevPath + "/" + entry.filename);
			tfm::printf("Changing view path to: %s\n", path);
			icv->SetPath(path);
		}
	});
	
	form->AddControls({icv, backBtn});
	
	btos_api::wm::EventLoop e;
	e.AddWindow(form);
	e.RunLoop();
	
	return 0;
}