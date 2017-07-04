#include <btos.h>
#include <dev/terminal.h>
#include <crt_support.h>
#include <stdio.h>
#include <string.h>
#include <dev/terminal_ioctl.h>

static bt_handle_t th = 0;

void bt_term_handle(bt_handle_t handle){
	th = handle;
}

void bt_term_stdout(){
	th = btos_get_handle(fileno(stdout));
}

void bt_term_SetTerminalMode(bt_terminal_mode mode){
	bt_fioctl(th, bt_terminal_ioctl_SetTerminalMode, sizeof(mode), (char*)&mode);
}

bt_terminal_mode bt_term_GetTerminalMode(){
	bt_terminal_mode ret;
	bt_fioctl(th, bt_terminal_ioctl_GetTerminalMode, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_SetInfoLine(bool state){
	bt_fioctl(th, bt_terminal_ioctl_SetInfoLine, sizeof(state), (char*)&state);
}

bool bt_term_GetInfoLine(){
	bool ret;
	bt_fioctl(th, bt_terminal_ioctl_GetInfoLine, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_SetTitle(const char *title){
	bt_fioctl(th, bt_terminal_ioctl_SetTitle, strlen(title) + 1, (char*)title);
}

size_t bt_term_GetTitle(char *title, size_t size){
	return bt_fioctl(th, bt_terminal_ioctl_GetTitle, size, (char*)title);
}

void bt_term_SetEcho(bool state){
	bt_fioctl(th, bt_terminal_ioctl_SetEcho, sizeof(state), (char*)&state);
}

bool bt_term_GetEcho(){
	bool ret;
	bt_fioctl(th, bt_terminal_ioctl_GetEcho, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_ShowPointer(){
	bt_fioctl(th, bt_terminal_ioctl_ShowPointer, 0, NULL);
}

void bt_term_HidePointer(){
	bt_fioctl(th, bt_terminal_ioctl_HidePointer, 0, NULL);
}

bool bt_term_GetPointerVisibility(){
	bool ret;
	bt_fioctl(th, bt_terminal_ioctl_GetPointerVisibility, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_SetPointerBitmap(bt_terminal_pointer_bitmap *bitmap){
	size_t size = sizeof(bt_terminal_pointer_bitmap) + bitmap->datasize;
	bt_fioctl(th, bt_terminal_ioctl_SetPointerBitmap, size, (char*)bitmap);
}

bt_terminal_pointer_info bt_term_GetPointerInfo(){
	bt_terminal_pointer_info ret;
	bt_fioctl(th, bt_terminal_ioctl_GetEcho, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_StartEventMode(){
	bt_fioctl(th, bt_terminal_ioctl_StartEventMode, 0, NULL);
}

void bt_term_EndEventMode(){
	bt_fioctl(th, bt_terminal_ioctl_EndEventMode, 0, NULL);
}

void bt_term_SetEventMode(bt_terminal_event_mode mode){
	bt_fioctl(th, bt_terminal_ioctl_SetEventMode, sizeof(mode), (char*)&mode);
}

void bt_term_PointerAutoHide(bool state){
	bt_fioctl(th, bt_terminal_ioctl_PointerAutoHide, sizeof(state), (char*)&state);
}

void bt_term_PointerFreeze(){
	bt_fioctl(th, bt_terminal_ioctl_PointerFreeze, 0, NULL);
}

void bt_term_PointerUnfreeze(){
	bt_fioctl(th, bt_terminal_ioctl_PointerUnfreeze, 0, NULL);
}

uint32_t bt_term_GetPointerSpeed(){
	uint32_t ret;
	bt_fioctl(th, bt_terminal_ioctl_GetPointerSpeed, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_SetPointerSpeed(uint32_t speed){
	bt_fioctl(th, bt_terminal_ioctl_SetPointerSpeed, sizeof(speed), (char*)&speed);
}

void bt_term_NewTerminal(const char *cmd){
	bt_fioctl(th, bt_terminal_ioctl_NewTerminal, strlen(cmd) + 1, (char*)cmd);
}

void bt_term_SwitchTerminal(uint64_t id){
	bt_fioctl(th, bt_terminal_ioctl_SwitchTerminal, sizeof(id), (char*)&id);
}

void bt_term_RegisterGlobalShortcut(uint16_t keycode){
	bt_fioctl(th, bt_terminal_ioctl_RegisterGlobalShortcut, sizeof(keycode), (char*)&keycode);
}

void bt_term_ClearScreen(){
	bt_fioctl(th, bt_terminal_ioctl_ClearScreen, 0, NULL);
}

size_t bt_term_GetScreenModeCount(){
	return bt_fioctl(th, bt_terminal_ioctl_GetScreenModeCount, 0, NULL);
}

bt_vidmode bt_term_GetScreenMode(size_t id){
	bt_vidmode ret;
	ret.id = id;
	bt_fioctl(th, bt_terminal_ioctl_GetScreenMode, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_SetScreenMode(bt_vidmode mode){
	bt_fioctl(th, bt_terminal_ioctl_SetScreenMode, sizeof(mode), (char*)&mode);
}

bt_vidmode bt_term_QueryScreenMode(){
	bt_vidmode ret;
	bt_fioctl(th, bt_terminal_ioctl_QueryScreenMode, sizeof(ret), (char*)&ret);
	return ret;
}

bt_video_palette_entry bt_term_GetPaletteEntry(size_t idx){
	bt_video_palette_entry ret;
	ret.index = idx;
	bt_fioctl(th, bt_terminal_ioctl_GetPaletteEntry, sizeof(ret), (char*)&ret);
	return ret;
}

void bt_term_SetTextColours(uint8_t c){
	bt_fioctl(th, bt_terminal_ioctl_SetTextColours, sizeof(c), (char*)&c);
}

uint8_t bt_term_GetTextColours(){
	return (uint8_t)bt_fioctl(th, bt_terminal_ioctl_GetTextColours, 0, NULL);
}

bool bt_term_GetScrolling(){
	return (bool)bt_fioctl(th, bt_terminal_ioctl_GetScrolling, 0, NULL);
}

void bt_term_SetScrolling(bool s){
	bt_fioctl(th, bt_terminal_ioctl_SetScrolling, sizeof(s), (char*)&s);
}

