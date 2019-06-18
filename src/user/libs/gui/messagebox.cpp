#include <gui/messagebox.hpp>
#include <gui/defaults.hpp>
#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/image.hpp>
#include <gui/label.hpp>

#include <wm/eventloop.hpp>

#include <util/tinyformat.hpp>

namespace btos_api{
namespace gui{

static const uint32_t margin = 10;
static const uint32_t buttonHeight = 30;

MessageBox::MessageBox() {}
MessageBox::MessageBox(const std::string &m, const std::string &t, std::shared_ptr<gds::Surface> i, std::vector<std::string> b):
	message(m), title(t), icon(i), buttons(b) {}
	
size_t MessageBox::Show(wm::Window *parent){
	size_t ret = -1;
	std::unique_ptr<gds::Surface> tmpSurf {new gds::Surface(gds_SurfaceType::Vector, 1, 1)};
	
	if(!icon) icon = icons::GetMessageBoxDefault();
	auto iconInfo = icon->Info();
	
	auto messageMeasures = tmpSurf->MeasureText(message, fonts::GetLabelFont(), fonts::GetLabelTextSize());
	
	std::vector<gds::TextMeasurements> buttonLabelMeasures;
	for(auto &b : buttons){
		buttonLabelMeasures.push_back(tmpSurf->MeasureText(b, fonts::GetButtonFont(), fonts::GetButtonTextSize()));
	}
	
	auto messageWidth = (margin * 3) + messageMeasures.w + iconInfo.w;
	auto buttonWidth = margin * 2;
	for(auto &b : buttonLabelMeasures){
		buttonWidth += b.w + (margin * 3);
	}
	
	auto formWidth = std::max(messageWidth, buttonWidth);
	auto formHeight = std::max(messageMeasures.h, iconInfo.h) + (3 * margin) + buttonHeight;
	
	auto form = std::make_shared<Form>(gds::Rect{0, 0, formWidth, formHeight}, FormOptions::ClosedFixed | wm_WindowOptions::NoHide, title);
	auto formInfo = form->Info();
	auto totalFormWidth = formWidth + formInfo.contentX;
	auto totalFormHeight = formHeight + formInfo.contentY;
	
	if(parent){
		auto pInfo = parent->Info();
		auto pContentInfo = gds::Surface::Wrap(pInfo.gds_id, false).Info();
		
		auto totalParentWidth = pContentInfo.w + pInfo.contentX;
		auto totalParentHeight = pContentInfo.h + pInfo.contentY;
		
		auto formOffsetX = (totalParentWidth - totalFormWidth) / 2;
		auto formOffsetY = (totalParentHeight - totalFormHeight) / 2;
		
		int32_t formX = pInfo.x + formOffsetX;
		int32_t formY = pInfo.y + formOffsetY;
		
		form->SetPosition({formX, formY});
		
		parent->SetModal(*form);
	}else{
		auto smode = form->GetScreenMode();
		int32_t formX = (smode.width - totalFormWidth) / 2;
		int32_t formY = (smode.height - totalFormHeight) / 2;
		form->SetPosition({formX, formY});
	}
	
	auto contentHeight = formHeight - (buttonHeight + margin);
	int32_t imageX = margin;
	int32_t imageY = (contentHeight - iconInfo.h) / 2;
	int32_t labelX = iconInfo.w + (2 * margin);
	int32_t labelY = ((contentHeight - messageMeasures.h) / 2) - (messageMeasures.h / 3);
	
	auto image = std::make_shared<Image>(gds::Rect{imageX, imageY, iconInfo.w, iconInfo.h}, icon);
	uint32_t labelHeight = (messageMeasures.h * 1.5);
	auto label = std::make_shared<Label>(gds::Rect{labelX, labelY, messageMeasures.w, labelHeight}, message);
	
	form->AddControls({image, label});
	
	int32_t buttonX = ((formWidth - buttonWidth) / 2) + (margin * 1.5);
	int32_t buttonY = contentHeight;
	
	wm::EventLoop loop;
	
	for(size_t i = 0; i < buttons.size(); ++i){
		auto btnWidth = buttonLabelMeasures[i].w + (2 * margin);
		auto btn = std::make_shared<Button>(gds::Rect{buttonX, buttonY, btnWidth, buttonHeight}, buttons[i]);
		btn->OnAction([&ret, i, &form, &loop]{
			ret = i;
			form->Close();
			loop.RemoveWindow(form->GetID());
		});
		form->AddControl(btn);
		buttonX += btnWidth + margin;
	}
	
	form->Open();
	loop.AddWindow(form);
	loop.RunLoop();
	
	if(parent) parent->ClearModal();
	return ret;
}
	
void MessageBox::SetMessage(const std::string &m){
	message = m;
}

void MessageBox::SetTitle(const std::string &t){
	title = t;
}

void MessageBox::SetIcon(std::shared_ptr<gds::Surface> i){
	icon = i;
}

void MessageBox::SetButons(std::vector<std::string> b){
	buttons = b;
}

}
}