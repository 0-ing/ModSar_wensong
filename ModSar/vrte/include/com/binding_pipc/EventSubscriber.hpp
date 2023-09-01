/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_EVENT_SUBSCRIBER_HPP
#define COM_BINDING_PIPC_EVENT_SUBSCRIBER_HPP

#include "binding_pipc/EventSubscriberBase.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "pipc/pub_sub/LoanSubscriber.hpp"
#include "pipc/sd/Runtime.hpp"

#include <atomic>

namespace com
{
namespace binding_pipc
{
/**
 * @brief Class for IPC-based event subscribing.
 *
 * Receives events from underlying transport (pipc).
 */
template<typename SampleType>
class EventSubscriber : public EventSubscriberBase<SampleType, pipc::pub_sub::LoanSubscriber<const SampleType>>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using BaseClass     = EventSubscriberBase<SampleType, pipc::pub_sub::LoanSubscriber<const SampleType>>;
    using EventCfgIpc   = com::config::EventCfgIpc;
    using SamplePointer = ara::com::SamplePtr<const SampleType>;

    /** \brief Constructor for an IPC deployment */
    EventSubscriber(const config::DeploymentContextIpc& context, const EventCfgIpc& eventCfg)
        : BaseClass(context, eventCfg), usedSampleSlots_(0U)
    {
    }

    ~EventSubscriber()                                       = default;
    EventSubscriber& operator=(const EventSubscriber& other) = delete;
    EventSubscriber& operator=(EventSubscriber&&)            = delete;
    EventSubscriber(const EventSubscriber& other)            = delete;
    EventSubscriber(EventSubscriber&& other)                 = delete;

    size_t GetFreeSampleCount() const override
    {
        return (this->maxSampleCount_ - usedSampleSlots_.load(std::memory_order_relaxed));
    }

protected:
    using typename ara::com::IProxyEvent<SampleType>::GetSampleReturnCode;

    ara::core::Result<SamplePointer, GetSampleReturnCode> GetSample(bool) override
    {
        if (usedSampleSlots_.load(std::memory_order_relaxed) < this->maxSampleCount_)
        {
            pipc::loan::LoanedSamplePtr<const SampleType> samplePtr;
            if (this->subscriber_.tryReceive(samplePtr))
            {
                usedSampleSlots_.fetch_add(1, std::memory_order_release);
                std::function<void()> comSampleDeleter = std::bind(&EventSubscriber::sampleDeleter, this);
                return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromValue(std::move(samplePtr),
                                                                                        comSampleDeleter);
            }
            else
            {
                // Return a SamplePtr(nullptr) to represent NoSamplesAvailable
                return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(GetSampleReturnCode::kNoSample);
            }
        }

        // All sample slots occupied
        // @ID{[SWS_CM_00022]}
        return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(GetSampleReturnCode::kMaxSamplesReached);
    }

    void sampleDeleter()
    {
        usedSampleSlots_.fetch_sub(1, std::memory_order_release);
    }

    /** @brief Variable to keep track of the used samples. */
    std::atomic<size_t> usedSampleSlots_;
};

} // namespace binding_pipc
} // namespace com
#endif // COM_BINDING_PIPC_EVENT_SUBSCRIBER_HPP
