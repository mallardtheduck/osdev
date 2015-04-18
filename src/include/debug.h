#ifndef _DEBUG_H
#define _DEBUG_H

#include "bt_enum.h"

ENUM_START(bt_debug_event)
	ENUM_SET(bt_debug_event, ProgramStart, 0),
	ENUM_SET(bt_debug_event, ProgramEnd, 1),
	ENUM_SET(bt_debug_event, Breakpoint, 2),
	ENUM_SET(bt_debug_event, Exception, 3),
	ENUM_SET(bt_debug_event, ThreadStart, 4),
	ENUM_SET(bt_debug_event, ThreadEnd, 5),
ENUM_END
ENUM_TYPE(bt_debug_event);

ENUM_START(bt_exception)
	ENUM_SET(bt_exception, NoError, 0),
	ENUM_SET(bt_exception, DivideByZero, 1),
	ENUM_SET(bt_exception, BoundsError, 2),
	ENUM_SET(bt_exception, InvalidOpCode, 3),
	ENUM_SET(bt_exception, SegmentFault, 4),
	ENUM_SET(bt_exception, ProtectionFault, 5),
	ENUM_SET(bt_exception, UnresolvedPageFault, 6),
ENUM_END
ENUM_TYPE(bt_exception);

struct bt_debug_event_msg{
	ENUM_NAME(bt_debug_event) event;
	ENUM_NAME(bt_exception) error;
	uint64_t pid;
	uint64_t thread;
};

#endif //_DEBUG_H
