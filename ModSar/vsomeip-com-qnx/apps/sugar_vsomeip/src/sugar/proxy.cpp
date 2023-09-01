#include "sugar/proxy.h"
#include "sugar/com/common.h"
#include "sugar/runtime.h"
#include "sugar/com/any.h"
#include "sugar/com/event/logic.h"
#include "vsomeip-wrapper/sugar/SugarVSomeipProxy.h"
#include "sugar/instance_identifier.h"

namespace sugar
{

    class SugarProxy : public SugarVSomeipProxy
    {
    public:
        void init(IStub *stub)
        {
            
            // 设置相关回调
            onMessageCallback(std::bind(&SugarProxy::messageCallback, this,
                                        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            start();
            ready();
        }
        void messageCallback(int method_type, void *content, int size)
        {
            if (method_type == sugar::com::SOMEIP_EVENT_NOTIFY)
            {
                // 找到
                eventManager.dispatchOnChange(content, size);
            }
        }
        SugarProxy(const sugar::InstanceIdentifier &instance, std::promise<int> &promise) : SugarVSomeipProxy(promise, instance, NULL)
        {
        }
        bool FindService();

        sugar::com::IHandlerManager *getEventManger()
        {
            return &eventManager;
        }
   
        sugar::com::event::EventManagerLogic eventManager;
    };

    static void vsomeip_workthread(SugarProxy *proxy)
    {
        IStub *stub = StubManager::instance().createStub();

        if (proxy)
        {
            proxy->init(stub);
            proxy->start();
        }
    }

    bool SugarProxy::FindService()
    {
        // 启动一个线程去构建vsomeip的启动

        std::thread  t(vsomeip_workthread, this);
        t.detach();
        return true;
    }
    BaiscProxy *CreateProxyWithProtocol(sugar::com::IProtocol *proto,const sugar::InstanceIdentifier &instance)
    {
        std::promise<int> ready_promise;
        std::future<int> ready = ready_promise.get_future();
        SugarProxy *proxy = new SugarProxy(instance, ready_promise);
        if (proxy)
        {
            proto->proxy = proxy;
            proxy->FindService();
            printf("proxy ready to work\n");
            int result = ready.get();
            // 检查返回值查看具体的信息
           
        }
        return proxy;
    }

} // namespace sugar