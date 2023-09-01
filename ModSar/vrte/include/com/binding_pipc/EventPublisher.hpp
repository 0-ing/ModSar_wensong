/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_EVENT_PUBLISHER_HPP
#define COM_BINDING_PIPC_EVENT_PUBLISHER_HPP

#include "ara/com/ISkeletonEvent.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "pipc/pub_sub/LoanPublisher.hpp"
#include "pipc/sd/Runtime.hpp"
#include "utils/Logger.hpp"

namespace com
{
namespace binding_pipc
{
/**
 * @brief Class for IPC-based event offering and sending
 *
 * Sends events over underlying transport (pipc).
 * Without E2E (not required).
 * Without serialization.
 */
template<typename SampleType>
class EventPublisher : public ara::com::ISkeletonEvent<SampleType>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using ComErrc       = ara::com::ComErrc;
    using Logger        = com::utils::Logger;
    using EventCfgIpc   = com::config::EventCfgIpc;
    using PipcPublisher = pipc::pub_sub::LoanPublisher<SampleType>;

    /**
     * \brief Assert if an event class has any virtual method i.e. uses vtable.
     *
     * Memory are statically allocated in PIPC, so the use of classes
     * with virtual methods is not possible. This assertion ensures that such a
     * problem shows up on compile time.
     */
    static_assert(!std::is_polymorphic<SampleType>::value, "Polymorphic sample types not supported");

    /** \brief Constructor for an IPC deployment */
    EventPublisher(const config::DeploymentContextIpc& context, const EventCfgIpc& eventCfg)
        : publisher_(ProviderIdGenerator::Generate(context, eventCfg), pipc::sd::Runtime::GetInstance())
    {
    }

    ~EventPublisher() = default;

    EventPublisher& operator=(const EventPublisher& other) = delete;
    EventPublisher(const EventPublisher& other)            = delete;

    EventPublisher(EventPublisher&& other)      = delete;
    EventPublisher& operator=(EventPublisher&&) = delete;

    ara::core::Result<void> Offer() override
    {
        auto offerCode = publisher_.startOffer();
        if (offerCode != pipc::ReturnCode::kOk)
        {
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }
        return ara::core::Result<void>::FromValue();
    }

    void StopOffer() override
    {
        publisher_.stopOffer();
    }

    ara::core::Result<ara::com::SampleAllocateePtr<SampleType>> Allocate() override
    {
        auto sample = publisher_.allocate();

        if (!sample)
        {
            return ara::core::Result<ara::com::SampleAllocateePtr<SampleType>>::FromError(
                ComErrc::kSampleAllocationFailure);
        }

        return ara::core::Result<ara::com::SampleAllocateePtr<SampleType>>::FromValue(std::move(sample));
    }

    ara::core::Result<void> Send(const SampleType& data) override
    {
        publisher_.send(data);
        return ara::core::Result<void>::FromValue();
    }

    ara::core::Result<void> Send(ara::com::SampleAllocateePtr<SampleType> data) override
    {
        if (data)
        {
            publisher_.send(std::move(data));
        }

        return ara::core::Result<void>::FromValue();
    }

private:
    PipcPublisher publisher_;
};
} // namespace binding_pipc
} // namespace com

#endif
