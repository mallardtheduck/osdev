#include <gui/shell/fileopendialog.hpp>

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/imagebutton.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>
#include <gui/checkbox.hpp>
#include <gui/messagebox.hpp>

#include <gui/shell/foldertreeview.hpp>
#include <gui/shell/folderdetailsview.hpp>
#include <gui/shell/utils.hpp>

#include <wm/eventloop.hpp>

#include <util/tinyformat.hpp>

#include <stack>

#include "shell_internal.hpp"

namespace btos_api{
namespace gui{
namespace shell{

static const uint32_t totalFormWidth = 500;
static const uint32_t totalFormHeight = 320;

FileOpenDialog::FileOpenDialog(const std::string &p, std::function<bool(const bt_directory_entry &e)> f):
path(p), filter(f) {}

std::string FileOpenDialog::Show(wm::Window *parent){
	std::string selectedPath;
	
	auto form = std::make_shared<Form>(gds::Rect{0, 0, totalFormWidth, totalFormHeight}, FormOptions::ClosedFixed | wm_WindowOptions::NoHide, "Open file...");
	auto backBtn = std::make_shared<ImageButton>(gds::Rect{10, 10, 28, 28}, LoadIcon("icons/back_16.png"));
	auto pathText = std::make_shared<TextBox>(gds::Rect{48, 10, 404, 28});
	auto goBtn = std::make_shared<ImageButton>(gds::Rect{462, 10, 28, 28}, LoadIcon("icons/goto_16.png"));
	auto tree = std::make_shared<FolderTreeView>(gds::Rect{10, 48, 155, 222}, "");
	auto details = std::make_shared<FolderDetailsView>(gds::Rect{170, 48, 320, 222}, "");
	auto filterChk = std::make_shared<Checkbox>(gds::Rect{10, 280, 120, 30}, "Apply filter", true);
	auto okBtn = std::make_shared<Button>(gds::Rect{360, 280, 60, 30}, "OK");
	auto cancelBtn = std::make_shared<Button>(gds::Rect{430, 280, 60, 30}, "Cancel");
	
	backBtn->Disable();
	details->SetFilter(filter);
	
	std::stack<std::string> history;
	
	auto navigateTo = [&](const std::string &path, bool keep){
		if(path != details->GetPath()){
			if(keep){
				history.push(details->GetPath());
				backBtn->Enable();
			}
			details->SetPath(path);
			tree->SetSelectedPath(path);
			pathText->SetText(path);
		}
	};
	
	wm::EventLoop *loop = nullptr;
	
	auto confirm = [&](const std::string &path){
		selectedPath = path;
		form->Close();
		loop->RemoveWindow(form->GetID());
	};
	
	auto fileActivate = [&]{
		auto item = details->GetSelectedEntry();
		auto path = CombinePath({details->GetPath(), item.filename});
		if(item.type == FS_Directory){
			navigateTo(path, true);
		}else{
			confirm(path);
		}
	};
	
	details->OnActivate(fileActivate);
	
	tree->OnChange([&](TreeViewNode*){
		auto path = tree->GetSelectedPath();
		navigateTo(path, true);
	});
	
	backBtn->OnAction([&]{
		if(!history.empty()){
			navigateTo(history.top(), false);
			history.pop();
		}
		if(history.empty()) backBtn->Disable();
	});
	
	filterChk->OnChange([&](bool v){
		if(v) details->SetFilter(filter);
		else details->SetFilter(nullptr);
	});
	
	auto goAction = [&]{
		auto path = pathText->GetValue();
		auto check = bt_stat(path.c_str());
		if(path.empty()) navigateTo(path, true);
		else if(check.valid){
			if(check.type == FS_Directory){
				navigateTo(path, true);
			}else{
				confirm(path);
			}
		}else{
			MessageBox msg(tfm::format("File/path \"%s\" not found.", path), "Error", LoadIcon("icons/error_32.png"));
			msg.Show(form.get());
			pathText->SetText(details->GetPath());
		}
	};
	
	goBtn->OnAction(goAction);
	pathText->OnAction(goAction);
	
	cancelBtn->OnAction([&]{
		confirm("");
	});
	
	okBtn->OnAction(fileActivate);
	
	std::vector<std::shared_ptr<IControl>> controls = {backBtn, pathText, goBtn, tree, details, filterChk, okBtn, cancelBtn};
	if(!filter) controls.erase(std::find(controls.begin(), controls.end(), filterChk));
	
	form->AddControls(controls);
	
	if(parent){
		auto pInfo = parent->Info();
		auto pContentInfo = gds::Surface::Wrap(pInfo.gds_id, false).Info();
		
		auto totalParentWidth = pContentInfo.w + pInfo.contentX;
		auto totalParentHeight = pContentInfo.h + pInfo.contentY;
		
		auto formOffsetX = (totalParentWidth - totalFormWidth) / 2;
		auto formOffsetY = (totalParentHeight - totalFormHeight) / 2;
		
		int32_t formX = pInfo.x + formOffsetX;
		int32_t formY = pInfo.y + formOffsetY;
		
		form->SetPosition({formX, formY});
		
		parent->SetModal(*form);
	}else{
		auto smode = form->GetScreenMode();
		int32_t formX = (smode.width - totalFormWidth) / 2;
		int32_t formY = (smode.height - totalFormHeight) / 2;
		form->SetPosition({formX, formY});
	}
	
	std::unique_ptr<wm::EventLoop> loopPtr;
	if(parent) loop = wm::EventLoop::GetFor(*parent);
	if(!loop){
		loopPtr.reset(new wm::EventLoop());
		loop = loopPtr.get();
	}
	
	form->Open();
	loop->RunModal(form);
	
	return selectedPath;
}
	
}
}
}