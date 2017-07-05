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

using namespace std;

vector<string> args_to_vec(int argc, char **argv){
	vector<string> ret;
	for(int i = 0; i < argc; ++i){
		ret.push_back(argv[i]);
	}
	return ret;
}

int main(int argc, char **argv){
	
    if(argc < 2 && argv[1]){
        printf("BT/OS terminal utility.\n");
        printf("Usage: %s command [params...]\n", argv[0]);
        return 1;
    }
    
    vector<string> args = args_to_vec(argc, argv);
    string cmd = args[1];
    
    Terminal term;
    
    if(cmd == "title" && args.size() == 3) {
		term.SetTitle(args[2]);
        return 0;
    }
    
    if(cmd == "echo" && args.size() == 3) {
        if(args[2] == "on") {
			term.SetEcho(true);
        }else if(args[2] == "off"){
            term.SetEcho(false);
        }else return 1;
        return 0;
    }
    
    if(cmd == "clear") {
        term.ClearScreen();
        return 0;
    }
    
    if(cmd == "new"){
        char runpath[BT_MAX_PATH]="";
        if(argc < 3){
            bt_getenv("SHELL", runpath, BT_MAX_PATH);
        }else{
            btos_path_parse(argv[2], runpath, BT_MAX_PATH);
        }
		term.New(runpath);
        return 0;
    }
    if(cmd == "switch" && args.size() == 3){
        uint64_t id = strtoull(args[2].c_str(), NULL, 0);
		term.Switch(id);
        return 0;
    }
    
    if(cmd == "pointer" && args.size() == 3){
        if(args[2] == "on"){
            term.SetPointerVisibility(true);
        }else if(args[2] == "off"){
            term.SetPointerVisibility(false);
        }else return 1;
        return 0;
    }
    
    if(cmd == "pointer" && args.size() == 2){
        bt_terminal_pointer_info info = term.GetPointerInfo();
        printf("Pointer: (%i, %i) Flags: %x\n", info.x, info.y, info.flags);
        return 0;
    }
    
    if(cmd == "modes"){
		size_t i = 0;
        for(auto mode : term.GetScreenModes()){
            printf("Mode %i: ID: %i %ix%i %ibpp %s.\n", (int)i, mode.id, mode.width, mode.height, mode.bpp, mode.textmode?"text":"graphics");
			++i;
        }
        bt_vidmode cmode = term.GetCurrentScreenMode();
        printf("Current mode: ID: %i %ix%i %ibpp %s.\n", cmode.id, cmode.width, cmode.height, cmode.bpp, cmode.textmode?"text":"graphics");
        return 0;
    }
    
    if(cmd == "reset"){
        for(auto mode : term.GetScreenModes()) {
            if(mode.textmode){
				term.SetScreenMode(mode);
                break;
            }
			term.SetScrolling(true);
        }
        return 0;
    }
    
    if(cmd == "pointer_speed" && args.size() >= 3){
    	if(args[2] == "get"){
    		uint32_t speed = term.GetPointerSpeed();
    		printf("Pointer speed: %i\n", speed);
    	}
    	if(args[2] == "set" && args.size() == 4){
    		uint32_t speed = strtoul(args[3].c_str(), NULL, 0);
			term.SetPointerSpeed(speed);
    	}else return 1;
    	return 0;
    }
        
    printf("Unknown option '%s'\n", cmd.c_str());
    return 1;
}
