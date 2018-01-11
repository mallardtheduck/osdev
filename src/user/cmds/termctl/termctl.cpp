#include <btos.h>
#include <crt_support.h>
#include <dev/terminal.h>
#include <dev/terminal.hpp>
#include <dev/video_dev.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <util/clipp.hpp>
#include <btos/envvars.hpp>

using namespace std;
using namespace clipp;

vector<string> args_to_vec(int argc, char **argv){
	vector<string> ret;
	for(int i = 0; i < argc; ++i){
		ret.push_back(argv[i]);
	}
	return ret;
}

int main(int argc, char **argv){
	enum class Mode{
		Help,
		Title,
		Echo,
		Clear,
		New,
		Switch,
		Pointer,
		Modes,
		Reset
	};
	Mode mode = Mode::Help;
	string title;
	string cmd;
	uint64_t id = 0;
	bool on = false;
	bool info = false;
	bool speedMode = false;
	uint32_t speed = 0;
	
	auto helpCmd = (
		command("help", "--help").set(mode, Mode::Help) % "Display usage help"
	);
	auto titleCmd = (
		command("title").set(mode, Mode::Title) % "Set terminal title",
		value("new-title").set(title) % "New title text"
	);
	auto echoCmd = (
		command("echo").set(mode, Mode::Echo) % "Change character echo setting",
		command("on").set(on, true) | command("off").set(on, false)
	);
	auto clearCmd = (
		command("clear").set(mode, Mode::Clear) % "Clear the display"
	);
	auto newCmd = (
		command("new").set(mode, Mode::New) % "Create new terminal",
		opt_value("command").set(cmd) % "Command to run on new terminal (default: $SHELL$)"
	);
	auto switchCmd = (
		command("switch").set(mode, Mode::Switch) % "Switch to another terminal",
		value("term-id").set(id) % "ID of terminal to switch to"
	);
	auto pointerCmd = (
		command("pointer").set(mode, Mode::Pointer) % "Control the pointing cursor",
		command("on").set(on, true) | command("off").set(on, false) | command("info").set(info) | (
			command("speed").set(speedMode) % "Control pointer speed",
			command("get").set(on, true) | (command("set").set(on, false) & value("speed").set(speed))
		)
	);
	auto modesCmd = (
		command("modes").set(mode, Mode::Modes) % "List available display modes"
	);
	auto resetCmd = (
		command("reset").set(mode, Mode::Reset) % "Reset terminal to first text display mode"
	);
	
	auto cli = (helpCmd | titleCmd | echoCmd | clearCmd | newCmd | switchCmd | pointerCmd | modesCmd | resetCmd);
	
	if(parse(argc, argv, cli)){
		Terminal term;
		switch(mode){
			case Mode::Help:{
					auto fmt = doc_formatting{}.start_column(2).alternatives_min_split_size(1);
					cout << make_man_page(cli, argv[0], fmt);
				}
				break;
			case Mode::Title:
				term.SetTitle(title);
				break;
			case Mode::Echo:
				term.SetEcho(on);
				break;
			case Mode::Clear:
				term.ClearScreen();
				break;
			case Mode::New:{
					char runpath[BT_MAX_PATH]="";
					if(cmd.empty()){
						bt_getenv("SHELL", runpath, BT_MAX_PATH);
					}else{
						btos_path_parse(cmd.c_str(), runpath, BT_MAX_PATH);
					}
					term.New(runpath);
				}
				break;
			case Mode::Switch:
				term.Switch(id);
				break;
			case Mode::Pointer:
				if(speedMode){
					if(on){
						uint32_t speed = term.GetPointerSpeed();
    					printf("Pointer speed: %i\n", speed);
					}else{
						term.SetPointerSpeed(speed);
					}
				}else if(info){
					bt_terminal_pointer_info info = term.GetPointerInfo();
        			printf("Pointer: (%i, %i) Flags: %x\n", info.x, info.y, info.flags);
				}else{
					term.SetPointerVisibility(on);
				}
				break;
			case Mode::Modes:{
					size_t i = 0;
			        for(auto mode : term.GetScreenModes()){
			            printf("Mode %i: ID: %i %ix%i %ibpp %s.\n", (int)i, mode.id, mode.width, mode.height, mode.bpp, mode.textmode?"text":"graphics");
						++i;
			        }
			        bt_vidmode cmode = term.GetCurrentScreenMode();
			        printf("Current mode: ID: %i %ix%i %ibpp %s.\n", cmode.id, cmode.width, cmode.height, cmode.bpp, cmode.textmode?"text":"graphics");
				}
				break;
			case Mode::Reset:
				for(auto mode : term.GetScreenModes()) {
					if(mode.textmode){
						term.SetScreenMode(mode);
						break;
					}
					term.SetScrolling(true);
				}
				break;
		}
	}else{
		cerr << usage_lines(cli, argv[0]) << endl;
	}
	return 0;
}
