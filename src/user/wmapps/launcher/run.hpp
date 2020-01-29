#ifndef _RUN_HPP
#define _RUN_HPP

#include <gui/idialog.hpp>

class Run : public btos_api::gui::IDialog<void>{
public:
    void Show(btos_api::wm::Window *parent) override;
private:
};

#endif