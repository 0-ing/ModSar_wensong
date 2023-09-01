#include "sugar/runtime.h"
#include "sugar/com/common.h"
#include "sugar/com/any.h"
#include "sugar/com/method/logic.h"
#include "sugar/com/field/logic.h"
#include "sugar/com/field.h"
#include "vsomeip-wrapper/sugar/SugarVSomeipSkeleton.h"
#include <signal.h>

namespace sugar
{
    namespace skeleton
    {
        bool init()
        {
            StubManager::instance().init(5); // 最多4个stub
            // 启动一个线程去构建vsomeip的启动
 
            return true;
        }

        void destroy()
        {
            StubManager::instance().wait();
            // sugar::ThreadManager::getInstance().waitAll();
        }

    } // namespace skeleton

} // namespace sugar
