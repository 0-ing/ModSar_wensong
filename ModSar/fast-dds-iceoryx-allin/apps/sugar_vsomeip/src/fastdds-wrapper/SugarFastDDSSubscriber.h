/***
 * 内嵌topic 和传输协议
 * topic 都是Events的唯一标识
 * type 是恒定的
 */
#include <functional>
#include "sugar/com/dds_event.h"
#include "protocol/HelloWorldPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

using namespace eprosima::fastdds::dds;

class SubListener : public DataReaderListener
{
public:
    SubListener()
        : samples_(0)
    {
    }

    ~SubListener() override
    {
    }

    void on_subscription_matched(DataReader *, const SubscriptionMatchedStatus &info) override;

    void on_data_available(DataReader *reader) override;

    std::vector<HelloWorld> caches_;

    std::atomic_int samples_;
    int maxSampleCount = 0;
    std::function<void()> onValiable;
    bool hadOnValiable = false;
};

class SugarFastDDSSubscriber : public sugar::com::IDDSSubscriber
{
public:
    DomainParticipant *participant_;

    Subscriber *subscriber_;

    DataReader *reader_;

    Topic *topic_;

    TypeSupport type_;

    SubListener listener_;

    SugarFastDDSSubscriber(const std::string &topicName);

    virtual ~SugarFastDDSSubscriber();

    //! Initialize the subscriber
    bool init();

    virtual void setReceiveHandler(const std::function<void()> &callback);

    int getNewSamples(const std::function<void(void *msg,int size)> &callback);

    void setMaxSamples(int size);

    void unsetReceiveHandler();
    
    std::string topicName;
};