#define BTOS_NO_USING

#include <vector>
#include <string>
#include <memory>
#include <map>

#include <btos/resc.h>
#include <gds/libgds.h>
#include <unistd.h>

#include <gui/messagebox.hpp>
#include <gui/shell/utils.hpp>
#include <btos/envvars.hpp>
#include <btos/process.hpp>

#include <util/tinyformat.hpp>

#include "elxrun_resc.tar.h"

namespace gui = btos_api::gui;
namespace sh = gui::shell;
namespace gds = btos_api::gds;
namespace resc = btos_api::resc;

using btos_api::Process;

static std::map<std::string, std::shared_ptr<gds::Surface>> loadedIcons;

std::shared_ptr<gds::Surface> LoadIcon(const char *path){
	auto i = loadedIcons.find(path);
	if(i == loadedIcons.end()){
		auto r = resc::Resc_LocalOpen(elxrun_resc_data, elxrun_resc_size);
		auto fd = resc::Resc_OpenResc(r, path);
		auto ret = GDS_LoadPNG(fd);
		close(fd);
		resc::Resc_Close(r);
		auto s = std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
		i = loadedIcons.insert(loadedIcons.end(), std::make_pair(path, s));
	}
	return i->second;
}

int main(int argc, char **argv){
	std::vector<std::string> args(argv, argv + argc);
	
	if(args.size() > 1){
		auto elxPath = args[1];
		auto elxName = sh::SplitPath(elxPath).back();
		auto info = sh::GetAppInfo(elxPath);
		if(!info.name.empty()) elxName = info.name;
		std::unique_ptr<btos_api::Process> proc;
		if(info.mode == "") info.mode = "CLI";
		if(info.mode == "GUI") proc.reset(new Process(Process::Spawn(elxPath)));
		else if(info.mode == "CLI"){
			auto drive = btos_api::GetEnv("SYSTEMDRIVE");
			auto termPath = tfm::format("%s:/BTOS/BIN/TERMWIN.ELX", drive);
			proc.reset(new Process(Process::Spawn(termPath, {elxPath})));
		}else{
			gui::MessageBox(tfm::format("This is a \"%s\" program and should not be run directly.", info.mode), elxName, LoadIcon("icons/error_32.png")).Show(nullptr);
		}
		if(proc){
			int ret = proc->Wait();
			if(ret == -1){
				gui::MessageBox(tfm::format("\"%s\" crashed.", elxName), "Crash", LoadIcon("icons/error_32.png")).Show(nullptr);
			}
			return ret;
		}
	}
	return 0;
}