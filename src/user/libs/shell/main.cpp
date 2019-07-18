#define BTOS_NO_USING

#include <gui/form.hpp>
#include <gui/shell/foldericonview.hpp>
#include <gui/shell/foldertreeview.hpp>
#include <gui/button.hpp>
#include <gui/label.hpp>
#include <wm/eventloop.hpp>

#include <btos/directory.hpp>
#include <cmd/path.hpp>

#include <stack>

#include <util/tinyformat.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;

int main(){
	std::stack<std::string> prevPath;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{200, 200, 500, 310}, wm_WindowOptions::Default | wm_WindowOptions::NoExpand, "Shell Library Test");
	auto icv = std::make_shared<sh::FolderIconView>(gds::Rect{170, 10, 320, 250}, "hdd:/");
	auto trv = std::make_shared<sh::FolderTreeView>(gds::Rect{10, 10, 150, 250}, "hdd:/");
	auto backBtn = std::make_shared<gui::Button>(gds::Rect{10, 270, 50, 30}, "Back");
	auto lbl = std::make_shared<gui::Label>(gds::Rect{70, 270, 410, 20}, "hdd:/", gui::Label::Justification::Left);
	
	backBtn->OnAction([&]{
		if(!prevPath.empty()){
			lbl->SetText(prevPath.top());
			icv->SetPath(prevPath.top());
			icv->SetValue(0);
			prevPath.pop();
		}
	});
	
	trv->OnChange([&](gui::TreeViewNode*){
		auto path = trv->GetSelectedPath();
		prevPath.push(icv->GetPath());
		lbl->SetText(path);
		icv->SetPath(path);
		icv->SetValue(0);
	});
	
	icv->OnActivate([&]{
		auto entry = icv->GetSelectedEntry();
		if(entry.valid && entry.type == FS_Directory){
			prevPath.push(icv->GetPath());
			auto path = btos_api::cmd::parse_path(prevPath.top() + "/" + entry.filename);
			lbl->SetText(path);
			icv->SetPath(path);
			icv->SetValue(0);
		}
	});
	
	form->AddControls({trv, icv, backBtn, lbl});
	
	btos_api::wm::EventLoop e;
	e.AddWindow(form);
	e.RunLoop();
	
	return 0;
}