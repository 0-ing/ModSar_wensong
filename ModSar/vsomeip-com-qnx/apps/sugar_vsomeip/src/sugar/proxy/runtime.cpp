#include "sugar/com/common.h"
#include "sugar/runtime.h"
#include "sugar/com/any.h"
#include "vsomeip-wrapper/sugar/SugarVSomeipProxy.h"
#include "sugar/com/method/logic.h"
#include "sugar/com/event/logic.h"
#include <signal.h>

namespace sugar
{
        namespace proxy
        {
            bool init()
            {
                StubManager::instance().init(5); // 最多4个stub
                // 检查返回值查看具体的信息
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`\n");
                return true;
            }

            void destroy()
            {
                StubManager::instance().wait();
            }

        } // namespace proxy

} // namespace sugar
