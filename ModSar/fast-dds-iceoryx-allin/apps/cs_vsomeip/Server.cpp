//
// Created by Gaddi
//
#include "Server.h"

void Server::ready() {
    if(app_){
        if(!app_->init()){
            LOGE("cannot init the application");
            return;
        }
        //注册服务实例可用状态回调
        app_->register_availability_handler(SERVICE_ID, INSTANCE_ID, std::bind(&Server::availableHandler,
                                                                               this,
                                                                               std::placeholders::_1,
                                                                               std::placeholders::_2,
                                                                               std::placeholders::_3));

        //注册状态变化回调
        app_->register_state_handler(std::bind(&Server::stateHandler, this, std::placeholders::_1));

        //注册消息接收回调, 这里我们主要模拟三个属性的(SET,GET), 以及单纯的FUNC执行
        app_->register_message_handler(SERVICE_ID, INSTANCE_ID,  METHOD_ID_FIELD_GET,std::bind(&Server::messageHandler,
                                                                          this,
                                                                          std::placeholders::_1));
        app_->register_message_handler(SERVICE_ID, INSTANCE_ID,  METHOD_ID_FIELD_SET,std::bind(&Server::messageHandler,
                                                                                               this,
                                                                                               std::placeholders::_1));
        app_->register_message_handler(SERVICE_ID, INSTANCE_ID,  METHOD_ID_FUNC_CALL,std::bind(&Server::messageHandler,
                                                                                               this,
                                                                                               std::placeholders::_1));
        //注册客户端订阅事件组
        app_->register_subscription_handler(SERVICE_ID, INSTANCE_ID, EVENT_GROUP_ID_1, std::bind(&Server::subscriptionHandler,
                                                                                                 this,
                                                                                                 std::placeholders::_1,
                                                                                                 std::placeholders::_4));
        //注册事件
        std::set<vsomeip::eventgroup_t> group_set_1;
        group_set_1.insert(EVENT_GROUP_ID_1);

        app_->offer_event(SERVICE_ID, INSTANCE_ID, EVENT_ID_FIELD_NOTIFY, group_set_1,
                          vsomeip::event_type_e::ET_EVENT,
                          std::chrono::milliseconds::zero(),
                          false,
                          true,
                          nullptr,
                          vsomeip::reliability_type_e::RT_UNRELIABLE);
        app_->offer_event(SERVICE_ID, INSTANCE_ID, EVENT_ID_ONLY_NOTIFY_0, group_set_1,
                          vsomeip::event_type_e::ET_EVENT,
                          std::chrono::milliseconds::zero(),
                          false,
                          true,
                          nullptr,
                          vsomeip::reliability_type_e::RT_UNRELIABLE);
        LOGE("ready done for server");
    }
}

void Server::start() {
    if(app_){
        LOGE("start for server");
        app_->start();
        LOGE("start done for server");
    }
}

/**
 * 当客户端订阅成功后，服务端每隔5s触发通知
 * @param srv
 */
static void offerEventCycle(Server* srv){
    const int size = 5;
    uint16_t v = 0;
    while(true){
        vsomeip_v3::byte_t* data_ = new vsomeip_v3::byte_t(size);
        for(int i=0; i<size; i++){
            data_[i] = v + i;
        }
        v++;
        std::shared_ptr<vsomeip::payload> payload_ = srv->rtm_->create_payload();
        payload_->set_data(data_, size);
        srv->app_->notify(SERVICE_ID, INSTANCE_ID, EVENT_ID_ONLY_NOTIFY_0, payload_, true);
        delete data_;
        sleep(5);
        if(v == 10){
            break;
        }
    }
}

void Server::availableHandler(vsomeip::service_t service_, vsomeip::instance_t instance_,
                              bool isAvailable) {
    LOGE("%s received service = %02X , instance = %02X, isAvailable = %d",
         __func__ ,
         service_ ,
         instance_,
         isAvailable);
}

void Server::messageHandler(const std::shared_ptr<vsomeip::message> &message_) {
    if(message_){
        LOGE("Server %s received service = %02X , instance = %02X, type = %hhu",
             __func__ ,
             message_->get_service(),
             message_->get_instance(),
             message_->get_message_type());

        if(message_->get_service() == SERVICE_ID && message_->get_instance() == INSTANCE_ID){
            switch(message_->get_method()){
                case METHOD_ID_FUNC_CALL:{
                    std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
                    if(payload_){
                        int val = payload_->get_data()[0];
                        callMethod(val);
                    }
                }break;

                case METHOD_ID_FIELD_SET:{
                    //获取客户端传递过来的数据
                    std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
                    bool changed = false;
                    if(payload_){
                        uint32_t val = payload_->get_data()[0];
                        if(field_ != val){
                            field_ = val;
                            changed = true;
                        }
                        //设置属性后，回复OK
                        if(message_->get_message_type() == vsomeip::message_type_e::MT_REQUEST){
                            std::shared_ptr<vsomeip::message> response_ = rtm_->create_response(message_);
                            app_->send(response_);
                        }

                        if(changed){
                            std::shared_ptr<vsomeip::payload> p_ = rtm_->create_payload();
                            vsomeip::byte_t* data_ = new vsomeip::byte_t[1];
                            data_[0] = field_;
                            p_->set_data(data_, 1);
                            app_->notify(SERVICE_ID, INSTANCE_ID, EVENT_ID_FIELD_NOTIFY, p_);
                            delete[] data_;
                        }
                    }
                } break;

                case METHOD_ID_FIELD_GET:{
                    //回复属性值field给到请求的客户端
                    LOGE("The client call field get val");
                    std::shared_ptr<vsomeip::message> response_ = rtm_->create_response(message_);
                    uint8_t size = 1;
                    vsomeip::byte_t* data_ = new vsomeip::byte_t[size];
                    data_[0] = field_;
                    std::shared_ptr<vsomeip::payload> payload_ = rtm_->create_payload(data_, size);
                    response_->set_payload(payload_);
                    app_->send(response_);
                    delete[] data_;
                } break;
            }
        }
    }
}

bool Server::subscriptionHandler(vsomeip::client_t client_, bool subscribed) {
    LOGE("%s received client_t = %02X , subscribed = %d",__func__ ,client_,subscribed);
    //客户端订阅成功，启动一个线程来间隔5s广播事件
    if(subscribed){
        std::thread execute(&offerEventCycle, this);
        execute.detach();
    }
    return true;
}

void Server::stateHandler(vsomeip::state_type_e state) {
    LOGE("%s received state_type_e = %hhu",__func__ ,state);
    if(state == vsomeip::state_type_e::ST_REGISTERED){
        app_->offer_service(SERVICE_ID, INSTANCE_ID);
    }
}

void Server::callMethod(int value) {
    LOGE("%s received param = %d", __func__ , value);
}


