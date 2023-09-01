#include "SugarFastDDSSubscriber.h"

void SubListener::on_subscription_matched(
    DataReader *,
    const SubscriptionMatchedStatus &info)
{
    if (info.current_count_change == 1)
    {
        std::cout << "Subscriber matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        std::cout << "Subscriber unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void SubListener::on_data_available(
    DataReader *reader) 
{
    SampleInfo info;
    HelloWorld hello_;
    if (reader->take_next_sample(&hello_, &info) == ReturnCode_t::RETCODE_OK)
    {
        if (info.valid_data)
        {
            caches_.push_back(hello_);
            samples_++;
            std::cout << "Message: " << hello_.message() << " with index: " << hello_.index() << "lst1:" << (int)hello_.message().at(10) << " last2:" << (int)hello_.message().at(11)
                      << " RECEIVED. size:" << hello_.message().size() << " len:" << hello_.message().length() << std::endl;
            if (hadOnValiable)
                onValiable();
        }
    }
}

SugarFastDDSSubscriber::SugarFastDDSSubscriber(const std::string &topicName)
    : participant_(nullptr), subscriber_(nullptr), topic_(nullptr), reader_(nullptr), type_(new HelloWorldPubSubType())
{
    this->topicName = topicName;
}

SugarFastDDSSubscriber::~SugarFastDDSSubscriber()
{
    if (reader_ != nullptr)
    {
        subscriber_->delete_datareader(reader_);
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    if (subscriber_ != nullptr)
    {
        participant_->delete_subscriber(subscriber_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}
bool SugarFastDDSSubscriber::init()
{
    DomainParticipantQos participantQos;
    participantQos.name("Participant_subscriber");
    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

    if (participant_ == nullptr)
    {
        return false;
    }

    // Register the Type
    type_.register_type(participant_);

    // Create the subscriptions Topic
    topic_ = participant_->create_topic(this->topicName.c_str(), "HelloWorld", TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr)
    {
        return false;
    }

    // Create the Subscriber
    subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);

    if (subscriber_ == nullptr)
    {
        return false;
    }

    // Create the DataReader
    reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT, &listener_);

    if (reader_ == nullptr)
    {
        return false;
    }

    return true;
}

void SugarFastDDSSubscriber::setReceiveHandler(const std::function<void()> &callback)
{
    listener_.onValiable = callback;
    listener_.hadOnValiable = true;
}

int SugarFastDDSSubscriber::getNewSamples(const std::function<void(void *msg,int size)> &callback)
{
    auto caches = listener_.caches_;
    if (caches.empty()) return 0;
    for (auto i = caches.begin(); i != caches.end();++i)
    {
        callback(&i->message()[0],i->message().size());
    }
    return caches.size();
}

void SugarFastDDSSubscriber::setMaxSamples(int size) 
{
    listener_.maxSampleCount = size;
}

void SugarFastDDSSubscriber::unsetReceiveHandler(){
    listener_.hadOnValiable = false;
}