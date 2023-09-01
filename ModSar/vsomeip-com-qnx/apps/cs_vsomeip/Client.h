#ifndef NATIVETEST_CLIENT_H
#define NATIVETEST_CLIENT_H
#include <unistd.h>
#include "Common.h"

class Client {
public:
    Client() : rtm_(vsomeip::runtime::get()),
               app_(rtm_->create_application("Client")){
    }
    ~Client() = default;
    void ready();
    void start();
    void callMethod(uint8_t value);
    void callSetField(uint8_t field);
    void callGetField();
protected:
    void stateHandler(vsomeip::state_type_e state);
    void availableHandler(vsomeip::service_t service_, vsomeip::instance_t instance_, bool isAvailable);
    void messageHandler(const std::shared_ptr<vsomeip::message>& message_);
private:
    std::shared_ptr<vsomeip::runtime> rtm_;
    std::shared_ptr<vsomeip::application> app_;
};
#endif //NATIVETEST_CLIENT_H


