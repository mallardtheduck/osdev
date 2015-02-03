
#ifndef _BT_MSG_H
#define _BT_MSG_H

#include "bt_enum.h"

#ifdef __cplusplus
namespace btos_api{
#endif

#ifndef __cplusplus
#define BT_MSG_MAX (1024*4069)
#else
const size_t BT_MSG_MAX=4096*1024;
#endif

struct bt_msg_header{
    bool valid;
    uint64_t id;
    uint64_t reply_id;
    uint32_t flags;
    uint16_t source;
    uint64_t from, to;
    uint32_t type;
    size_t length;
    bool critical, recieved, replied;
    void *content;
};
#ifndef __cplusplus
typedef struct bt_msg_header bt_msg_header;
#endif

ENUM_START(bt_msg_flags)
    ENUM_SET(bt_msg_flags, UserSpace, 1 >> 0),
    ENUM_SET(bt_msg_flags, Reply, 1 << 1),
ENUM_END
ENUM_TYPE(bt_msg_flags);

ENUM_START(bt_kernel_messages)
	ENUM_SET(bt_kernel_messages, ProcessStart, 1),
	ENUM_SET(bt_kernel_messages, ProcessEnd, 2),
ENUM_END
ENUM_TYPE(bt_kernel_messages);

#ifdef __cplusplus
}
#endif

#endif