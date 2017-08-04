#ifndef _TERMINAL_HPP
#define _TERMINAL_HPP

#include "terminal.h"
#include "video_dev.h"
#include <btos/file.hpp>
#include <string>

namespace btos_api{

	class Terminal : public File{
	private:
	public:
		Terminal();
		Terminal(bt_handle_t h);

		void SetMode(bt_terminal_mode::Enum mode);
		bt_terminal_mode::Enum GetMode();

		void SetInfoLine(bool mode);
		bool GetInfoLine();

		void SetTitle(const std::string &str);
		std::string GetTitle();

		void SetEcho(bool mode);
		bool GetEcho();

		void SetPointerVisibility(bool mode);
		bool GetPointerVisibility();

		void SetPointerBitmap(bt_terminal_pointer_bitmap *bitmap);
		bt_terminal_pointer_info GetPointerInfo();

		void StartEventMode();
		void EndEventMode();
		void SetEventMode(bt_terminal_event_mode::Enum mode);

		void SetPointerAutohide(bool mode);

		void PointerFreeze();
		void PointerUnfreeze();

		void SetPointerSpeed(uint32_t speed);
		uint32_t GetPointerSpeed();

		void New(std::string command);
		void Switch(uint64_t id);
		void RegisterGlobalShortcut(uint16_t keycode);

		void ClearScreen();

		class ScreenModes{
		private:
			friend class Terminal;
			Terminal *term;		
		public:
			class iterator{
			private:
				friend class ScreenModes;
				Terminal *term;
				bt_vidmode mode;
				size_t index = 0;
			public:
				void operator++();
				bt_vidmode operator*();

				bool operator==(const iterator &i);
				bool operator!=(const iterator &i);
			};

			size_t count();
			iterator begin();
			iterator end();

			bt_vidmode operator[](size_t i);
		};

		ScreenModes GetScreenModes();
		void SetScreenMode(const bt_vidmode &mode);
		bt_vidmode GetCurrentScreenMode();

		class ScreenPalette{
		private:
			friend class Terminal;
			Terminal *term;		
		public:
			class iterator{
			private:
				friend class ScreenPalette;
				Terminal *term;
				bt_video_palette_entry ent;
				size_t index = 0;
			public:
				void operator++();
				bt_video_palette_entry operator*();

				bool operator==(const iterator &i);
				bool operator!=(const iterator &i);
			};

			size_t count();
			iterator begin();
			iterator end();

			bt_video_palette_entry operator[](size_t i);
		};

		ScreenPalette GetPalette();

		void SetTextColours(uint8_t c);
		uint8_t GetTextColours();

		void SetScrolling(bool mode);
		bool GetScrolling();
		
		void WaitActive();
		
	};	

}

#endif
