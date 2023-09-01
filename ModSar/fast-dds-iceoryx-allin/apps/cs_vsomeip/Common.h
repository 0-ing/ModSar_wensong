#ifndef _COMMON_H
#define _COMMON_H

#include <vsomeip/vsomeip.hpp>
#include <memory>

#define SERVICE_ID  0x0001  //服务ID
#define INSTANCE_ID 0x0001  //服务实例ID
#include <stdarg.h>
#define METHOD_ID_FIELD_SET   0x1000   //属性SET方法ID
#define METHOD_ID_FIELD_GET   0x1001   //属性GET方法ID
#define EVENT_ID_FIELD_NOTIFY 0x2000   //属性事件ID

#define METHOD_ID_FUNC_CALL    0x1002  //客户端调用服务端方法ID
#define EVENT_ID_ONLY_NOTIFY_0 0x2001  //服务端事件0
#define EVENT_GROUP_ID_1  0x0001 //事件组1

int println(const char *fmt, ...);

#define LOGE println

#endif // _COMMON_H
