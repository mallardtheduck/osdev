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

struct MessageBoxImpl{
	std::string message;
	std::string title;
	std::shared_ptr<gds::Surface> icon;
	std::vector<std::string> buttons;
};
PIMPL_IMPL(MessageBoxImpl);

MessageBox::MessageBox() : im(new MessageBoxImpl()) {}
MessageBox::MessageBox(const std::string &m, const std::string &t, std::shared_ptr<gds::Surface> i, std::vector<std::string> b) : im(new MessageBoxImpl()){
	im->message = m; im->title = t; im->icon = i; im->buttons = b;
}
	
size_t MessageBox::Show(wm::Window *parent){
	size_t ret = -1;
	std::unique_ptr<gds::Surface> tmpSurf {new gds::Surface(gds_SurfaceType::Vector, 1, 1)};
	
	if(!im->icon) im->icon = icons::GetMessageBoxDefault();
	auto iconInfo = im->icon->Info();
	
	auto messageMeasures = tmpSurf->MeasureText(im->message, fonts::GetLabelFont(), fonts::GetLabelTextSize());
	
	std::vector<gds::TextMeasurements> buttonLabelMeasures;
	for(auto &b : im->buttons){
		buttonLabelMeasures.push_back(tmpSurf->MeasureText(b, fonts::GetButtonFont(), fonts::GetButtonTextSize()));
	}
	
	auto messageWidth = (margin * 3) + messageMeasures.w + iconInfo.w;
	auto buttonWidth = margin * 2;
	for(auto &b : buttonLabelMeasures){
		buttonWidth += b.w + (margin * 3);
	}
	
	auto formWidth = std::max(messageWidth, buttonWidth);
	auto formHeight = std::max(messageMeasures.h, iconInfo.h) + (3 * margin) + buttonHeight;
	
	auto form = std::make_shared<Form>(gds::Rect{0, 0, formWidth, formHeight}, FormOptions::ClosedFixed | wm_WindowOptions::NoHide, im->title);
	
	form->SetPosition(DialogPosition(parent, *form));
	if(parent) parent->SetModal(*form);
	
	auto contentHeight = formHeight - (buttonHeight + margin);
	int32_t imageX = margin;
	int32_t imageY = (contentHeight - iconInfo.h) / 2;
	int32_t labelX = iconInfo.w + (2 * margin);
	int32_t labelY = ((contentHeight - messageMeasures.h) / 2) - (messageMeasures.h / 3);
	
	auto image = std::make_shared<Image>(gds::Rect{imageX, imageY, iconInfo.w, iconInfo.h}, im->icon);
	uint32_t labelHeight = (messageMeasures.h * 1.5);
	auto label = std::make_shared<Label>(gds::Rect{labelX, labelY, messageMeasures.w, labelHeight}, im->message);
	
	form->AddControls({image, label});
	
	int32_t buttonX = ((formWidth - buttonWidth) / 2) + (margin * 1.5);
	int32_t buttonY = contentHeight;
	
	auto loop = DialogEventLoop(parent);
	
	for(size_t i = 0; i < im->buttons.size(); ++i){
		auto btnWidth = buttonLabelMeasures[i].w + (2 * margin);
		auto btn = std::make_shared<Button>(gds::Rect{buttonX, buttonY, btnWidth, buttonHeight}, im->buttons[i]);
		btn->OnAction([&ret, i, &form, &loop]{
			ret = i;
			form->Close();
			loop->RemoveWindow(form->GetID());
		});
		form->AddControl(btn);
		buttonX += btnWidth + margin;
	}
	
	form->Open();
	loop->RunModal(form);
	
	if(parent) parent->ClearModal();
	return ret;
}
	
void MessageBox::SetMessage(const std::string &m){
	im->message = m;
}

void MessageBox::SetTitle(const std::string &t){
	im->title = t;
}

void MessageBox::SetIcon(std::shared_ptr<gds::Surface> i){
	im->icon = i;
}

void MessageBox::SetButons(std::vector<std::string> b){
	im->buttons = b;
}

}
}