#ifndef _CORE_H
#define _CORE_H

#include <btos.h>

#ifdef __cplusplus
namespace btos_api{
#endif

EXTERN_C bt_threadhandle btos_create_thread(void (*entry)(void*), void *param, size_t stack_size);

#ifdef __cplusplus
}
#endif

#endif