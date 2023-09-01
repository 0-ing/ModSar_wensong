#include "sugar/proxy/vsomeip/proxy.hpp"

namespace sugar
{   
    BaiscProxy *CreateProxyWithProtocol(sugar::com::IProtocol *proto,const sugar::InstanceIdentifier &instance)
    {
        std::promise<int> ready_promise;
        std::future<int> ready = ready_promise.get_future();
        proxy::vsomeip::SugarProxy *proxy = new proxy::vsomeip::SugarProxy(instance, ready_promise);
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