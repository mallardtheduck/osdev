#ifndef _SM_H
#define _SM_H

#include <btos.h>
#ifdef __cplusplus
#include <string>
#endif

NS_BEGIN(btos_api)
NS_BEGIN(sm)

ENUM_START(sm_RequestType)
	ENUM_SET(sm_RequestType, GetService, 1),
	ENUM_SET(sm_RequestType, StartService, 2),
	ENUM_SET(sm_RequestType, StopService, 3),
	ENUM_SET(sm_RequestType, ForceStopService, 4),
ENUM_END
ENUM_TYPE(sm_RequestType);

EXTERN_C bt_pid_t SM_GetService(const char *name);
CPP_ONLY(bt_pid_t SM_GetService(const std::string &name);)

EXTERN_C bt_pid_t SM_StartService(const char *name);
CPP_ONLY(bt_pid_t SM_StartService(const std::string &name);)

EXTERN_C void SM_StopService(const char *name, bool force CPP_ONLY(=false));
CPP_ONLY(void SM_StopService(const std::string &name, bool force = false);)

NS_END
NS_END

#endif
