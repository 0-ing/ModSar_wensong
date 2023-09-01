#include "protocol/HelloWorldPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

#include "sugar/com/dds_event.h"
using namespace eprosima::fastdds::dds;

class PubListener : public DataWriterListener
    {
    public:

        PubListener();

        ~PubListener();
        

        void on_publication_matched(
                DataWriter*,
                const PublicationMatchedStatus& info);

        std::atomic_int matched_;

    };
class SugarFastDDSPublisher : public sugar::com::IDDSPublisher
{
private:

    HelloWorld hello_;

    DomainParticipant* participant_;

    Publisher* publisher_;

    Topic* topic_;

    DataWriter* writer_;

    TypeSupport type_;

   PubListener  listener_;

public:

    SugarFastDDSPublisher(const std::string &topicName);

    virtual ~SugarFastDDSPublisher();

    //!Initialize the publisher
    bool init();
 
    //!Send a publication
    bool publish(void *content, int size);

    std::string topicName;
};