#include <gui/shell/fileopendialog.hpp>

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>
#include <gui/shell/foldertreeview.hpp>
#include <gui/shell/folderdetailsview.hpp>

#include <wm/eventloop.hpp>

namespace btos_api{
namespace gui{
namespace shell{

FileOpenDialog::FileOpenDialog(const std::string &p, std::function<bool(const bt_directory_entry &e)> f):
path(p), filter(f) {}

std::string FileOpenDialog::Show(wm::Window *parent){
	auto form = std::make_shared<Form>(gds::Rect{0, 0, 500, 320}, FormOptions::ClosedFixed | wm_WindowOptions::NoHide, "Open file...");
	auto backBtn = std::make_shared<Button>(gds::Rect{10, 10, 50, 30}, "Back");
	auto pathText = std::make_shared<TextBox>(gds::Rect{70, 10, 360, 30});
	auto goBtn = std::make_shared<Button>(gds::Rect{440, 10, 50, 30}, "Go");
	auto tree = std::make_shared<FolderTreeView>(gds::Rect{10, 50, 155, 220}, "");
	auto details = std::make_shared<FolderDetailsView>(gds::Rect{170, 50, 320, 220}, "");
	auto okBtn = std::make_shared<Button>(gds::Rect{360, 280, 60, 30}, "OK");
	auto cancelBtn = std::make_shared<Button>(gds::Rect{430, 280, 60, 30}, "Cancel");
	
	form->AddControls({backBtn, pathText, goBtn, tree, details, okBtn, cancelBtn});
	
	wm::EventLoop *loop = nullptr;
	std::unique_ptr<wm::EventLoop> loopPtr;
	if(parent) loop = wm::EventLoop::GetCurrent();
	if(!loop){
		loopPtr.reset(new wm::EventLoop());
		loop = loopPtr.get();
	}
	
	form->Open();
	loop->RunModal(form);
	
	return "";
}
	
}
}
}