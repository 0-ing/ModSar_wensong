#include "SugarVSomeipProxy.h"

void SugarVSomeipProxy::ready()
{
    if (!app_->init())
    {
        LOGE("cannot init the application");
        return;
    }

    // 注册初始化回调
    app_->register_state_handler(std::bind(&SugarVSomeipProxy::stateHandler, this, std::placeholders::_1));
    // 注册服务实例发现状态回调
    app_->register_availability_handler(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), std::bind(&SugarVSomeipProxy::availableHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    // 注册消息回调
    app_->register_message_handler(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), vsomeip::ANY_METHOD, std::bind(&SugarVSomeipProxy::messageHandler, this, std::placeholders::_1));
}

void SugarVSomeipProxy::start()
{
    if (app_)
    {
        app_->start();
    }
}

void SugarVSomeipProxy::stateHandler(vsomeip::state_type_e state)
{
    LOGE("SugarVSomeipProxy %s received state_type_e = %hhu",
         __func__,
         state);
    // 初始化成功之后，请求服务
    if (state == vsomeip::state_type_e::ST_REGISTERED)
    {
        app_->request_service(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId());
    }
}

void SugarVSomeipProxy::availableHandler(vsomeip::service_t service_, vsomeip::instance_t instance_,
                                         bool isAvailable)
{
    LOGE("Client %s received service = %02X , instance = %02X, isAvailable = %d",
         __func__,
         service_,
         instance_,
         isAvailable);
    static bool first = true;
    if (isAvailable)
    {
        // 请求事件
        std::set<vsomeip::eventgroup_t> group_1;
        group_1.insert(EVENT_GROUP_ID_1);
        app_->request_event(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_ID_FIELD_NOTIFY, group_1,
                            vsomeip::event_type_e::ET_EVENT,
                            vsomeip::reliability_type_e::RT_UNRELIABLE);
        app_->request_event(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_ID_ONLY_NOTIFY_0, group_1,
                            vsomeip::event_type_e::ET_EVENT,
                            vsomeip::reliability_type_e::RT_UNRELIABLE);
        // 订阅事件
        app_->subscribe(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_GROUP_ID_1);
        if (first)
        {
            promise.set_value(-1);
            first = false;
        }
        
    }
  
   
}

void SugarVSomeipProxy::messageHandler(const std::shared_ptr<vsomeip::message> &message_)
{
    if (message_)
    {
        LOGE("SugarVSomeipProxy::messageHandler %s received service = %02X , instance = %02X, type = %hhu",
             __func__,
             message_->get_service(),
             message_->get_instance(),
             message_->get_message_type());
        sugar::com::SomeipProxyMethod type = sugar::com::SOMEIP_METHOD_INVALID;
        switch (message_->get_method())
        {
        case METHOD_ID_FIELD_GET:
        {
            type = sugar::com::SOMEIP_GET_FIELD;
        }
        break;
        case METHOD_ID_FIELD_SET:
        {
            type = sugar::com::SOMEIP_SET_FIELD;
        }
        break;
        case EVENT_ID_FIELD_NOTIFY:
        {
            type = sugar::com::SOMEIP_EVENT_NOTIFY;
        }
        break;
        case EVENT_ID_ONLY_NOTIFY_0:
        {
            type = sugar::com::SOMEIP_EVENT_NOTIFY;
        }
        break;
        case METHOD_ID_FUNC_CALL:
        {
            type = sugar::com::SOMEIP_METHOD;
        }
        break;
        }
        std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
        if (payload_)
        {
            uint16_t size = payload_->get_length();
            vsomeip::byte_t *data = payload_->get_data();
            if (size >= 4) {
                int sessionid = *(int*)data;
                LOGE("?????????????????????? SugarVSomeipProxy::messageHandler handle callback with session sessionid:--------> %d",sessionid);
                
                if (sessionid == -2)
                {
                    // 回调出去 event
                    messageCallback(type, data+sizeof(int), size - sizeof(int));
                }
                else {
                    
                    handleMessageCallback(sessionid,type, data+sizeof(int), size - sizeof(int));
                }
            }
          
        }

        switch (message_->get_method())
        {
        case METHOD_ID_FIELD_GET:
        {
            LOGE("Client get field: %d", message_->get_payload()->get_data()[0]);
        }
        break;
        case METHOD_ID_FIELD_SET:
        {
            bool isOk = message_->get_return_code() == vsomeip::return_code_e::E_OK;
            LOGE("Client set field result: %d", isOk);
        }
        break;
        case EVENT_ID_FIELD_NOTIFY:
        {
            std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
            if (payload_)
            {
                LOGE("Client received field changed event, the field is %d", payload_->get_data()[0]);
            }
        }
        break;
        case EVENT_ID_ONLY_NOTIFY_0:
        {
            std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
            if (payload_)
            {
                uint16_t size = payload_->get_length();
                vsomeip::byte_t *data = payload_->get_data();
                LOGE("Client received event, payload is: ");
                //for (int i = 0; i < size; i++)
               // {
                //    LOGE("%02X", data[i]);
               // }
            }
        }
        break;
        case METHOD_ID_FUNC_CALL:
        {
            LOGE("Client message method callback");
        }
        break;
        }
    }
}

// 调用服务端的方法
void SugarVSomeipProxy::callMethod(uint8_t value)
{
    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(instance_identifier.getServiceId());
    msg_->set_instance(instance_identifier.getSerciceInstanceId());
    msg_->set_method(METHOD_ID_FUNC_CALL);
    msg_->set_message_type(vsomeip::message_type_e::MT_REQUEST_NO_RETURN);
    vsomeip::byte_t *data_ = new vsomeip::byte_t[1];
    data_[0] = value;
    std::shared_ptr<vsomeip::payload> method_ = rtm_->create_payload(data_, 1);
    msg_->set_payload(method_);
    app_->send(msg_);
    delete[] data_;
}

// 调用服务端的setField方法
void SugarVSomeipProxy::callSetField(uint8_t field)
{
    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(instance_identifier.getServiceId());
    msg_->set_instance(instance_identifier.getSerciceInstanceId());
    msg_->set_method(METHOD_ID_FIELD_SET);
    vsomeip::byte_t *data_ = new vsomeip::byte_t[1];
    data_[0] = field;
    std::shared_ptr<vsomeip::payload> method_ = rtm_->create_payload(data_, 1);
    msg_->set_payload(method_);
    app_->send(msg_);
    delete[] data_;
}

// 调用服务端属性Get方法
void SugarVSomeipProxy::callGetField()
{
    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(instance_identifier.getServiceId());
    msg_->set_instance(instance_identifier.getSerciceInstanceId());
    msg_->set_method(METHOD_ID_FIELD_GET);
    app_->send(msg_);
}

void SugarVSomeipProxy::invokeToSkeleton(int type, void *content, int size)
{
    int id = 0;
    switch (type)
    {
    case sugar::com::SOMEIP_METHOD:
        id = METHOD_ID_FUNC_CALL;
        break;
    case sugar::com::SOMEIP_GET_FIELD:
        id = METHOD_ID_FIELD_GET;
        break;
    case sugar::com::SOMEIP_SET_FIELD:
        id = METHOD_ID_FIELD_SET;
        break;
    case sugar::com::SOMEIP_EVENT_NOTIFY:

        break;
    default:
        break;
    }

    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(instance_identifier.getServiceId());
    msg_->set_instance(instance_identifier.getSerciceInstanceId());
    msg_->set_method(id);
    msg_->set_message_type(vsomeip::message_type_e::MT_REQUEST_NO_RETURN);
    int sessionid = -1;
    vsomeip::byte_t *data_ = new vsomeip::byte_t[size+sizeof(int)];
    memcpy(data_,&sessionid,sizeof(int));
    memcpy(data_+sizeof(int), content, size);
    std::shared_ptr<vsomeip::payload> method_ = rtm_->create_payload(data_,size +sizeof(int));
    msg_->set_payload(method_);
    app_->send(msg_);
    delete[] data_;
}

void SugarVSomeipProxy::invokeToSkeletonWithCallback(int type, void *content, int size,const std::function<void(void*,int)> &callback)
{
    int id = 0;
    switch (type)
    {
    case sugar::com::SOMEIP_METHOD:
        id = METHOD_ID_FUNC_CALL;
        break;
    case sugar::com::SOMEIP_GET_FIELD:
        id = METHOD_ID_FIELD_GET;
        break;
    case sugar::com::SOMEIP_SET_FIELD:
        id = METHOD_ID_FIELD_SET;
        break;
    case sugar::com::SOMEIP_EVENT_NOTIFY:

        break;
    default:
        break;
    }
 

    std::shared_ptr<vsomeip::message> msg_ = rtm_->create_request(false);
    msg_->set_service(instance_identifier.getServiceId());
    msg_->set_instance(instance_identifier.getSerciceInstanceId());
    msg_->set_method(id);
    msg_->set_message_type(vsomeip::message_type_e::MT_REQUEST_NO_RETURN);
    sessionid_mtx.lock();
    sessionid ++;
    sessionid_mtx.unlock();
    vsomeip::byte_t *data_ = new vsomeip::byte_t[size+sizeof(int)];
    memcpy(data_,&sessionid,sizeof(int));
    memcpy(data_+sizeof(int), content, size);
    std::shared_ptr<vsomeip::payload> method_ = rtm_->create_payload(data_, size +sizeof(int));
    msg_->set_payload(method_);
    app_->send(msg_);
    sugar::com::printbin("SugarVSomeipProxy::invokeToSkeletonWithCallback end",data_,size+sizeof(int));
    delete[] data_;
    callbacks_mtx.lock();
    callbacks[sessionid] = callback;
    callbacks_mtx.unlock();
   
}


void SugarVSomeipProxy::handleMessageCallback(int sessionid,int type,void * data,int size)
{
    printf("SugarVSomeipProxy::handleMessageCallback %d\n",sessionid);
    std::function<void(void*,int)> callback;
    callbacks_mtx.lock();
    auto it = callbacks.find(sessionid);
   
    if (it == callbacks.end()) {
        callbacks_mtx.unlock();
        return;
    }
    callback = it->second;
    callbacks_mtx.unlock();
    callback(data,size);

}
