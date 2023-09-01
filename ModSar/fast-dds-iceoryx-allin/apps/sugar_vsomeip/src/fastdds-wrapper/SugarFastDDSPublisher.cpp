#include "SugarFastDDSPublisher.h"

PubListener::PubListener()
    : matched_(0)
{
}

PubListener::~PubListener()
{
}

void PubListener::on_publication_matched(
    DataWriter *,
    const PublicationMatchedStatus &info)
{
    if (info.current_count_change == 1)
    {
        matched_ = info.total_count;
        std::cout << "Publisher matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        matched_ = info.total_count;
        std::cout << "Publisher unmatched." << std::endl;
    }
    else
    {
        std::cout << info.current_count_change
                  << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
    }
}

SugarFastDDSPublisher::SugarFastDDSPublisher(const std::string &topicName)
    : participant_(nullptr), publisher_(nullptr), topic_(nullptr), writer_(nullptr), type_(new HelloWorldPubSubType())
{
    this->topicName = topicName;
}

SugarFastDDSPublisher::~SugarFastDDSPublisher()
{
    if (writer_ != nullptr)
    {
        publisher_->delete_datawriter(writer_);
    }
    if (publisher_ != nullptr)
    {
        participant_->delete_publisher(publisher_);
    }
    if (topic_ != nullptr)
    {
        participant_->delete_topic(topic_);
    }
    DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

//! Initialize the publisher
bool SugarFastDDSPublisher::init()
{
    hello_.index(0);

    DomainParticipantQos participantQos;
    participantQos.name("Participant_publisher");
    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

    if (participant_ == nullptr)
    {
        return false;
    }

    // Register the Type
    type_.register_type(participant_);

    // Create the publications Topic
    topic_ = participant_->create_topic(topicName.c_str(), "HelloWorld", TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr)
    {
        return false;
    }

    // Create the Publisher
    publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

    if (publisher_ == nullptr)
    {
        return false;
    }

    // Create the DataWriter
    writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);

    if (writer_ == nullptr)
    {
        return false;
    }
    return true;
}

//! Send a publication
bool SugarFastDDSPublisher::publish(void *content, int size)
{
    if (listener_.matched_ > 0)
    {
        hello_.index(hello_.index() + 1);
        memcpy(&hello_.message()[0], content, size);
        writer_->write(&hello_);
        return true;
    }
    return false;
}
