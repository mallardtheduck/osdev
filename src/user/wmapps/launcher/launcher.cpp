#define BTOS_NO_USING

#include <gui/form.hpp>
#include <gui/label.hpp>
#include <gui/imagebutton.hpp>
#include <gui/messagebox.hpp>
#include <gui/inputbox.hpp>

#include <gui/shell/utils.hpp>

#include <wm/eventloop.hpp>
#include <wm/libwm.h>

#include <gds/libgds.h>

#include <btos/table.hpp>
#include <btos/process.hpp>
#include <btos/resc.h>
#include <btos/messageloop.hpp>
#include <btos/timer.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>

#include <unistd.h>
#include <time.h>

#include "launcher_resc.tar.h"

#include <util/tinyformat.hpp>

namespace gui = btos_api::gui;
namespace wm = btos_api::wm;
namespace gds = btos_api::gds;
namespace sh = gui::shell;
namespace resc = btos_api::resc;

static const uint32_t baseFormWidth = 71;
static const uint32_t formHeight = 64;
static const uint32_t appBtnSize = 54;
static const uint32_t margin = 5;

static std::vector<std::string> pinnedApps = {"HDD:/GUI/APPVIEW.ELX", "HDD:/GUI/FOLDER.ELX", "HDD:/BTOS/BIN/TERMWIN.ELX"};

bool CaseInsensitiveCompare(const std::string &a, const std::string &b){
	return a.length() == b.length() && std::equal(a.begin(), a.end(), b.begin(), [](unsigned char a, unsigned char b){
		return tolower(a) == tolower(b);
	});
}

struct AppMapCompare{
	bool operator()(const std::string &a, const std::string &b){
		bool aPinned = std::find_if(pinnedApps.begin(), pinnedApps.end(), [&](const std::string &p){
			return CaseInsensitiveCompare(a, p);
		}) != pinnedApps.end();
		bool bPinned = std::find_if(pinnedApps.begin(), pinnedApps.end(), [&](const std::string &p){
			return CaseInsensitiveCompare(b, p);
		}) != pinnedApps.end();
		
		if(aPinned && !bPinned) return true;
		if(!aPinned && bPinned) return false;
		return a < b;
	}
};

typedef std::map<std::string, std::vector<uint64_t>, AppMapCompare> AppMap;

AppMap GetAppsAndWindows(){
	std::ifstream procsfile{"INFO:/PROCS"};
	auto procstbl = btos_api::parsecsv(procsfile);
	std::map<btos_api::bt_pid_t, std::string> procs;
	for(auto &p : procstbl.rows){
		procs[strtoul(p["PID"].c_str(), nullptr, 10)] = p["path"];
	}
	procsfile.close();
	
	AppMap ret;
	
	for(auto p : pinnedApps) ret[p] = {};
	
	auto ids = WM_GetValidWindowIDs();
	for(auto wid : ids){
		WM_SelectWindow(wid);
		auto info = WM_WindowInfo();
		auto path = procs[info.owner];
		auto retIt = std::find_if(ret.begin(), ret.end(), [&](const AppMap::value_type &r){
			return CaseInsensitiveCompare(r.first, path);
		});
		if(retIt == ret.end()) retIt = ret.insert({path, {}}).first;
		retIt->second.push_back(wid);
	}
	
	return ret;
}

bool AppListChanged(const AppMap &curApps, const AppMap &apps){
	return curApps.size() != apps.size() || !std::equal(curApps.begin(), curApps.end(), apps.begin(),
	[](const AppMap::value_type &a, const AppMap::value_type &b){
		return a.first == b.first;
	});
}

static std::map<std::string, std::shared_ptr<gds::Surface>> loadedIcons;

std::shared_ptr<gds::Surface> LoadIcon(const char *path){
	auto i = loadedIcons.find(path);
	if(i == loadedIcons.end()){
		auto r = resc::Resc_LocalOpen(launcher_resc_data, launcher_resc_size);
		auto fd = resc::Resc_OpenResc(r, path);
		auto ret = GDS_LoadPNG(fd);
		close(fd);
		resc::Resc_Close(r);
		auto s = std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
		i = loadedIcons.insert(loadedIcons.end(), std::make_pair(path, s));
	}
	return i->second;
}

int main(){
	uint32_t formWidth = baseFormWidth;
	btos_api::MessageLoop msgLoop;
	auto loop = std::make_shared<wm::EventLoop>();

	std::vector<std::shared_ptr<gui::IControl>> appButtons;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{0, 0, formWidth, formHeight}, wm_WindowOptions::NoTitle | wm_WindowOptions::Unlisted, "Launcher");
	auto timeLbl = std::make_shared<gui::Label>(gds::Rect{5, 5, 61, 21}, "--:-- XX");
	auto exitBtn = std::make_shared<gui::ImageButton>(gds::Rect{5, 31, 28, 28}, LoadIcon("icons/exit_16.png"));
	auto runBtn = std::make_shared<gui::ImageButton>(gds::Rect{38, 31, 28, 28}, LoadIcon("icons/run_16.png"));

	exitBtn->OnAction([&]{
		auto btn = gui::MessageBox("Exit and end session?", "Exit", LoadIcon("icons/question_32.png"), {"Yes", "No"}).Show(form.get());
		if(btn == 0){
			form->Close();
			loop->RemoveWindow(form->GetID());
			msgLoop.Terminate();
		}
	});
	
	form->AddControls({timeLbl, exitBtn, runBtn});
	
	AppMap curApps;
	
	std::function<void()> updateBtns;
	
	auto appBtnClick = [&](const std::string &path){
		updateBtns();
		auto it = std::find_if(curApps.begin(), curApps.end(), [&](const AppMap::value_type &a){
			return CaseInsensitiveCompare(a.first, path);
		});
		if(it != curApps.end()){
			auto &a = *it;
			if(!a.second.empty()){
				for(auto w : a.second){
					WM_SelectWindow(w);
					auto info = WM_WindowInfo();
					WM_ChangeOptions(info.options | wm_WindowOptions::Visible);
					WM_RaiseWindow();
				}
			}else{
				btos_api::Process::Spawn(a.first);
			}
		}
	};
	
	updateBtns = [&]{
		auto apps = GetAppsAndWindows();
		if(AppListChanged(apps, curApps)){
			formWidth = baseFormWidth + (apps.size() * (appBtnSize + margin)) + margin;
			
			form->Resize(formWidth, formHeight);
			
			for(auto &b : appButtons) form->RemoveControl(b);
			appButtons.clear();
			
			size_t appBtnCount = 0;
			for(auto &a : apps){
				int32_t xPos = baseFormWidth + (appBtnCount * (appBtnSize + margin)) + margin;
				auto btn = std::make_shared<gui::ImageButton>(gds::Rect{xPos, margin, appBtnSize, appBtnSize}, sh::GetPathIcon(a.first, 32));
				btn->OnAction([=]{
					appBtnClick(a.first);
				});
				appButtons.push_back(btn);
				++appBtnCount;
			}
			form->AddControls(appButtons);
			
			auto mode = form->GetScreenMode();
			int32_t formX = (mode.width - formWidth) / 2;
			int32_t formY = mode.height - formHeight;
			
			form->SetPosition({formX, formY});
		}
		curApps = apps;
	};
	
	updateBtns();
	form->OnGlobal([&](const wm_Event &){
		updateBtns();
	});

	std::string curTime;
	auto updateClock = [&]{
		time_t rawtime;
		time(&rawtime);
		auto timeinfo = localtime(&rawtime);
		std::unique_ptr<char[]> buf(new char[1024]);
		strftime(buf.get(), 1024, "%l:%M %p", timeinfo);
		if(curTime != buf.get()){
			auto _ = loop->Lock();
			timeLbl->SetText(buf.get());
			curTime = buf.get();
		}
	};

	auto timer = std::make_shared<btos_api::Timer>(500);
	timer->SetHandler([&](btos_api::Timer &t)->bool{
		t.Reset();
		updateClock();
		return true;
	});
	updateClock();
	timer->Reset();
	
	loop->AddWindow(form);
	form->Show();
	msgLoop.AddHandler(loop);
	msgLoop.AddHandler(timer);
	msgLoop.RunLoop();
	
	return 0;
}