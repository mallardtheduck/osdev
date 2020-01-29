#define BTOS_NO_USING
#include "run.hpp"

#include <btos.h>
#include <btos/envvars.hpp>
#include <btos/process.hpp>

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>
#include <gui/image.hpp>
#include <gui/messagebox.hpp>
#include <gui/shell/fileopendialog.hpp>
#include <gui/shell/utils.hpp>

#include <util/tinyformat.hpp>

namespace gui = btos_api::gui;
namespace wm = btos_api::wm;
namespace gds = btos_api::gds;
namespace sh = gui::shell;

extern std::shared_ptr<gds::Surface> LoadIcon(const char *path);

void Run::Show(wm::Window *parent){
    auto form = std::make_shared<gui::Form>(gds::Rect{0, 0, 350, 132}, gui::FormOptions::ClosedFixed | wm_WindowOptions::NoHide, "Run...");
    auto image = std::make_shared<gui::Image>(gds::Rect{10, 10, 32, 32}, LoadIcon("icons/run_32.png"));
    auto label = std::make_shared<gui::Label>(gds::Rect{52, 15, 200, 20}, "Select a file to open or run");
    auto text = std::make_shared<gui::TextBox>(gds::Rect{10, 52, 240, 30});
    auto browse = std::make_shared<gui::Button>(gds::Rect{260, 52, 80, 30}, "Browse...");
    auto cancel = std::make_shared<gui::Button>(gds::Rect{210, 92, 60, 30}, "Cancel");
    auto run = std::make_shared<gui::Button>(gds::Rect{280, 92, 60, 30}, "Run");

    auto loop = gui::DialogEventLoop(parent);

    cancel->OnAction([&]{
        form->Close();
        loop->RemoveWindow(form->GetID());
    });

    browse->OnAction([&]{
        sh::FileOpenDialog dlg("", sh::FileExtensionPredicate({".elx", ".cmd"}));
        text->SetText(dlg.Show(form.get()));
    });

    run->OnAction([&]{
        auto path = text->GetText();
        auto stat = btos_api::bt_stat(path.c_str());
        if(stat.type == FS_File){
            if(sh::FileExtensionPredicate(".cmd")(path)){
                auto drive = btos_api::GetEnv("SYSTEMDRIVE");
			    auto termPath = tfm::format("%s:/BTOS/BIN/TERMWIN.ELX", drive);
                auto cmdPath = tfm::format("%s:/BTOS/CMD/CMD.ELX", drive);
			    btos_api::Process::Spawn(termPath, {cmdPath, "-s", path});
            }else{
                sh::Launch(path);
            }
            form->Close();
            loop->RemoveWindow(form->GetID());
        }else{
            gui::MessageBox msg("File not found.", "Error", LoadIcon("icons/error_32.png"));
            msg.Show(form.get());
        }
    });

    form->AddControls({label, image, text, browse, cancel, run});
    form->SetPosition(gui::DialogPosition(parent, *form));
    form->Show();
    loop->RunModal(form);
}