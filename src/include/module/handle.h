#ifndef _HANDLE_H
#define _HANDLE_H

typedef void (*handle_close_fn)(void*);

typedef uint32_t bt_handle_t;

struct bt_handle_info {
    uint32_t type;
    bool open;
    void *value;
    handle_close_fn close;
};

#ifndef __cplusplus
typedef struct bt_handle_info bt_handle_info;
#endif

#endif