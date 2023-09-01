/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_EVENT_PUBLISHER_SERIALIZED_BASE_HPP
#define COM_BINDING_PIPC_EVENT_PUBLISHER_SERIALIZED_BASE_HPP

#include "ara/com/ISkeletonEvent.hpp"
#include "ara/com/types.h"
#include "binding/SerializedSample.hpp"
#include "binding/SomeipHeaderGen.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "binding/ReadableComponentIdentifier.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "pipc/pub_sub/LoanPublisher.hpp"
#include "pipc/sd/Runtime.hpp"
#include "serializer/ISerializer.hpp"
#include "utils/Logger.hpp"
#include "utils/ObjectStorage.hpp"

namespace com
{
namespace binding_pipc
{
/** @brief Class for publishing and sending serialized events on Pipc.
 * Sends events over underlying transport (pipc) to any subscribed receiver.
 *  This is, e.g. a gateway which puts it on the network.
 *  Allows configuration of E2E protection
 *  Allows configuration of serialization
 */
template<size_t N, typename SampleType>
class EventPublisherSerializedBase : public ara::com::ISkeletonEvent<SampleType>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using ComErrc        = ara::com::ComErrc;
    using EventCfgIpc    = com::config::EventCfgIpc;
    using EventCfgSomeIp = com::config::EventCfgSomeIp;
    using ISerializer    = com::serializer::ISerializer<SampleType>;
    using Logger         = com::utils::Logger;
    template<typename T>
    using UniquePtr     = ara::com::UniquePtr<T>;
    using PipcPublisher = pipc::pub_sub::LoanPublisher<binding::SerializedSample>;

    /** \brief Constructor for an IPC deployment */
    EventPublisherSerializedBase(const config::DeploymentContextIpc& context, const EventCfgIpc& eventCfg)
        : maxSampleSize_(eventCfg.maxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          bindingType_(ara::com::NetworkBindingEnum::IPC),
          cfgSomeIp_(),
          publisher_(ProviderIdGenerator::Generate(context, eventCfg), pipc::sd::Runtime::GetInstance(), maxSampleSize_),
          objectStorage_(),
          readableComponentId_{context, eventCfg.eventName}
    {
    }

    /** \brief Constructor for a "SOME/IP" deployment */
    EventPublisherSerializedBase(const config::DeploymentContextSomeIp& context, const EventCfgSomeIp& eventCfg)
        : maxSampleSize_(eventCfg.maxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          bindingType_(ara::com::NetworkBindingEnum::SOME_IP),
          cfgSomeIp_(eventCfg),
          publisher_(ProviderIdGenerator::Generate(context, eventCfg), pipc::sd::Runtime::GetInstance(), maxSampleSize_),
          objectStorage_(),
          readableComponentId_{context, eventCfg.eventName}
    {
    }

    ~EventPublisherSerializedBase() = default;

    EventPublisherSerializedBase& operator=(const EventPublisherSerializedBase& other) = delete;
    EventPublisherSerializedBase(const EventPublisherSerializedBase& other)            = delete;

    EventPublisherSerializedBase(EventPublisherSerializedBase&& other)      = delete;
    EventPublisherSerializedBase& operator=(EventPublisherSerializedBase&&) = delete;

    /**
     * @brief Offers the publisher's event.
     *
     * @return kCommunicationStackError if the publisher's startOffer() was not OK, otherwise returns void Result
     */
    ara::core::Result<void> Offer() override
    {
        auto offerCode = publisher_.startOffer();
        if (offerCode != pipc::ReturnCode::kOk)
        {
            Logger::GetInstance().LogError()
                << readableComponentId_
                << " Offer failed with internal error code: " << static_cast<uint16_t>(offerCode) << "\n";
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }
        return ara::core::Result<void>::FromValue();
    }

    /** @brief stops offering the publisher's event. */
    void StopOffer() override
    {
        publisher_.stopOffer();
    }

    /**
     * @brief allocates the sample.
     *
     * @return SampleAllocateePtr if successful, kSampleAllocationFailure if couldn't allocate
     */
    ara::core::Result<ara::com::SampleAllocateePtr<SampleType>> Allocate() override
    {
        auto sample = objectStorage_.getSampleAllocateePtr();

        if (!sample)
        {
            return ara::core::Result<ara::com::SampleAllocateePtr<SampleType>>::FromError(
                ComErrc::kSampleAllocationFailure);
        }

        return ara::core::Result<ara::com::SampleAllocateePtr<SampleType>>::FromValue(std::move(sample));
    }

protected:
    /** @brief The maxium size of the serialized sample. */
    const size_t maxSampleSize_;
    /** @brief Network binding type. */
    ara::com::NetworkBindingEnum bindingType_;
    /** @brief Someip event configuration. */
    EventCfgSomeIp cfgSomeIp_;
    /** @brief The Pipc loan publisher. */
    PipcPublisher publisher_;
    /** @brief Object storage used for sample allocation. */
    com::utils::ObjectStorage<N, SampleType> objectStorage_;
    /** @brief Identifier for human-friendly printouts. */
    const binding::ReadableComponentIdentifier readableComponentId_;
};
} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_EVENT_PUBLISHER_SERIALIZED_BASE_HPP
