//
// Created by Gaddi
//
#include "SugarVSomeipSkeleton.h"

void SugarVSomeipSkeleton::ready()
{
    if (app_)
    {
        if (!app_->init())
        {
            LOGE("cannot init the application");
            return;
        }
        // 注册服务实例可用状态回调
        app_->register_availability_handler(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), std::bind(&SugarVSomeipSkeleton::availableHandler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        // 注册状态变化回调
        app_->register_state_handler(std::bind(&SugarVSomeipSkeleton::stateHandler, this, std::placeholders::_1));

        // 注册消息接收回调, 这里我们主要模拟三个属性的(SET,GET), 以及单纯的FUNC执行
        app_->register_message_handler(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), METHOD_ID_FIELD_GET, std::bind(&SugarVSomeipSkeleton::messageHandler, this, std::placeholders::_1));
        app_->register_message_handler(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), METHOD_ID_FIELD_SET, std::bind(&SugarVSomeipSkeleton::messageHandler, this, std::placeholders::_1));
        app_->register_message_handler(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), METHOD_ID_FUNC_CALL, std::bind(&SugarVSomeipSkeleton::messageHandler, this, std::placeholders::_1));
        // 注册客户端订阅事件组
        app_->register_subscription_handler(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_GROUP_ID_1, std::bind(&SugarVSomeipSkeleton::subscriptionHandler, this, std::placeholders::_1, std::placeholders::_4));
        // 注册事件
        std::set<vsomeip::eventgroup_t> group_set_1;
        group_set_1.insert(EVENT_GROUP_ID_1);

        app_->offer_event(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_ID_FIELD_NOTIFY, group_set_1,
                          vsomeip::event_type_e::ET_EVENT,
                          std::chrono::milliseconds::zero(),
                          false,
                          true,
                          nullptr,
                          vsomeip::reliability_type_e::RT_UNRELIABLE);
        app_->offer_event(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_ID_ONLY_NOTIFY_0, group_set_1,
                          vsomeip::event_type_e::ET_EVENT,
                          std::chrono::milliseconds::zero(),
                          false,
                          true,
                          nullptr,
                          vsomeip::reliability_type_e::RT_UNRELIABLE);
        LOGE("ready done for server");
    }
}

void SugarVSomeipSkeleton::start()
{
    if (app_)
    {
        LOGE("start for server");
        app_->start();
        LOGE("start done for server");
    }
}

/**
 * 当客户端订阅成功后，服务端每隔5s触发通知
 * @param srv
 */
static void offerEventCycle(SugarVSomeipSkeleton *srv)
{
    sleep(1);
    srv->sendWaitEvents();
#if 0
    const int size = 5;
    uint16_t v = 0;
    while (true)
    {
   
   
            vsomeip_v3::byte_t *data_ = new vsomeip_v3::byte_t(size + sizeof(int));
            int sessionid = -2;
            memcpy(data_, &sessionid, sizeof(int));

            for (int i = sizeof(int); i < size; i++)
            {
                data_[i] = v + i;
            }
            v++;
            std::shared_ptr<vsomeip::payload> payload_ = srv->rtm_->create_payload();
            payload_->set_data(data_, size + sizeof(int));
            srv->app_->notify(SERVICE_ID, INSTANCE_ID, EVENT_ID_ONLY_NOTIFY_0, payload_, true);
            delete data_;

        sleep(5);
        if (v == 10)
        {
            break;
        }
    }
#endif
}

void SugarVSomeipSkeleton::availableHandler(vsomeip::service_t service_, vsomeip::instance_t instance_,
                                            bool isAvailable)
{
    LOGE("%s received service = %02X , instance = %02X, isAvailable = %d",
         __func__,
         service_,
         instance_,
         isAvailable);
    static bool first = true;
    if (first)
    {
        promise.set_value(0);
        first = false;
    }
}

class SugarVsomeipResponse : public sugar::com::IResponse
{
public:
    int sessionid = 0;
    // 运行时环境
    std::shared_ptr<vsomeip::runtime> rtm_;
    // 服务端application
    std::shared_ptr<vsomeip::application> app_;

    std::shared_ptr<vsomeip::message> response_;

    SugarVsomeipResponse(int sessionid, std::shared_ptr<vsomeip::runtime> rtm_, std::shared_ptr<vsomeip::application> app_, std::shared_ptr<vsomeip::message> response_)
        : sessionid(sessionid), rtm_(rtm_), app_(app_), response_(response_)
    {
    }
    virtual void responseToProxy(int type, void *content, int size)
    {
        vsomeip::byte_t *data_ = new vsomeip::byte_t[size + sizeof(int)];
        memcpy(data_, &sessionid, sizeof(int));
        memcpy(data_ + sizeof(int), content, size);
        std::shared_ptr<vsomeip::payload> payload_ = rtm_->create_payload(data_, size + sizeof(int));
        response_->set_payload(payload_);
        app_->send(response_);
        delete[] data_;
    }
};
void SugarVSomeipSkeleton::messageHandler(const std::shared_ptr<vsomeip::message> &message_)
{
    if (message_)
    {
        LOGE("SugarVSomeipSkeleton::messageHandler  %s received service = %02X , instance = %02X, type = %hhu",
             __func__,
             message_->get_service(),
             message_->get_instance(),
             message_->get_message_type());

        if (message_->get_service() == instance_identifier.getServiceId() && message_->get_instance() == instance_identifier.getSerciceInstanceId())
        {
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
                if (size >= 4)
                {
                    int sessionid = *(int *)data;
                    LOGE("SugarVSomeipSkeleton::messageHandler ---》》》》》》》》》》》》》》》》》》sessionid:%d", sessionid);
                    // 回调出去
                    SugarVsomeipResponse response(sessionid, rtm_, app_, rtm_->create_response(message_));
                    messageCallback(type, &response, data + sizeof(int), size - sizeof(int));
                }
            }
            LOGE("SugarVSomeipSkeleton::messageHandler get ---》》》》》》》》》》》》》》》》》》get_method:%x", message_->get_method());
            switch (message_->get_method())
            {
            case METHOD_ID_FUNC_CALL:
            {
#if 0
                std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
                if (payload_)
                {
                    int val = payload_->get_data()[0];
                    callMethod(val);
                }
#endif
            }
            break;

            case METHOD_ID_FIELD_SET:
            {
#if 0
                // 获取客户端传递过来的数据
                std::shared_ptr<vsomeip::payload> payload_ = message_->get_payload();
                bool changed = false;
                if (payload_)
                {
                    uint32_t val = payload_->get_data()[0];
                    if (field_ != val)
                    {
                        field_ = val;
                        changed = true;
                    }
                    // 设置属性后，回复OK
                    if (message_->get_message_type() == vsomeip::message_type_e::MT_REQUEST)
                    {
                        std::shared_ptr<vsomeip::message> response_ = rtm_->create_response(message_);
                        app_->send(response_);
                    }

                    if (changed)
                    {
                        std::shared_ptr<vsomeip::payload> p_ = rtm_->create_payload();
                        vsomeip::byte_t *data_ = new vsomeip::byte_t[1];
                        data_[0] = field_;
                        p_->set_data(data_, 1);
                        app_->notify(SERVICE_ID, INSTANCE_ID, EVENT_ID_FIELD_NOTIFY, p_);
                        delete[] data_;
                    }
                }
#endif
                LOGE("SugarVSomeipSkeleton::messageHandler The client call field set val 5555555555555555555555555555555555555555555555555");
            }
            break;

            case METHOD_ID_FIELD_GET:
            {
                // 回复属性值field给到请求的客户端
                LOGE("SugarVSomeipSkeleton::messageHandler The client call field get val 6666666666666666666666666666666666666666666666");
#if 0
                std::shared_ptr<vsomeip::message> response_ = rtm_->create_response(message_);
                uint8_t size = 1;
                vsomeip::byte_t *data_ = new vsomeip::byte_t[size];
                data_[0] = field_;

                std::shared_ptr<vsomeip::payload> payload_ = rtm_->create_payload(data_, size);
                response_->set_payload(payload_);
                app_->send(response_);
                delete[] data_;
#endif
            }
            break;
            }
        }
    }
}

bool SugarVSomeipSkeleton::checkEventReady()
{
    std::unique_lock<std::mutex> lck(mtx2);
	cv2.wait(lck, [&]()->bool {return isSubscribled;});
    usleep(100*1000);  // TODO Need to find real solution for this event 
    
    return true;
}

void SugarVSomeipSkeleton::sendWaitEvents()
{

    waitEvents_mtx.lock();
    int index = 1;
    for (auto i = waitEvents.begin(); i != waitEvents.end(); ++i)
    {
        app_->notify(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_ID_ONLY_NOTIFY_0, *i, true);
        sugar::com::println("SugarVSomeipSkeleton::notifyToProxy--------------> %d", index++);
    }
    waitEvents.clear();
    waitEvents_mtx.unlock();
}
bool SugarVSomeipSkeleton::subscriptionHandler(vsomeip::client_t client_, bool subscribed)
{
    LOGE("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! %s received client_t = %02X , subscribed = %d", __func__, client_, subscribed);
    // 客户端订阅成功，启动一个线程来间隔5s广播事件
    if (subscribed)
    {
      //  std::thread execute(&offerEventCycle, this);
      //  execute.detach();
        std::unique_lock<std::mutex> lck(mtx2);
		isSubscribled = true;
		cv2.notify_one();
    }
    else {
        isSubscribled = false;
    }
    return true;
}

void SugarVSomeipSkeleton::stateHandler(vsomeip::state_type_e state)
{
    LOGE("%s received state_type_e = %hhu", __func__, state);
    if (state == vsomeip::state_type_e::ST_REGISTERED)
    {
        app_->offer_service(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId());
    }
}

void SugarVSomeipSkeleton::callMethod(int value)
{
    LOGE("%s received param = %d", __func__, value);
}

void SugarVSomeipSkeleton::notifyToProxy(void *content, int size)
{
    std::shared_ptr<vsomeip::payload> p_ = rtm_->create_payload();

    int sessionid = -2;
    vsomeip::byte_t *data_ = new vsomeip::byte_t[size + sizeof(int)];
    memcpy(data_, &sessionid, sizeof(int));

    memcpy(data_ + sizeof(int), content, size);
    p_->set_data(data_, size + sizeof(int));
    app_->notify(instance_identifier.getServiceId(), instance_identifier.getSerciceInstanceId(), EVENT_ID_ONLY_NOTIFY_0, p_, true);
    delete[] data_;
    //waitEvents_mtx.lock();
    //waitEvents.push_back(p_);
    //waitEvents_mtx.unlock();

    //sendWaitEvents();

    
}
