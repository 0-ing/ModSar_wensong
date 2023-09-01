#ifndef NATIVETEST_CLIENT_H
#define NATIVETEST_CLIENT_H
#include <unistd.h>
#include "sugar/proxy.h"
#include "SugarVSomeipDefs.h"
#include "sugar/instance_identifier.h"
#include "mts/MTSLogic.h"

class SugarVSomeipProxy : public sugar::BaiscProxy
{
public:
    SugarVSomeipProxy(std::promise<int> &promise, IStub *stub) : rtm_(vsomeip::runtime::get()),
                                                                 promise(promise), stub(stub)
    {
    }
    SugarVSomeipProxy(std::promise<int> &promise, const sugar::InstanceIdentifier &ins, IStub *stub) : rtm_(vsomeip::runtime::get()),
                                                                                                       /*app_(rtm_->create_application(ins.getUniqueName())),*/ promise(promise), stub(stub)
    {
        app_ = rtm_->create_application(ins.getUniqueName());
        this->instance_identifier = ins;
    }
    ~SugarVSomeipProxy() = default;
    void ready();
    void start();
    void callMethod(uint8_t value);
    void callSetField(uint8_t field);
    void callGetField();

    void invokeToSkeleton(int type, void *content, int size);
    void invokeToSkeletonWithCallback(int type, void *content, int size, const std::function<void(void *, int)> &callback);

protected:
    void stateHandler(vsomeip::state_type_e state);
    void availableHandler(vsomeip::service_t service_, vsomeip::instance_t instance_, bool isAvailable);
    void messageHandler(const std::shared_ptr<vsomeip::message> &message_);
    void handleMessageCallback(int sessionid, int type, void *data, int size);

private:
    std::shared_ptr<vsomeip::runtime> rtm_;
    std::shared_ptr<vsomeip::application> app_;
    std::promise<int> &promise;

protected:
    IStub *stub = NULL;
    int sessionid = 0;
    std::mutex callbacks_mtx;
    std::mutex sessionid_mtx;
    std::map<int, std::function<void(void *, int)>> callbacks;
};
#endif // NATIVETEST_CLIENT_H
