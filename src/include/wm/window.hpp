#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <gds/surface.hpp>
#include <wm/wm.h>
#include <string>

#include "menu.hpp"

namespace btos_api{
namespace wm{

	class Window{
	private:
		uint64_t id;
		bool owned;

		Window(const Window&) = delete;
		Window operator=(const Window&) = delete;
		Window() {}
	public:
		Window(const gds::Point &p, uint32_t options, uint32_t subscriptions, const gds::Surface &surf, const std::string &title);
		Window(const wm_WindowInfo &info);

		Window(Window &&w);

		~Window();

		static Window Wrap(uint64_t id, bool own);

		void Select() const;
		uint64_t GetID() const;

		wm_WindowInfo Info() const;
		void SetSubscribed(uint32_t events);
		void Update();
		void Update(const gds::Rect &r);
		void SetSurface(const gds::Surface &surf);
		gds::Surface GetSurface() const;
		void SetPosition(const gds::Point &p);
		gds::Point GetPosition() const;
		void SetOptions(uint32_t options);
		uint32_t GetOptions() const;
		void SetTitle(const std::string &title);
		std::string GetTitle() const;

		void SetMenu(const Menu &m);
		void ResetMenu();

		void ShowMenu(const Menu &m, const gds::Point &p);
	};

}
}

#endif
