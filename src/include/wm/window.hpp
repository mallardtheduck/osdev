#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <gds/surface.hpp>
#include <wm/wm.h>
#include <string>

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

		void Select();
		uint64_t GetID();

		wm_WindowInfo Info();
		void SetSubscribed(uint32_t events);
		void Update();
		void Update(const gds::Rect &r);
		void SetSurface(const gds::Surface &surf);
		gds::Surface GetSurface();
		void SetPosition(const gds::Point &p);
		gds::Point GetPosition();
		void SetOptions(uint32_t options);
		uint32_t GetOptions();
		void SetTitle(const std::string &title);
		std::string GetTitle();
		
	};

}
}

#endif
