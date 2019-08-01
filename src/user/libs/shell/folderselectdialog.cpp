#include <gui/shell/folderselectdialog.hpp>

#include <gui/shell/fileopendialog.hpp>

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/imagebutton.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>
#include <gui/checkbox.hpp>
#include <gui/messagebox.hpp>
#include <gui/inputbox.hpp>

#include <gui/shell/foldertreeview.hpp>
#include <gui/shell/utils.hpp>

#include <wm/eventloop.hpp>

#include <util/tinyformat.hpp>

#include <stack>

#include "shell_internal.hpp"

namespace btos_api{
namespace gui{
namespace shell{

FolderSelectDialog::FolderSelectDialog(const std::string &p) : 
defPath(p) {}

std::string FolderSelectDialog::Show(wm::Window *parent){
	std::string selectedPath = defPath;
	auto form = std::make_shared<Form>(gds::Rect{0, 0, 400, 320}, FormOptions::ClosedFixed | wm_WindowOptions::NoHide, "Select folder...");
	auto backBtn = std::make_shared<ImageButton>(gds::Rect{10, 10, 28, 28}, LoadIcon("icons/back_16.png"));
	auto pathText = std::make_shared<TextBox>(gds::Rect{48, 10, 266, 28});
	auto goBtn = std::make_shared<ImageButton>(gds::Rect{324, 10, 28, 28}, LoadIcon("icons/goto_16.png"));
	auto newFldrBtn = std::make_shared<ImageButton>(gds::Rect{362, 10, 28, 28}, LoadIcon("icons/new_folder_16.png"));
	auto tree = std::make_shared<FolderTreeView>(gds::Rect{10, 48, 380, 222}, "");
	auto okBtn = std::make_shared<Button>(gds::Rect{260, 280, 60, 30}, "OK");
	auto cancelBtn = std::make_shared<Button>(gds::Rect{330, 280, 60, 30}, "Cancel");
	
	std::stack<std::string> history;
	backBtn->Disable();
	
	auto loop = DialogEventLoop(parent);
	
	auto navigateTo = [&](const std::string &path, bool keep){
		if(keep){
			history.push(tree->GetSelectedPath());
			backBtn->Enable();
		}
		tree->SetSelectedPath(path);
		pathText->SetText(path);
	};
	
	auto confirm = [&](const std::string &path){
		selectedPath = path;
		form->Close();
		loop->RemoveWindow(form->GetID());
	};
	
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
	
	auto goAction = [&]{
		auto path = pathText->GetValue();
		auto check = bt_stat(path.c_str());
		if(path.empty() || (check.valid && check.type == FS_Directory)){
			navigateTo(path, true);
		}else{
			MessageBox msg(tfm::format("Cannot navigate to \"%s\".", path), "Error", LoadIcon("icons/error_32.png"));
			msg.Show(form.get());
		}
	};
	
	cancelBtn->OnAction([&]{
		confirm("");
	});
	
	okBtn->OnAction([&]{
		auto path = tree->GetSelectedPath();
		auto check = bt_stat(path.c_str());
		if(check.valid && check.type == FS_Directory){
			confirm(path);
		}else{
			MessageBox msg(tfm::format("Cannot navigate to \"%s\".", path), "Error", LoadIcon("icons/error_32.png"));
			msg.Show(form.get());
		}
	});
	
	goBtn->OnAction(goAction);
	pathText->OnAction(goAction);
	
	newFldrBtn->OnAction([&]{
		if(tree->GetSelectedPath() != ""){
			InputBox dlg("Enter new folder name:", "New Folder...");
			auto name = dlg.Show(form.get());
			if(!name.empty()){
				auto fullpath = CombinePath(tree->GetSelectedPath(), name);
				bt_dirhandle dh=bt_dopen(fullpath.c_str(), FS_Read | FS_Create);
				if(dh){
					bt_dclose(dh);
					navigateTo(fullpath, true);
				}else{
					MessageBox msg(tfm::format("Error creating folder."), "Error", LoadIcon("icons/error_32.png"));
					msg.Show(form.get());
				}
			}
		}else{
			MessageBox msg(tfm::format("Cannot create folder here."), "Error", LoadIcon("icons/error_32.png"));
			msg.Show(form.get());	
		}
	});
	
	form->AddControls({backBtn, pathText, goBtn, newFldrBtn, tree, okBtn, cancelBtn});
	
	tree->SetSelectedPath(defPath);
	
	form->SetPosition(DialogPosition(parent, *form));
	if(parent) parent->SetModal(*form);
	
	form->Open();
	loop->RunModal(form);
	
	if(parent) parent->ClearModal();
	return selectedPath;
}

}
}
}