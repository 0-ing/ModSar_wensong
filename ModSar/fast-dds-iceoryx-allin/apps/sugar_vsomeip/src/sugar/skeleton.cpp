#include "sugar/skeleton/vsomeip/skeleton.hpp"

namespace sugar
{
    
    static void vsomeip_workthread(Skeleton *skeleton, const InstanceIdentifier &ins, std::promise<int> &promise)
    {
        IStub *stub = StubManager::instance().createStub();
        auto realSkeleton = (sugar::skeleton::vsomeip::SugarSkeleton*)skeleton->getSkeleton();
        if (realSkeleton)
        {
            realSkeleton->setStub(stub);
            realSkeleton->init();
            realSkeleton->start();
        }
    }
    Skeleton::Skeleton(const sugar::InstanceIdentifier &instance_identifier) : instance_identifier(instance_identifier)
    {
        _skeleton = new sugar::skeleton::vsomeip::SugarSkeleton(ready_promise, instance_identifier);
    }

    bool Skeleton::OfferService()
    {
        // 启动一个线程去构建vsomeip的启动
        
        std::future<int> ready = ready_promise.get_future();
        std::thread t(vsomeip_workthread, this, instance_identifier, std::ref(ready_promise));
        t.detach();
        // sugar::ThreadManager::getInstance().add("vsomeip_thread_skeleton", vsomeip);

        int result = ready.get();
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Skeleton::OfferService %d\n", result);
        // 检查返回值查看具体的信息
        return true;
    }

} // namespace sugar
