#ifndef _HANDLE_H
#define _HANDLE_H

typedef void (*handle_close_fn)(void*);

struct bt_handle{
    uint32_t type;
    bool open;
    void *value;
    handle_close_fn close;
};

#ifndef __cplusplus
typedef struct bt_handle bt_handle;
#endif

#endif