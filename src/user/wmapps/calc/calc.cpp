#define BTOS_NO_USING

#include <btos/resc.h>
#include <unistd.h>
#include <map>

#include <gui/toolbar.hpp>
#include <gui/messagebox.hpp>
#include <wm/menu.hpp>
#include <wm/eventloop.hpp>

#include "calc_resc.tar.h"
#include "icalcmode.hpp"
#include "stdmode.hpp"
#include "scimode.hpp"
#include "progmode.hpp"
#include "calc.hpp"

namespace gds = btos_api::gds;
namespace resc = btos_api::resc;
namespace gui = btos_api::gui;
namespace wm = btos_api::wm;

CalcMode CurrentMode = CalcMode::Standard;

static resc::RescHandle rsc;
static std::map<std::string, std::shared_ptr<gds::Surface>> pngs;
static std::shared_ptr<wm::Menu> menu;
static wm::EventLoop loop;

static std::unique_ptr<ICalcMode> currentCalc;
static std::shared_ptr<gui::Form> currentForm;

static const gds::Point defaultPos = {120, 120};

template<typename T, CalcMode M> static void SwitchCalc(){
	gds::Point pos = defaultPos;
	if(currentForm){
		pos = currentForm->GetPosition();
		loop.RemoveWindow(currentForm->GetID());
		currentForm->Close();
		currentForm.reset();
	}
	CurrentMode = M;
	currentCalc.reset(new T(pos));
	currentForm = currentCalc->Show();
	loop.AddWindow(currentForm);
}

bool MenuHandler(int id){
	switch(id){
		case 1:
			SwitchCalc<StandardMode, CalcMode::Standard>();
			break;
		case 2:
			SwitchCalc<ScientificMode, CalcMode::Scientific>();
			break;
		case 3:
			SwitchCalc<ProgrammerMode, CalcMode::Programmer>();
			break;
		
		case 4:
			//Copy
			break;
		case 5:
			//Paste
			break;
		case 6:
			gui::MessageBox("BT/OS Calculator", "About", LoadPNG("calc_32.png")).Show(currentForm.get());
			break;
	}
	return true;
}

void MakeToolbarAndMenu(std::shared_ptr<gui::Form> form){
	auto iconStd = LoadPNG("calc_standard.png");
	auto iconSci = LoadPNG("calc_scientific.png");
	auto iconProg = LoadPNG("calc_programmer.png");
	
	auto iconCopy = LoadPNG("editcopy.png");
	auto iconPaste = LoadPNG("editpaste.png");
	
	auto iconCalc = LoadPNG("calc_16.png");
	
	if(menu){
		loop.RemoveMenu(menu->GetID());
	}
	menu = std::make_shared<wm::Menu>();
	auto stdModeMenuFlags = (CurrentMode == CalcMode::Standard) ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
	menu->AddItem(wm::MenuItem(1, "Standard Mode", stdModeMenuFlags, iconStd.get()));
	auto sciModeMenuFlags = (CurrentMode == CalcMode::Scientific) ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
	menu->AddItem(wm::MenuItem(2, "Scientific Mode", sciModeMenuFlags, iconSci.get()));
	auto progModeMenuFlags = (CurrentMode == CalcMode::Programmer) ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
	menu->AddItem(wm::MenuItem(3, "Programmer Mode", progModeMenuFlags, iconProg.get()));
	menu->AddItem(wm::MenuItem(0, "",  wm_MenuItemFlags::Separator));
	menu->AddItem(wm::MenuItem(4, "Copy", wm_MenuItemFlags::Default, iconCopy.get()));
	menu->AddItem(wm::MenuItem(5, "Paste", wm_MenuItemFlags::Default, iconPaste.get()));
	menu->AddItem(wm::MenuItem(0, "",  wm_MenuItemFlags::Separator));
	menu->AddItem(wm::MenuItem(6, "About...", wm_MenuItemFlags::Default, iconCalc.get()));
	menu->SetEventHandler(MenuHandler);
	loop.AddMenu(menu);
	form->SetMenu(*menu);
	
	auto toolbar = std::make_shared<gui::Toolbar>();
	auto tbModeStd = std::make_shared<gui::ToolbarButton>(iconStd);
	tbModeStd->OnAction(SwitchCalc<StandardMode, CalcMode::Standard>);
	auto tbModeSci = std::make_shared<gui::ToolbarButton>(iconSci);
	tbModeSci->OnAction(SwitchCalc<ScientificMode, CalcMode::Scientific>);
	auto tbModeProg = std::make_shared<gui::ToolbarButton>(iconProg);
	tbModeProg->OnAction(SwitchCalc<ProgrammerMode, CalcMode::Programmer>);
	
	switch(CurrentMode){
		case CalcMode::Standard:
			tbModeStd->Disable();
			break;
		case CalcMode::Scientific:
			tbModeSci->Disable();
			break;
		case CalcMode::Programmer:
			tbModeProg->Disable();
			break;
	}
	
	auto tbSpacer = std::make_shared<gui::ToolbarSpacer>();
	auto tbCopy = std::make_shared<gui::ToolbarButton>(iconCopy);
	auto tbPaste = std::make_shared<gui::ToolbarButton>(iconPaste);
	toolbar->Controls().insert(toolbar->Controls().end(), {tbModeStd, tbModeSci, tbModeProg, tbSpacer, tbCopy, tbPaste});
	toolbar->Refresh();
	
	form->AddControls({toolbar});
}

std::shared_ptr<gds::Surface> LoadPNG(const char *path){
	auto it = pngs.find(path);
	if(it == pngs.end()){
		auto fd = resc::Resc_OpenResc(rsc, path);
		auto ret = GDS_LoadPNG(fd);
		close(fd);
		auto png = std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
		auto r = pngs.insert({path, png});
		if(r.second) it = r.first;
	}
	return it->second;
}

int main(){
	rsc = resc::Resc_LocalOpen(calc_resc_data, calc_resc_size);
	
	SwitchCalc<StandardMode, CalcMode::Standard>();
	loop.RunLoop();
	
	resc::Resc_Close(rsc);
	return 0;
}