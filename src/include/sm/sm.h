#ifndef _SM_H
#define _SM_H

#include <btos.h>
#ifdef __cplusplus
#include <string>
#endif

NS_BEGIN(btos_api)
NS_BEGIN(sm)

struct sm_ServiceInfo{
	char name[BT_MAX_SEGLEN];
	bool running;
	int users;
	bt_pid_t pid;
};

ENUM_START(sm_RequestType)
	ENUM_SET(sm_RequestType, GetService, 1),
	ENUM_SET(sm_RequestType, StartService, 2),
	ENUM_SET(sm_RequestType, ReleaseService, 3),
	ENUM_SET(sm_RequestType, StopService, 4),
	ENUM_SET(sm_RequestType, GetServiceCount, 5),
	ENUM_SET(sm_RequestType, GetServiceInfo, 6),
ENUM_END
ENUM_TYPE(sm_RequestType);

ENUM_START(sm_ServiceRequest)
	ENUM_SET(sm_RequestType, StopService, 1),
ENUM_END
ENUM_TYPE(sm_ServiceRequest);

EXTERN_C void SM_SetServerPID(bt_pid_t pid);
EXTERN_C bt_pid_t SM_GetServerPID();

EXTERN_C bt_pid_t SM_GetService(const char *name);
CPP_ONLY(bt_pid_t SM_GetService(const std::string &name);)

EXTERN_C bt_pid_t SM_StartService(const char *name);
CPP_ONLY(bt_pid_t SM_StartService(const std::string &name);)

EXTERN_C void SM_ReleaseService(const char *name);
CPP_ONLY(void SM_ReleaseService(const std::string &name);)

EXTERN_C void SM_StopService(const char *name);
CPP_ONLY(void SM_StopService(const std::string &name);)

EXTERN_C size_t SM_GetServiceCount();
EXTERN_C sm_ServiceInfo SM_GetServiceInfo(size_t index);

NS_END
NS_END

#endif
