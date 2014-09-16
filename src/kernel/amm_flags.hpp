#ifndef _AMM_FLAGS
#define _AMM_FLAGS

namespace amm_flags{
    enum Enum{
        Normal          = 0,
        Shared          = 1 << 1,
        Is_PageTable    = 1 << 2,
        File_Mapped     = 1 << 3,

        Do_Not_Use      = 1 << 9,
        Do_Not_Move     = 1 << 10,
        Do_Not_Swap     = 1 << 11,

        Kernel          = Do_Not_Move | Do_Not_Swap,
        User            = Normal,
        Guard_Page      = Do_Not_Use | Do_Not_Move | Do_Not_Swap,
        PageTable       = Is_PageTable | Do_Not_Move,
    };
}

#endif