#ifndef _HOLDLOCK_HPP
#define _HOLDLOCK_HPP

#include "module_stubs.h"

class hold_lock{
private:
    lock *l;

public:
    hold_lock(lock *lck): l(lck) {
        take_lock(l);
    }

    ~hold_lock() {
        release_lock(l);
    }
};

#endif