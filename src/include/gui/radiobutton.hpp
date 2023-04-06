#ifndef _RADIOBUTTON_HPP
#define _RADIOBUTTON_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct RadioButtonImpl;
PIMPL_CLASS(RadioButtonImpl);

class RadioButton : public IValueControl<bool> {
private:
	btos::pimpl_ptr<RadioButtonImpl> im;

	template<typename T> friend class RadioGroup;
	
	std::function<std::vector<gds::Rect>()> getAllRects;
	void SetValue(bool v);
public:
	RadioButton(const gds::Rect &r, const std::string &t, bool v);
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void Focus() override;
	void Blur() override;
	uint32_t GetFlags() override;
	bool GetValue() override;
	void Enable() override;
	void Disable() override;
	bool IsEnabled() override;
	void SetPosition(const gds::Rect&) override;
	
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
