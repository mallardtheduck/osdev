#include <gui/actionmanager.hpp>

namespace btos_api{
namespace gui{

void ActionManager::Add(const std::string &key, const std::string &text, std::shared_ptr<gds::Surface> icon, std::function<void()> function){
	Action act;
	act.text = text;
	act.icon = icon;
	act.function = function;
	act.id = ++id_counter;
	
	Add(key, act);
}

void ActionManager::Add(const std::string &key, const std::string &text, std::function<void()> function){
	Add(key, text, nullptr, function);
}

void ActionManager::Add(const std::string &key, const Action &action){
	actions[key] = action;
}

const ActionManager::Action &ActionManager::Get(const std::string &key){
	return actions[key];
}

std::shared_ptr<ToolbarButton> ActionManager::GetToolbarButton(const std::string &key, bool icon, bool text){
	auto act = Get(key);
	auto ret = std::make_shared<gui::ToolbarButton>(icon ? act.icon : nullptr, text ? act.text : "");
	ret->OnAction(act.function);
	return ret;
}

std::shared_ptr<Button> ActionManager::GetButton(const std::string &key, gds::Rect rect){
	auto act = Get(key);
	auto ret = std::make_shared<Button>(rect, act.text);
	ret->OnAction(act.function);
	return ret;
}

std::shared_ptr<ImageButton> ActionManager::GetImageButton(const std::string &key, gds::Rect rect){
	auto act = Get(key);
	auto ret = std::make_shared<ImageButton>(rect, act.icon);
	ret->OnAction(act.function);
	return ret;
}

wm::MenuItem ActionManager::GetMenuItem(const std::string &key, bool icon){
	auto act = Get(key);
	return wm::MenuItem(act.id, act.text, wm_MenuItemFlags::Default, icon ? act.icon.get() : nullptr);
}

void ActionManager::MenuHandler(uint32_t id){
	for(const auto &act : actions){
		if(act.second.id == id){
			if(act.second.function) act.second.function();
			break;
		}
	}
}

}
}