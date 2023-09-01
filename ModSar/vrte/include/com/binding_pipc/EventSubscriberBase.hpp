/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_EVENT_SUBSCRIBER_BASE_HPP
#define COM_BINDING_PIPC_EVENT_SUBSCRIBER_BASE_HPP

#include "ara/com/IProxyEvent.hpp"
#include "binding_pipc/ProviderIdGenerator.hpp"
#include "binding/ReadableComponentIdentifier.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "pipc/pub_sub/LoanSubscriber.hpp"
#include "pipc/sd/Runtime.hpp"
#include "utils/Logger.hpp"
#include "utils/TaskDispatcher.hpp"

#include <functional>

namespace com
{
namespace binding_pipc
{
/**
 * @brief Base class for EventSubscriber and EventSubscriberSerialized.
 *
 */
template<typename SampleType, typename PipcSubscriber>
class EventSubscriberBase : public ara::com::IProxyEvent<SampleType>
{
public:
    using ComErrc               = ara::com::ComErrc;
    using SubscriberPublicState = pipc::pub_sub::SubscriberPublicState;
    using E2ESMState            = ara::com::e2e::SMState;
    using PipcProviderId        = pipc::session::ProviderId;

    /**
     * \brief Assert if the sample type has any virtual method i.e. uses vtable.
     *
     * Virtual methods as part of the sample type are not possible,
     * as the vtable cannot be properly transferred via shmem.
     * This assertion ensures that such a problem shows up on compile time.
     * \todo
     * Should be checked in pipc directly.
     */
    static_assert(!std::is_polymorphic<SampleType>::value, "Polymorphic sample types not supported");

    /** \brief Constructor */
    template<typename ContextT, typename ConfigT>
    EventSubscriberBase(const ContextT& deploymentContext, const ConfigT& config)
        : subscriber_(ProviderIdGenerator::Generate(deploymentContext, config), pipc::sd::Runtime::GetInstance()),
          maxSampleCount_(0U),
          smState_(E2ESMState::kStateMDisabled),
          dispatcher_(),
          receiveHandler_(),
          readableComponentId_({deploymentContext, config.eventName})
    {
        dispatcher_.setReceiveHandler([this]() { this->invokeReceiveHandlerDispatcher(); });
    }

    /** \brief Constructor with stride as input.*/
    template<typename ContextT, typename ConfigT>
    EventSubscriberBase(const ContextT& deploymentContext, const ConfigT& config, size_t stride)
        : subscriber_(ProviderIdGenerator::Generate(deploymentContext, config),
                      pipc::sd::Runtime::GetInstance(),
                      stride),
          maxSampleCount_(0U),
          smState_(E2ESMState::kStateMDisabled),
          dispatcher_(),
          receiveHandler_(),
          readableComponentId_({deploymentContext, config.eventName})
    {
        dispatcher_.setReceiveHandler([this]() { this->invokeReceiveHandlerDispatcher(); });
    }

    /** \brief Subscribe to the event and set the maxSampleCount to be received.*/
    ara::core::Result<void> Subscribe(size_t maxSampleCount) override
    {
        if (maxSampleCount > subscriber_.getMailboxMaxSize())
        {
            utils::Logger::GetInstance().LogError()
                << readableComponentId_
                << " maxSampleCout exceeds maximum. Limit is: " << subscriber_.getMailboxMaxSize() << "\n";
            return ara::core::Result<void>::FromError(ComErrc::kMaxSampleCountNotRealizable);
        }
        if (this->GetSubscriptionState() != ara::com::SubscriptionState::kNotSubscribed)
        {
            if (maxSampleCount_ != maxSampleCount)
            {
                utils::Logger::GetInstance().LogError() << readableComponentId_ << " maxSampleCout " << maxSampleCount
                                                        << " differs from previous value " << maxSampleCount_ << "\n";
                return ara::core::Result<void>::FromError(ComErrc::kMaxSampleCountNotRealizable);
            }

            return ara::core::Result<void>::FromValue();
        }

        maxSampleCount_ = maxSampleCount;
        subscriber_.subscribe();
        return ara::core::Result<void>::FromValue();
    }

    /** \brief unsubscribe from the event.*/
    void Unsubscribe() override
    {
        subscriber_.unsubscribe();
    }

    /** \brief getter of the event's SubscriptionState.*/
    ara::com::SubscriptionState GetSubscriptionState() const override
    {
        return getAraSubscriptionState(subscriber_.getSubscriptionState());
    }

    ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler) override
    {
        // handler_ = handler;

        // std::function<void(SubscriberPublicState)> pipcHandler
        //     = std::bind(&EventSubscriberBase::pipcSubscriptionStateChangeHandler, this, std::placeholders::_1);
        // subscriber_.setSubscriptionStateChangeHandler(pipcHandler);
        // return ara::core::Result<void>::FromValue();

        static_cast<void>(handler);
        return ara::core::Result<void>::FromError(ComErrc::kServiceNotAvailable);
    }

    void UnsetSubscriptionStateChangeHandler() override
    {
        // subscriber_.setSubscriptionStateChangeHandler(nullptr);
        // handler_ = nullptr;
    }

    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler) override
    {
        receiveHandler_ = handler;
        subscriber_.setEventReceiveHandler([this]() { this->dispatcher_.notify(); });
        dispatcher_.start();
        return ara::core::Result<void>::FromValue();
    }

    ara::core::Result<void> UnsetReceiveHandler() override
    {
        subscriber_.setEventReceiveHandler(nullptr);
        dispatcher_.stop();
        return ara::core::Result<void>::FromValue();
    }

    E2ESMState GetSMState() const override
    {
        return smState_;
    }

protected:
    ara::com::SubscriptionState getAraSubscriptionState(SubscriberPublicState pipcSubscriptionState) const
    {
        switch (pipcSubscriptionState)
        {
        case SubscriberPublicState::kSubscribed:
            return ara::com::SubscriptionState::kSubscribed;
        case SubscriberPublicState::kNotSubscribed:
            return ara::com::SubscriptionState::kNotSubscribed;
        case SubscriberPublicState::kSubscriptionPending:
            return ara::com::SubscriptionState::kSubscriptionPending;
        default:
            return ara::com::SubscriptionState::kNotSubscribed;
        }
    }

    /** @brief Call registered receive handler, if a msg is received & a handler is registered. */
    void invokeReceiveHandlerDispatcher()
    {
        if (!this->subscriber_.getAppLayer().getMailbox().msgs_.empty())
        {
            if (receiveHandler_)
            {
                receiveHandler_();
            }
        }
    }

    /** @brief Pipc loan subscriber. */
    PipcSubscriber subscriber_;
    /** @brief Variable to store the maxSampleCount, which is set during Subscribe. */
    size_t maxSampleCount_;
    /** @brief Current state of the E2E State machine. */
    E2ESMState smState_;
    /** @brief Dispatcher to control the caller thread of the receiveHandler.*/
    utils::TaskDispatcher dispatcher_;
    /** @brief registered receiveHandler function.*/
    std::function<void()> receiveHandler_;
    /** @brief Identifier for human-friendly printouts. */
    const binding::ReadableComponentIdentifier readableComponentId_;
};
} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_EVENT_SUBSCRIBER_BASE_HPP
