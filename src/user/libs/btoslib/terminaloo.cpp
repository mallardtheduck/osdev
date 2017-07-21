#include <dev/terminal.hpp>
#include <crt_support.h>
#include <cstdio>

namespace btos_api{

	Terminal::Terminal() : File(btos_get_handle(fileno(stdout))) {}

	Terminal::Terminal(bt_handle_t h) : File(h) {}

	void Terminal::SetMode(bt_terminal_mode::Enum mode){
		IOCtl(bt_terminal_ioctl::SetTerminalMode, sizeof(mode), (char*)&mode);
	}
	
	bt_terminal_mode::Enum Terminal::GetMode(){
		bt_terminal_mode::Enum ret;
		IOCtl(bt_terminal_ioctl::GetTerminalMode, sizeof(ret), (char*)&ret);
		return ret;
	}

	void Terminal::SetInfoLine(bool state){
		IOCtl(bt_terminal_ioctl::SetInfoLine, sizeof(state), (char*)&state);
	}

	bool Terminal::GetInfoLine(){
		bool ret;
		IOCtl(bt_terminal_ioctl::GetInfoLine, sizeof(ret), (char*)&ret);
		return ret;
	}

	void Terminal::SetTitle(const std::string &str){
		IOCtl(bt_terminal_ioctl::SetTitle, str.length() + 1, (char*)str.c_str());
	}
	std::string Terminal::GetTitle(){
		size_t size = 128;
		char *buf = new char[size];
		IOCtl(bt_terminal_ioctl::GetTitle, size, (char*)buf);
		std::string ret = buf;
		delete buf;
		return ret;
	}

	void Terminal::SetEcho(bool state){
		IOCtl(bt_terminal_ioctl::SetEcho, sizeof(state), (char*)&state);
	}
	bool Terminal::GetEcho(){
		bool ret;
		IOCtl(bt_terminal_ioctl::GetEcho, sizeof(ret), (char*)&ret);
		return ret;
	}

	void Terminal::SetPointerVisibility(bool mode){
		if(mode){
			IOCtl(bt_terminal_ioctl::ShowPointer, 0, NULL);
		}else{
			IOCtl(bt_terminal_ioctl::HidePointer, 0, NULL);
		}
	}
	bool Terminal::GetPointerVisibility(){
		bool ret;
		IOCtl(bt_terminal_ioctl::GetPointerVisibility, sizeof(ret), (char*)&ret);
		return ret;
	}

	void Terminal::SetPointerBitmap(bt_terminal_pointer_bitmap *bitmap){
		size_t size = sizeof(bt_terminal_pointer_bitmap) + bitmap->datasize;
		IOCtl(bt_terminal_ioctl::SetPointerBitmap, size, (char*)bitmap);
	}
	bt_terminal_pointer_info Terminal::GetPointerInfo(){
		bt_terminal_pointer_info ret;
		IOCtl(bt_terminal_ioctl::GetPointerInfo, sizeof(ret), (char*)&ret);
		return ret;
	}

	void Terminal::StartEventMode(){
		IOCtl(bt_terminal_ioctl::StartEventMode, 0, NULL);
	}
	void Terminal::EndEventMode(){
		IOCtl(bt_terminal_ioctl::EndEventMode, 0, NULL);
	}
	void Terminal::SetEventMode(bt_terminal_event_mode::Enum mode){
		IOCtl(bt_terminal_ioctl::SetEventMode, sizeof(mode), (char*)&mode);
	}

	void Terminal::SetPointerAutohide(bool state){
		IOCtl(bt_terminal_ioctl::PointerAutoHide, sizeof(state), (char*)&state);
	}

	void Terminal::PointerFreeze(){
		IOCtl(bt_terminal_ioctl::PointerFreeze, 0, NULL);
	}
	void Terminal::PointerUnfreeze(){
		IOCtl(bt_terminal_ioctl::PointerUnfreeze, 0, NULL);
	}

	void Terminal::SetPointerSpeed(uint32_t speed){
		IOCtl(bt_terminal_ioctl::SetPointerSpeed, sizeof(speed), (char*)&speed);
	}

	uint32_t Terminal::GetPointerSpeed(){
		uint32_t ret;
		IOCtl(bt_terminal_ioctl::GetPointerSpeed, sizeof(ret), (char*)&ret);
		return ret;
	}

	void Terminal::New(std::string command){
		IOCtl(bt_terminal_ioctl::NewTerminal, command.length() + 1, (char*)command.c_str());
	}
	void Terminal::Switch(uint64_t id){
		IOCtl(bt_terminal_ioctl::SwitchTerminal, sizeof(id), (char*)&id);
	}
	void Terminal::RegisterGlobalShortcut(uint16_t keycode){
		IOCtl(bt_terminal_ioctl::RegisterGlobalShortcut, sizeof(keycode), (char*)&keycode);
	}

	void Terminal::ClearScreen(){
		IOCtl(bt_terminal_ioctl::ClearScreen, 0, NULL);
	}

	void Terminal::ScreenModes::iterator::operator++(){
		mode.id = index;
		term->IOCtl(bt_terminal_ioctl::GetScreenMode, sizeof(mode), (char*)&mode);
		++index;
	}
	bt_vidmode Terminal::ScreenModes::iterator::operator*(){
		return mode;
	}

	bool Terminal::ScreenModes::iterator::operator==(const iterator &i){
		return index == i.index;
	}
	bool Terminal::ScreenModes::iterator::operator!=(const iterator &i){
		return !(*this == i);
	}

	size_t Terminal::ScreenModes::count(){
		return term->IOCtl(bt_terminal_ioctl::GetScreenModeCount, 0, NULL);
	}

	Terminal::ScreenModes::iterator Terminal::ScreenModes::begin(){
		iterator ret;
		ret.term = term;
		++ret;
		return ret;
	}

	Terminal::ScreenModes::iterator Terminal::ScreenModes::end(){
		iterator ret;
		ret.term = term;
		ret.index = count();
		return ret;
	}

	bt_vidmode Terminal::ScreenModes::operator[](size_t id){
		bt_vidmode ret;
		ret.id = id;
		term->IOCtl(bt_terminal_ioctl::GetScreenMode, sizeof(ret), (char*)&ret);
		return ret;
	}

	Terminal::ScreenModes Terminal::GetScreenModes(){
		ScreenModes ret;
		ret.term = this;
		return ret;
	}

	void Terminal::SetScreenMode(const bt_vidmode &mode){
		IOCtl(bt_terminal_ioctl::SetScreenMode, sizeof(mode), (char*)&mode);
	}
	bt_vidmode Terminal::GetCurrentScreenMode(){
		bt_vidmode ret;
		IOCtl(bt_terminal_ioctl::QueryScreenMode, sizeof(ret), (char*)&ret);
		return ret;
	}

	void Terminal::ScreenPalette::iterator::operator++(){
		ent.index = index;
		term->IOCtl(bt_terminal_ioctl::GetPaletteEntry, sizeof(ent), (char*)&ent);
		++index;
	}
	bt_video_palette_entry Terminal::ScreenPalette::iterator::operator*(){
		return ent;
	}

	bool Terminal::ScreenPalette::iterator::operator==(const iterator &i){
		return index == i.index;
	}
	bool Terminal::ScreenPalette::iterator::operator!=(const iterator &i){
		return !(*this == i);
	}

	size_t Terminal::ScreenPalette::count(){
		bt_vidmode mode = term->GetCurrentScreenMode();
		return (1 << mode.bpp);
	}

	Terminal::ScreenPalette::iterator Terminal::ScreenPalette::begin(){
		iterator ret;
		ret.term = term;
		++ret;
		return ret;
	}

	Terminal::ScreenPalette::iterator Terminal::ScreenPalette::end(){
		iterator ret;
		ret.term = term;
		ret.index = count();
		return ret;
	}

	bt_video_palette_entry  Terminal::ScreenPalette::operator[](size_t idx){
		bt_video_palette_entry ret;
		ret.index = idx;
		term->IOCtl(bt_terminal_ioctl::GetPaletteEntry, sizeof(ret), (char*)&ret);
		return ret;
	}


	Terminal::ScreenPalette Terminal::GetPalette(){
		ScreenPalette ret;
		ret.term = this;
		return ret;
	}

	void Terminal::SetTextColours(uint8_t c){
		IOCtl(bt_terminal_ioctl::SetTextColours, sizeof(c), (char*)&c);
	}
	uint8_t Terminal::GetTextColours(){
		return (uint8_t)IOCtl(bt_terminal_ioctl::GetTextColours, 0, NULL);
	}

	void Terminal::SetScrolling(bool s){
		IOCtl(bt_terminal_ioctl::SetScrolling, sizeof(s), (char*)&s);
	}
	bool Terminal::GetScrolling(){
		return (bool)IOCtl(bt_terminal_ioctl::GetScrolling, 0, NULL);
	}

}
