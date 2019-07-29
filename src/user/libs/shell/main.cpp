#define BTOS_NO_USING

#include <gui/shell/foldericonview.hpp>
#include <gui/shell/foldertreeview.hpp>
#include <gui/shell/folderdetailsview.hpp>
#include <gui/shell/fileopendialog.hpp>

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/label.hpp>
#include <gui/messagebox.hpp>
#include <wm/eventloop.hpp>

#include <btos/directory.hpp>
#include <cmd/path.hpp>
#include <gui/shell/utils.hpp>

#include <stack>

#include <util/tinyformat.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;

void outputPathParts(const std::string &path){
	auto parts = sh::SplitPath(path);
	for(auto &p : parts){
		tfm::printf("[\"%s\"]", p);
	}
	tfm::printf("\n");
}

int main(){
	outputPathParts("");
	outputPathParts("hdd:");
	outputPathParts("hdd:/");
	outputPathParts("hdd:/btos");
	outputPathParts("hdd:/btos/system");
	outputPathParts("hdd:/btos/cmd/cmd.elx");
	outputPathParts("potato");
	
	std::stack<std::string> prevPath;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{200, 100, 500, 420}, wm_WindowOptions::Default | wm_WindowOptions::NoExpand, "Shell Library Test");
	auto icv = std::make_shared<sh::FolderIconView>(gds::Rect{170, 10, 320, 200}, "");
	auto trv = std::make_shared<sh::FolderTreeView>(gds::Rect{10, 10, 150, 200}, "");
	auto backBtn = std::make_shared<gui::Button>(gds::Rect{10, 220, 50, 30}, "Back");
	auto lbl = std::make_shared<gui::Label>(gds::Rect{70, 220, 300, 30}, "", gui::Label::Justification::Left);
	auto dtv = std::make_shared<sh::FolderDetailsView>(gds::Rect{10, 260, 480, 150}, "");
	
	auto openBtn = std::make_shared<gui::Button>(gds::Rect{380, 220, 50, 30}, "Open");
	
	backBtn->OnAction([&]{
		if(!prevPath.empty()){
			lbl->SetText(prevPath.top());
			icv->SetPath(prevPath.top());
			icv->SetValue(0);
			dtv->SetPath(prevPath.top());
			dtv->SetValue(0);
			trv->SetSelectedPath(prevPath.top());
			prevPath.pop();
		}
	});
	
	trv->OnChange([&](gui::TreeViewNode*){
		auto path = trv->GetSelectedPath();
		prevPath.push(icv->GetPath());
		lbl->SetText(path);
		icv->SetPath(path);
		icv->SetValue(0);
		dtv->SetPath(path);
		dtv->SetValue(0);
	});
	
	icv->OnActivate([&]{
		auto entry = icv->GetSelectedEntry();
		if(entry.valid && entry.type == FS_Directory){
			prevPath.push(icv->GetPath());
			auto path = btos_api::cmd::parse_path(sh::CombinePath({prevPath.top(), entry.filename}));
			lbl->SetText(path);
			icv->SetPath(path);
			icv->SetValue(0);
			trv->SetSelectedPath(path);
			dtv->SetPath(path);
			dtv->SetValue(0);
		}
	});
	
	dtv->OnActivate([&]{
		auto entry = dtv->GetSelectedEntry();	
		if(entry.valid && entry.type == FS_Directory){
			prevPath.push(icv->GetPath());
			auto path = btos_api::cmd::parse_path(sh::CombinePath({prevPath.top(), entry.filename}));
			lbl->SetText(path);
			icv->SetPath(path);
			icv->SetValue(0);
			trv->SetSelectedPath(path);
			dtv->SetPath(path);
			dtv->SetValue(0);
		}
	});
	
	openBtn->OnAction([&]{
		sh::FileOpenDialog dlg;
		auto path = dlg.Show(form.get());
		gui::MessageBox(tfm::format("Selected: %s", path), "Open").Show(form.get());
	});
	
	form->AddControls({trv, icv, backBtn, lbl, dtv, openBtn});
	
	btos_api::wm::EventLoop e;
	e.AddWindow(form);
	e.RunLoop();
	
	return 0;
}