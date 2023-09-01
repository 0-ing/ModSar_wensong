#ifndef _SUGAR_PROXY_RUNTIME_H
#define _SUGAR_PROXY_RUNTIME_H
#include "sugar/com/common.h"
namespace sugar
{
    namespace proxy
    {
        /***
         * sugar 启动服务 并且构建proxy 端的vsomeip 启动 
         */
        bool init();
        void destroy();
    } // namespace proxy

} // namespace sugar

#endif // _SUGAR_PROXY_RUNTIME_H
