#ifndef _HOLDLOCK_HPP
#define _HOLDLOCK_HPP

#include <btos_module.h>

class hold_lock{
private:
    lock *l;

public:
    hold_lock(lock *lck, bool exclusive=true): l(lck) {
        if(exclusive) take_lock(l);
        else take_lock_recursive(l);
    }

    ~hold_lock() {
        release_lock(l);
    }
};

#endif