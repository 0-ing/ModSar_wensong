#include "Client.h"

void Client::ready() {
    if(!app_->init()){
        LOGE("cannot init the application");
        return;
    }

    //注册初始化回调
    app_->register_state_handler(std::bind(&Client::stateHandler, this, std::placeholders::_1));
    //注册服务实例发现状态回调
    app_->register_availability_handler(SERVICE_ID, INSTANCE_ID, std::bind(&Client::availableHandler,
                                                                           this,
                                                                           std::placeholders::_1,
                                                                           std::placeholders::_2,
                                                                           std::placeholders::_3));
    //注册消息回调
    app_->register_message_handler(SERVICE_ID, INSTANCE_ID, vsomeip::ANY_METHOD, std::bind(&Client::messageHandler,
                                                                                           this,
                                                                                           std::placeholders::_1));
}

void Client::start() {
    if(app_){
        app_->start();
    }
}

void Client::stateHandler(vsomeip::state_type_e state) {
    LOGE("Client %s received state_type_e = %hhu",
         __func__ ,
         state);
    //初始化成功之后，请求服务
    if(state == vsomeip::state_type_e::ST_REGISTERED){
        app_->request_service(SERVICE_ID, INSTANCE_ID);
    }
}

void Client::availableHandler(vsomeip::service_t service_, vsomeip::instance_t instance_,
                              bool isAvailable) {
    LOGE("Client %s received service = %02X , instance = %02X, isAvailable = %d",
         __func__ ,
         service_ ,
         instance_,
         isAvailable);
    if(isAvailable){
        //请求事件
        std::set<vsomeip::eventgroup_t> group_1;
        group_1.insert(EVENT_GROUP_ID_1);
        app_->request_event(SERVICE_ID, INSTANCE_ID, EVENT_ID_FIELD_NOTIFY, group_1,
                            vsomeip::event_type_e::ET_EVENT,
                            vsomeip::reliability_type_e::RT_UNRELIABLE);
        app_->request_event(SERVICE_ID, INSTANCE_ID, EVENT_ID_ONLY_NOTIFY_0, group_1,
                            vsomeip::event_type_e::ET_EVENT,
                            vsomeip::reliability_type_e::RT_UNRELIABLE);
        //订阅事件
        app_->subscribe(SERVICE_ID, INSTANCE_ID, EVENT_GROUP_ID_1);
    }
}

void Client::messageHandler(const std::shared_ptr<vsomeip::message> &message_) {
    if(message_){
        LOGE("Client %s received service = %02X , instance = %02X, type = %hhu",
             __func__ ,
             message_->get_service(),
             message_->get_instance(),
             message_->get_message_type());

        switch(message_->get_method()){
            case METHOD_ID_FIELD_GET:{
                LOGE("Client get field: %d", message_->get_payload()->get_data()[0]);
            }break;

            case METHOD_ID_FIELD_SET:{
                bool isOk = message_->get_return_code() == vsomeip::return_code_e::E_OK;
                LOGE("Client set field result: %d", isOk);
            }break;

            case EVENT_ID_FIELD_NOTIFY:{
                std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
                if(payload_){
                    LOGE("Client received field changed event, the field is %d", payload_->get_data()[0]);
                }
            }break;

            case EVENT_ID_ONLY_NOTIFY_0:{
                std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
                if(payload_){
                    uint16_t size = payload_->get_length();
                    vsomeip::byte_t* data = payload_->get_data();
                    LOGE("Client received event, payload is: ");
                    for(int i=0; i< size; i++){
                        LOGE("%02X", data[i]);
                    }
                }
            }break;
        }
    }
}

//调用服务端的方法
void Client::callMethod(uint8_t value) {
    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(SERVICE_ID);
    msg_->set_instance(INSTANCE_ID);
    msg_->set_method(METHOD_ID_FUNC_CALL);
    msg_->set_message_type(vsomeip::message_type_e::MT_REQUEST_NO_RETURN);
    vsomeip::byte_t* data_ = new vsomeip::byte_t[1];
    data_[0] = value;
    std::shared_ptr<vsomeip::payload> method_ = rtm_->create_payload(data_, 1);
    msg_->set_payload(method_);
    app_->send(msg_);
    delete[] data_;
}

//调用服务端的setField方法
void Client::callSetField(uint8_t field) {
    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(SERVICE_ID);
    msg_->set_instance(INSTANCE_ID);
    msg_->set_method(METHOD_ID_FIELD_SET);
    vsomeip::byte_t* data_ = new vsomeip::byte_t[1];
    data_[0] = field;
    std::shared_ptr<vsomeip::payload> method_ = rtm_->create_payload(data_, 1);
    msg_->set_payload(method_);
    app_->send(msg_);
    delete[] data_;
}

//调用服务端属性Get方法
void Client::callGetField() {
    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(SERVICE_ID);
    msg_->set_instance(INSTANCE_ID);
    msg_->set_method(METHOD_ID_FIELD_GET);
    app_->send(msg_);
}


