#include <gui/inputbox.hpp>
#include <gui/defaults.hpp>
#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/image.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>

#include <wm/eventloop.hpp>

#include <util/tinyformat.hpp>

namespace btos_api{
namespace gui{

static const uint32_t margin = 10;
static const uint32_t buttonHeight = 30;
static const uint32_t textHeight = 20;

InputBox::InputBox() {}
InputBox::InputBox(const std::string &m, const std::string &t, const std::string &d, std::shared_ptr<gds::Surface> i) :
	message(m), title(t), defvalue(d), icon(i) {}
	
std::string InputBox::Show(wm::Window *parent){
	std::vector<std::string> buttons = {"OK", "Cancel"};
	std::unique_ptr<gds::Surface> tmpSurf {new gds::Surface(gds_SurfaceType::Vector, 1, 1)};
	
	if(!icon) icon = icons::GetInputBoxDefault();
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
	auto formHeight = std::max(messageMeasures.h, iconInfo.h) + (4 * margin) + buttonHeight + textHeight;
	
	auto form = std::make_shared<Form>(gds::Rect{0, 0, formWidth, formHeight}, FormOptions::ClosedFixed | wm_WindowOptions::NoHide, title);
	
	form->SetPosition(DialogPosition(parent, *form));
	if(parent) parent->SetModal(*form);
	
	auto contentHeight = formHeight - (buttonHeight + margin);
	int32_t imageX = margin;
	int32_t imageY = (contentHeight - iconInfo.h) / 2;
	int32_t labelX = iconInfo.w + (2 * margin);
	int32_t labelY = ((contentHeight - textHeight - margin - messageMeasures.h) / 2) - (messageMeasures.h / 3);
	uint32_t labelHeight = (messageMeasures.h * 1.5);
	int32_t textX = labelX;
	int32_t textY = ((contentHeight - textHeight - margin - messageMeasures.h) / 2) + labelHeight + margin;
	
	auto image = std::make_shared<Image>(gds::Rect{imageX, imageY, iconInfo.w, iconInfo.h}, icon);
	auto label = std::make_shared<Label>(gds::Rect{labelX, labelY, messageMeasures.w, labelHeight}, message);
	auto text = std::make_shared<TextBox>(gds::Rect{textX, textY, messageMeasures.w, textHeight}, defvalue);
	
	form->AddControls({image, label, text});
	
	int32_t buttonX = ((formWidth - buttonWidth) / 2) + (margin * 1.5);
	int32_t buttonY = contentHeight;
	
	auto loop = DialogEventLoop(parent);
	
	size_t buttonIdx = -1;
	for(size_t i = 0; i < buttons.size(); ++i){
		auto btnWidth = buttonLabelMeasures[i].w + (2 * margin);
		auto btn = std::make_shared<Button>(gds::Rect{buttonX, buttonY, btnWidth, buttonHeight}, buttons[i]);
		btn->OnAction([&buttonIdx, i, &form, &loop]{
			buttonIdx = i;
			form->Close();
			loop->RemoveWindow(form->GetID());
		});
		form->AddControl(btn);
		buttonX += btnWidth + margin;
	}
	
	form->Open();
	loop->RunModal(form);
	
	if(parent) parent->ClearModal();
	
	if(buttonIdx == 0) return text->GetValue();
	else return "";
}
	
void InputBox::SetMessage(const std::string &m){
	message = m;
}

void InputBox::SetTitle(const std::string &t){
	title = t;
}

void InputBox::SetIcon(std::shared_ptr<gds::Surface> i){
	icon = i;
}

}
}