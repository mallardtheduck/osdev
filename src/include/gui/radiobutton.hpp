#ifndef _RADIOBUTTON_HPP
#define _RADIOBUTTON_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{
	
class RadioButton : public IValueControl<bool> {
private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> bkSurf;
	
	bool value;
	gds::TextMeasurements textMeasures;
	bool focus = false;
	bool enabled = true;
	
	template<typename T> friend class RadioGroup;
	std::function<std::vector<gds::Rect>()> getAllRects;
	
	void SetValue(bool v);
public:
	RadioButton(const gds::Rect &r, const std::string &t, bool v);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	bool GetValue();
	void Enable();
	void Disable();
	bool IsEnabled();
	void SetPosition(const gds::Rect&);
	
	void SetText(const std::string &t);
};

template<typename T> class RadioGroup{
private:
	std::map<std::shared_ptr<RadioButton>, T> values;
	std::shared_ptr<RadioButton> current;
	
	std::function<void(T)> onChange;
public:
	T GetValue(){
		auto v = values.find(current);
		if(v != values.end()) return v->second;
		else{
			for(auto &p : values){
				if(p.first && p.first->GetValue()){
					current = p.first;
					return p.second;
				}
			}
			return {};
		}
	}
	
	void AddButton(std::shared_ptr<RadioButton> r, T v){
		values[r] = v;
		std::weak_ptr<RadioButton> w = r;
		r->OnChange([w, this](bool b) {
			if(w.expired()) return;
			auto r = w.lock();
			if(b && (r != current)){
				current = r;
				if(onChange) onChange(values[r]);
				for(auto &p : values){
					if(r != p.first){
						if(p.first) p.first->SetValue(false);
					}
				}       
			}
		});
		r->getAllRects = [this](){
			std::vector<gds::Rect> ret;
			for(auto &p : values){
				if(p.first) ret.push_back(p.first->GetPaintRect());
			}
			return ret;
		};
	}
	
	void OnChange(const std::function<void(T)> &oC){
		onChange = oC;
	}
};

}
}

#endif
