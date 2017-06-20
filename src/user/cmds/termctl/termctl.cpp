#include <btos.h>
#include <crt_support.h>
#include <dev/terminal.h>
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
    
    bt_filehandle fh=btos_get_handle(fileno(stdout));
    if(!fh) return -1;
    
    if(cmd == "title" && args.size() == 3) {
        bt_fioctl(fh, bt_terminal_ioctl::SetTitle, args[2].length(), (char*)args[2].c_str());
        return 0;
    }
    
    if(cmd == "echo" && args.size() == 3) {
        if(args[2] == "on") {
            bool val = true;
            bt_fioctl(fh, bt_terminal_ioctl::SetEcho, 1, (char*)&val);
        }else if(args[2] == "off"){
            bool val = false;
            bt_fioctl(fh, bt_terminal_ioctl::SetEcho, 1, (char*)&val);
        }else return 1;
        return 0;
    }
    
    if(cmd == "clear") {
        bt_fioctl(fh, bt_terminal_ioctl::ClearScreen, 0, NULL);
        return 0;
    }
    
    if(cmd == "new"){
        char runpath[BT_MAX_PATH]="";
        if(argc < 3){
            bt_getenv("SHELL", runpath, BT_MAX_PATH);
        }else{
            btos_path_parse(argv[2], runpath, BT_MAX_PATH);
        }
        bt_fioctl(fh, bt_terminal_ioctl::NewTerminal, BT_MAX_PATH, runpath);
        return 0;
    }
    if(cmd == "switch" && args.size() == 3){
        uint64_t id = strtoull(args[2].c_str(), NULL, 0);
        bt_fioctl(fh, bt_terminal_ioctl::SwtichTerminal, sizeof(id), (char*)&id);
        return 0;
    }
    
    if(cmd == "pointer" && args.size() == 3){
        if(args[2] == "on"){
            bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
        }else if(args[2] == "off"){
            bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
        }else return 1;
        return 0;
    }
    
    if(cmd == "pointer" && args.size() == 2){
        bt_terminal_pointer_info info;
        bt_fioctl(fh, bt_terminal_ioctl::GetPointerInfo, sizeof(info), (char*)&info);
        printf("Pointer: (%i, %i) Flags: %x\n", info.x, info.y, info.flags);
        return 0;
    }
    
    if(cmd == "modes"){
        size_t modecount = bt_fioctl(fh, bt_terminal_ioctl::GetScreenModeCount, 0, NULL);
        for(size_t i=0; i<modecount; ++i){
            bt_vidmode mode;
            mode.id=i;
            bt_fioctl(fh, bt_terminal_ioctl::GetScreenMode, sizeof(mode), (char*)&mode);
            printf("Mode %i: ID: %i %ix%i %ibpp %s.\n", (int)i, mode.id, mode.width, mode.height, mode.bpp, mode.textmode?"text":"graphics");
        }
        bt_vidmode cmode;
        bt_fioctl(fh, bt_terminal_ioctl::QueryScreenMode, sizeof(cmode), (char*)&cmode);
        printf("Current mode: ID: %i %ix%i %ibpp %s.\n", cmode.id, cmode.width, cmode.height, cmode.bpp, cmode.textmode?"text":"graphics");
        return 0;
    }
    
    if(cmd == "reset"){
        size_t modecount= bt_fioctl(fh, bt_terminal_ioctl::GetScreenModeCount, 0, NULL);
        for(size_t i=0; i<modecount; ++i) {
            bt_vidmode mode;
            mode.id=i;
            bt_fioctl(fh, bt_terminal_ioctl::GetScreenMode, sizeof(mode), (char*)&mode);
            if(mode.textmode){
                bt_fioctl(fh, bt_terminal_ioctl::SetScreenMode, sizeof(mode), (char*)&mode);
                break;
            }
            bool scroll = true;
            bt_fioctl(fh, bt_terminal_ioctl::SetScrolling, sizeof(scroll), (char*)&scroll);
        }
        return 0;
    }
    
    if(cmd == "pointer_speed" && args.size() >= 3){
    	if(args[2] == "get"){
    		uint32_t speed;
    		bt_fioctl(fh, bt_terminal_ioctl::GetPointerSpeed, sizeof(speed), (char*)&speed);
    		printf("Pointer speed: %i\n", speed);
    	}
    	if(args[2] == "set" && args.size() == 4){
    		uint32_t speed = strtoul(args[3].c_str(), NULL, 0);
    		bt_fioctl(fh, bt_terminal_ioctl::SetPointerSpeed, sizeof(speed), (char*)&speed);
    	}else return 1;
    	return 0;
    }
        
    printf("Unknown option '%s'\n", cmd.c_str());
    return 1;
}
