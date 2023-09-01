#ifndef NATIVETEST_SERVER_H
#define NATIVETEST_SERVER_H
#include <unistd.h>
#include "thread"
#include "Common.h"
class Server {
public:
    Server() : rtm_(vsomeip::runtime::get()),
               app_(rtm_->create_application("Server")){
    }
    ~Server() = default;
    //初始化Server
    void ready();
    //启动Server
    void start();
    //运行时环境
    std::shared_ptr<vsomeip::runtime> rtm_;
    //服务端application
    std::shared_ptr<vsomeip::application> app_;

private:
    //属性值
    uint32_t field_;
    //application初始化状态回调
    void stateHandler(vsomeip::state_type_e state);
    //服务实例可用状态回调
    void availableHandler(vsomeip::service_t service_, vsomeip::instance_t instance_, bool isAvailable);
    //报文回调
    void messageHandler(const std::shared_ptr<vsomeip::message>& message_);
    //事件订阅状态回调
    bool subscriptionHandler(vsomeip::client_t, bool subscribed);
    //供客户端调用的方法
    void callMethod(int value);
};
#endif //NATIVETEST_SERVER_H


