#ifndef _ACTIONMANAGER_HPP
#define _ACTIONMANAGER_HPP

#include <map>
#include <functional>
#include <memory>
#include <string>

#include <gds/surface.hpp>

#include <gui/toolbar.hpp>
#include <gui/button.hpp>
#include <gui/imagebutton.hpp>
#include <wm/menu.hpp>

namespace btos_api{
namespace gui{

class ActionManager{
public:
	struct Action{
	public:
		std::string text;
		std::shared_ptr<gds::Surface> icon;
		std::function<void()> function;
		
	private:
		friend class ActionManager;
		uint32_t id;
	};

private:
	uint32_t id_counter = 0;
	std::map<std::string, Action> actions;
	
public:
	void Add(const std::string &key, const std::string &text, std::shared_ptr<gds::Surface> icon, std::function<void()> function);
	void Add(const std::string &key, const std::string &text, std::function<void()> function);
	void Add(const std::string &key, const Action &action);
	
	const Action &Get(const std::string &key);
	
	std::shared_ptr<ToolbarButton> GetToolbarButton(const std::string &key, bool icon = true, bool text = false);
	std::shared_ptr<Button> GetButton(const std::string &key, gds::Rect rect);
	std::shared_ptr<ImageButton> GetImageButton(const std::string &key, gds::Rect rect);
	wm::MenuItem GetMenuItem(const std::string &key, bool icon = true);
	
	void MenuHandler(uint32_t id);
};

}
}

#endif