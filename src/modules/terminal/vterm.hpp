#ifndef _VTERM_HPP
#define _VTERM_CPP

#include "module_api.h"
#include "video_dev.h"

class vterm{
private:
    uint8_t *buffer;
    bt_vidmode mode;

    pid_t curpid;

public:
    void activate();
    void deactivate();
};

extern vterm current_vterm;

#endif