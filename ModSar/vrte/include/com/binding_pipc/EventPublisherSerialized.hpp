/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_EVENT_PUBLISHER_SERIALIZED_HPP
#define COM_BINDING_PIPC_EVENT_PUBLISHER_SERIALIZED_HPP

#include "binding_pipc/EventPublisherSerializedBase.hpp"
#include "e2e/IE2EProtector.hpp"
#include "serializer/ISerializer.hpp"

namespace com
{
namespace binding_pipc
{
/** @brief Class for publishing and sending serialized events on Pipc.
 * Sends events over underlying transport (pipc) to any subscribed receiver.
 *  This is, e.g. a gateway which puts it on the network.
 *  Allows configuration of E2E protection
 *  Allows configuration of serialization
 *
 *  @note: Even though Allocate() may succeed, Send(SampleAllocateePtr) may still fail
 *  with kSampleAllocationFailure. One scenario to reproduce this is if we use Allocate() first,
 *  then use a couple of Send(SampleType), then use Send(SampleAllocateePtr). The last Send(SampleAllocateePtr)
 *  will fail if the PIPC Loan Publisher has no more free samples available.
 */
template<size_t N, typename SampleType>
class EventPublisherSerialized : public EventPublisherSerializedBase<N, SampleType>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using ComErrc        = ara::com::ComErrc;
    using EventCfgIpc    = com::config::EventCfgIpc;
    using EventCfgSomeIp = com::config::EventCfgSomeIp;
    using IE2EProtector  = e2e::IE2EProtector;
    using ISerializer    = com::serializer::ISerializer<SampleType>;
    using Logger         = com::utils::Logger;
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;
    using BaseClass = EventPublisherSerializedBase<N, SampleType>;

    /** \brief Constructor for an IPC deployment */
    EventPublisherSerialized(const config::DeploymentContextIpc& context,
                             const EventCfgIpc& eventCfg,
                             UniquePtr<ISerializer>&& serializer,
                             UniquePtr<IE2EProtector>&& protector)
        : BaseClass(context, eventCfg), serializer_(std::move(serializer)), protector_(std::move(protector))
    {
    }

    /** \brief Constructor for a "SOME/IP" deployment */
    EventPublisherSerialized(const config::DeploymentContextSomeIp& context,
                             const EventCfgSomeIp& eventCfg,
                             UniquePtr<ISerializer>&& serializer,
                             UniquePtr<IE2EProtector>&& protector)
        : BaseClass(context, eventCfg), serializer_(std::move(serializer)), protector_(std::move(protector))
    {
        protector_->setOffset(binding::SomeipHeaderGen::HEADER_SIZE);
    }

    ~EventPublisherSerialized() = default;

    EventPublisherSerialized& operator=(const EventPublisherSerialized& other) = delete;
    EventPublisherSerialized(const EventPublisherSerialized& other)            = delete;

    EventPublisherSerialized(EventPublisherSerialized&& other) = delete;
    EventPublisherSerialized& operator=(EventPublisherSerialized&&) = delete;

    /**
     * @brief sends Event's data.
     * calculate the sample's size after serialization with the needed headers
     * allocates storage for the sample. Serialize the sample and protect() it (if an e2e proflile is configured)
     * send the sample if no error occured in any of the previous steps
     *
     * @param data the data to be sent by the publisher
     * @return relevant ComErrc or returns void Result to represent successful Send
     */
    ara::core::Result<void> Send(const SampleType& data) override
    {
        // Calculate sizes
        uint32_t sampleSize           = serializer_->computeSerializedSize(&data);
        uint32_t sampleSerializeStart = static_cast<uint32_t>(protector_->getE2EHeaderLength());
        uint32_t totalSize            = sampleSize + sampleSerializeStart;

        if (this->bindingType_ == ara::com::NetworkBindingEnum::SOME_IP)
        {
            totalSize += binding::SomeipHeaderGen::HEADER_SIZE;
            sampleSerializeStart += binding::SomeipHeaderGen::HEADER_SIZE;
        }

        if ((totalSize + binding::SerializedSample::GetHeaderSize()) > this->maxSampleSize_)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_ << " Serialized sample of size "
                << totalSize + binding::SerializedSample::GetHeaderSize()
                << " is bigger than configured maxSampleSize of " << this->maxSampleSize_ << "\n";
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }

        auto sample = this->publisher_.allocate();

        if (!sample)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_ << " Shared Memory full, cannot send message\n";
            return ara::core::Result<void>::FromError(ComErrc::kSampleAllocationFailure);
        }

        sample.get()->resize(totalSize);
        auto sampleData = sample.get()->data();

        if (this->bindingType_ == ara::com::NetworkBindingEnum::SOME_IP)
        {
            if (!binding::SomeipHeaderGen::addHeader(sampleData, totalSize, this->cfgSomeIp_))
            {
                Logger::GetInstance().LogError()
                    << this->readableComponentId_ << " Could not add Application Someip header\n";
                return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
            }
        }

        // Serialize data
        // The serializer must successfully serialize within the amount of requested bytes,
        // checked within the serializer
        bool success = serializer_->serialize(&sampleData[sampleSerializeStart], sampleSize, &data);
        if (success == false)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_ << " Serializer didn't serialize the message correctly\n";
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }

        // The event will be sent only if protect function worked ok or if there is no profile configuration
        e2e::ProtectStatus protectStatus = protector_->protect(sampleData, totalSize, nullptr, 0);
        if (protectStatus == e2e::ProtectStatus::kOk || protectStatus == e2e::ProtectStatus::kProtectDisabled)
        {
            // send to shared memory
            this->publisher_.send(std::move(sample));
            return ara::core::Result<void>{};
        }
        else
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_
                << " Protect function for event failed (protectStatus :" << static_cast<uint16_t>(protectStatus)
                << ")\n";
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }
    }

    /**
     * @brief sends Event's data.
     * checks the passed SamplePtr, if not null then call the Send() on the sample's data.
     *
     * @param data the SamplePtr of the data to be sent by the publisher
     * @return void Result (no error) if 'data' is a nullptr, otherwise call Send() and return its result
     */
    ara::core::Result<void> Send(ara::com::SampleAllocateePtr<SampleType> data) override
    {
        // Check if the pointer really contains a sample
        if (data)
        {
            return Send(*(data.get()));
        }
        // There is no ErrorCode defined for empty samples, so return OK
        return ara::core::Result<void>{};
    }

private:
    /** @brief Sample serializer. */
    UniquePtr<ISerializer> serializer_;
    /** @brief Sample e2e protector. */
    UniquePtr<IE2EProtector> protector_;
};
} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_EVENT_PUBLISHER_SERIALIZED_HPP
