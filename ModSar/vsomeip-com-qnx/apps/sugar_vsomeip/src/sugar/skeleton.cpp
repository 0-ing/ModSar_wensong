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
    class SugarSkeleton : public SugarVSomeipSkeleton
    {
    public:
        SugarSkeleton(std::promise<int> &promise, const sugar::InstanceIdentifier &ins) : SugarVSomeipSkeleton(promise, ins, NULL)
        {
        }
        void init()
        {
            // 设置相关回调
            onMessageCallback(std::bind(&SugarSkeleton::disptachMessage, this,
                                        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
            ready();
        }
        void disptachMessage(int method_type, sugar::com::IResponse *response, void *content, int size)
        {
            sugar::com::printbin("MySugarVSomeipSkeleton::disptachMessage", content, size);
            if (method_type == sugar::com::SOMEIP_METHOD)
            {
                methodManager.disptachMessageInSkeletonWithCallback(
                    method_type,
                    content,
                    size,
                    [&](void *content, int size)
                    { response->responseToProxy(method_type, content, size); });
            }
            else if (method_type == sugar::com::SOMEIP_GET_FIELD)
            {
                fieldManager.disptachMessageInSkeletonWithCallback(
                    sugar::com::BasicField::Type::GET,
                    content,
                    size,
                    [&](void *content, int size)
                    { response->responseToProxy(method_type, content, size); });
            }
            else if (method_type == sugar::com::SOMEIP_SET_FIELD)
            {
                fieldManager.disptachMessageInSkeletonWithCallback(
                    sugar::com::BasicField::Type::SET,
                    content,
                    size,
                    [&](void *content, int size)
                    { response->responseToProxy(method_type, content, size); }

                );
            }
        }
        void setStub(IStub *stub)
        {
            this->stub = stub;
        }
        sugar::com::IHandlerManager *getMethodManger()
        {
            return &methodManager;
        }
        sugar::com::IHandlerManager *getFieldManger()
        {
            return &fieldManager;
        }
     
  
        sugar::com::method::MethodManagerLogic methodManager;
        sugar::com::field::FieldManagerLogic fieldManager;
    };

    static void vsomeip_workthread(Skeleton *skeleton, const InstanceIdentifier &ins, std::promise<int> &promise)
    {
        IStub *stub = StubManager::instance().createStub();
        auto realSkeleton = (SugarSkeleton*)skeleton->getSkeleton();
        if (realSkeleton)
        {
            realSkeleton->setStub(stub);
            realSkeleton->init();
            realSkeleton->start();
        }
    }
    Skeleton::Skeleton(const sugar::InstanceIdentifier &instance_identifier) : instance_identifier(instance_identifier)
    {
        _skeleton = new SugarSkeleton(ready_promise, instance_identifier);
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
