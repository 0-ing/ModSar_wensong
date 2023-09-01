#ifndef _SUGAR_SKELETON_RUNTIME_H
#define _SUGAR_SKELETON_RUNTIME_H
#include "sugar/com/common.h"
namespace sugar
{
    namespace skeleton
    {
        /***
         * sugar 启动服务 并且构建skeleton 端的vsomeip 启动 
         */
        bool init();
        void destroy();
    } // namespace skeleton

} // namespace sugar

#endif // _SUGAR_SKELETON_RUNTIME_H
