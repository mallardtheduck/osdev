#define BTOS_NO_USING

#include "notepad.hpp"

#include <gui/form.hpp>
#include <gui/toolbar.hpp>
#include <gui/statusbar.hpp>
#include <gui/textarea.hpp>
#include <gui/messagebox.hpp>
#include <gui/actionmanager.hpp>

#include <gui/shell/fileopendialog.hpp>
#include <gui/shell/filesavedialog.hpp>
#include <gui/shell/utils.hpp>

#include <wm/eventloop.hpp>
#include <wm/menu.hpp>

#include <btos/clipboard.hpp>

#include <fstream>
#include <iterator>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;
namespace wm = btos_api::wm;
namespace clip = btos_api::clipboard;

static const uint32_t formWidth = 500;
static const uint32_t formHeight = 400;
static const uint32_t toolbarHeight = 32;
static const uint32_t statusbarHeight = 20;

int main(int argc, char **argv){
	std::vector<std::string> args(argv, argv + argc);
	
	std::string filename;
	bool modified = false;
	
	auto displayFilename = [&]() -> std::string{
		if(filename.empty()) return "Unsaved file";
		else return filename;
	};
	
	auto form = std::make_shared<gui::Form>(gds::Rect{100, 50, formWidth, formHeight}, gui::FormOptions::ClosedSizable, "Notepad");
	auto toolbar = std::make_shared<gui::Toolbar>();
	auto statusbar = std::make_shared<gui::StatusBar>(displayFilename());
	auto textarea = std::make_shared<gui::TextArea>(gds::Rect{1, toolbarHeight + 1, formWidth - 2, formHeight - toolbarHeight - statusbarHeight}, "", true);
	
	auto filenew = [&]{
		filename.clear();
		textarea->SetText("");
		statusbar->SetText(displayFilename());
	};
	
	auto openFile = [&](const std::string &path){
		filename = path;
		std::ifstream ifs(path);
		std::string content;
		std::copy(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), std::back_inserter<std::string>(content));
		textarea->SetText(content);
		statusbar->SetText(displayFilename());
		modified = false;
	};
	
	auto open = [&]{
		sh::FileOpenDialog dlg("", sh::FileExtensionPredicate({".txt", ".cmd", ".ini", ".inf"}));
		auto path = dlg.Show(form.get());
		if(!path.empty()){
			openFile(path);
		}
	};
	
	std::function<void()> saveas;
	
	auto save = [&]{
		if(!filename.empty()){
			std::ofstream ofs(filename);
			std::string content = textarea->GetValue();
			std::copy(content.begin(), content.end(), std::ostreambuf_iterator<char>(ofs));
			modified = false;
		}else{
			saveas();
		}
	};
	
	saveas = [&]{
		sh::FileSaveDialog dlg("untitled.txt", ".txt", "", sh::FileExtensionPredicate({".txt", ".cmd", ".ini", ".inf"}));
		auto path = dlg.Show(form.get());
		if(!path.empty()){
			filename = path;
			save();
			statusbar->SetText(displayFilename());
		}
	};
	
	auto copy = [&]{
		auto text = textarea->GetSelection();
		if(!text.empty()){
			std::vector<char> data(text.begin(), text.end());
			clip::CopyCut(clip::Clipboard::Primary, "text/plain", data);
		}
	};
	
	auto cut = [&]{
		copy();
		textarea->CutSelection();
		modified = true;
	};
	
	auto paste = [&]{
		auto header = clip::GetContentHeader(clip::Clipboard::Primary);
		if(header.type == "text/plain"){
			auto data = clip::Paste(clip::Clipboard::Primary, header.id);
			std::string text(data.data(), data.size());
			textarea->InsertText(text);
		}
		modified = true;
	};
	
	auto about = [&]{
		gui::MessageBox("BT/OS Notepad", "About", LoadIcon("icons/notepad_32.png")).Show(form.get());
	};
	
	gui::ActionManager am;
	am.Add("new", "New", LoadIcon("icons/filenew_16.png"), filenew);
	am.Add("open", "Open file...", LoadIcon("icons/fileopen_16.png"), open);
	am.Add("save", "Save", LoadIcon("icons/filesave_16.png"), save);
	am.Add("saveas", "Save as...", LoadIcon("icons/filesaveas_16.png"), saveas);
	am.Add("cut", "Cut", LoadIcon("icons/editcut_16.png"), cut);
	am.Add("copy", "Copy", LoadIcon("icons/editcopy_16.png"), copy);
	am.Add("paste", "Paste", LoadIcon("icons/editpaste_16.png"), paste);
	am.Add("about", "About...", LoadIcon("icons/notepad_16.png"), about);
	
	toolbar->Controls() = {
		am.GetToolbarButton("new"),
		am.GetToolbarButton("open"),
		am.GetToolbarButton("save"),
		am.GetToolbarButton("saveas"),
		std::make_shared<gui::ToolbarSpacer>(),
		am.GetToolbarButton("cut"),
		am.GetToolbarButton("copy"),
		am.GetToolbarButton("paste")
	};
	toolbar->Refresh();
	
	form->AddControls({toolbar, statusbar, textarea});
	
	form->OnResize([&](const gds::Rect &size){
		form->MoveControl(textarea, gds::Rect{1, toolbarHeight + 1, size.w - 2, size.h - toolbarHeight - statusbarHeight});
	});
	
	textarea->OnKeyPress([&](uint32_t){
		modified = true;
		return false;
	});
	
	form->OnClose([&]{
		if(modified){
			auto btn = gui::MessageBox("File not saved! Save file?", "Close", LoadIcon("icons/question_32.png"), {"Save", "Close", "Cancel"}).Show(form.get());
			if(btn == 0) save();
			if(btn == 2) return true;
		}
		return false;
	});
	
	auto menuHandler = [&](int action) -> bool{
		am.MenuHandler(action);
		return true;
	};
	
	auto fileMenu = std::make_shared<wm::Menu>();
	fileMenu->AddItem(am.GetMenuItem("new"));
	fileMenu->AddItem(am.GetMenuItem("open"));
	fileMenu->AddItem(am.GetMenuItem("save"));
	fileMenu->AddItem(am.GetMenuItem("saveas"));
	fileMenu->SetEventHandler(menuHandler);
	
	auto editMenu = std::make_shared<wm::Menu>();
	editMenu->AddItem(am.GetMenuItem("cut"));
	editMenu->AddItem(am.GetMenuItem("copy"));
	editMenu->AddItem(am.GetMenuItem("paste"));
	editMenu->SetEventHandler(menuHandler);
	
	auto mainMenu = std::make_shared<wm::Menu>();
	mainMenu->AddItem(wm::MenuItem(0, "File", wm_MenuItemFlags::ChildMenu, nullptr, fileMenu.get()));
	mainMenu->AddItem(wm::MenuItem(0, "Edit", wm_MenuItemFlags::ChildMenu, nullptr, editMenu.get()));
	mainMenu->AddItem(wm::MenuItem(0, "", wm_MenuItemFlags::Separator));
	mainMenu->AddItem(am.GetMenuItem("about"));
	mainMenu->SetEventHandler(menuHandler);
	
	form->SetMenu(*mainMenu);
	
	if(args.size() > 1) openFile(args[1]);
		
	wm::EventLoop loop;
	loop.AddWindow(form);
	loop.AddMenu(fileMenu);
	loop.AddMenu(editMenu);
	loop.AddMenu(mainMenu);
	form->Show();
	loop.RunLoop();
	return 0;
}
