//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      FieldSubscriber.hpp
/// @brief     Generic implementation for a Field Subscriber
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================
#ifndef COM_BINDING_FIELD_SUBSCRIBER_HPP
#define COM_BINDING_FIELD_SUBSCRIBER_HPP

#include "ara/com/IProxyEvent.hpp"
#include "ara/com/IProxyField.hpp"
#include "ara/com/IProxyMethod.hpp"

namespace com
{
namespace binding
{
/**
 * \brief Generic FieldSubscriber class
 *
 * The Field is a composition of 3 existing classes:
 * - A Notifier Event
 * - A Getter Method
 * - A Setter Method
 *
 * This is a generic class, which handles redirection of method calls
 * to the underlying members. It cannot exist on its own, as it has no concrete
 * binding implementation. Binding implementations have to derive from this class
 * and provide an appropriate constructor to inject the desired transport classes.
 *
 * \remark In the implementation we are not checking for null pointers
 * in the callbacks, because the callbacks are already deactivated by the
 * front-end class. This means they are uncallable and if they get called,
 * something is very wrong in our code and we should break.
 *
 * TODO: We can only do this if the FTL generator forwards the template arguments to the
 * Factory and then to the concrete constructor.
 * Disable if(pointer) later.
 */
template<typename FieldType_T>
class FieldSubscriber : public ara::com::IProxyField<FieldType_T>
{
public:
    /** \brief Declarations for readability and forwarding to inherited classes */
    using FieldType   = FieldType_T;
    using IProxyField = ara::com::IProxyField<FieldType>;
    using typename IProxyField::ComErrc;
    using typename IProxyField::SamplePointer;
    using typename IProxyField::SMState;
    using typename IProxyField::SubscriptionState;
    using typename ara::com::IProxyEvent<FieldType>::GetSampleReturnCode;
    template<typename T>
    using UniquePtr    = ara::com::UniquePtr<T>;
    using NotifierType = ara::com::IProxyEvent<FieldType>;
    using GetterType   = ara::com::IProxyMethod<FieldType, void>;
    // TODO: Make setter input 'const FieldType&'
    using SetterType = ara::com::IProxyMethod<FieldType, FieldType>;

    using NotifierUniquePtr = UniquePtr<NotifierType>;
    using GetterUniquePtr   = UniquePtr<GetterType>;
    using SetterUniquePtr   = UniquePtr<SetterType>;

    /** \brief Redirection to the notifier's \see GetSubScriptionState(). */
    virtual SubscriptionState GetSubscriptionState() const override
    {
        if (notifier)
        {
            return notifier->GetSubscriptionState();
        }
        return SubscriptionState::kNotSubscribed;
    }

    /** \brief Redirection to the notifier's \see Subscribe(). */
    virtual ara::core::Result<void> Subscribe(size_t maxSampleCount) override
    {
        if (notifier)
        {
            return notifier->Subscribe(maxSampleCount);
        }
        else
        {
            return ara::core::Result<void>::FromError(ComErrc::kServiceNotAvailable);
        }
    }

    /** \brief Redirection to the notifier's \see Unsubscribe(). */
    virtual void Unsubscribe() override
    {
        if (notifier)
        {
            notifier->Unsubscribe();
        }
    }

    /** \brief Redirection to the notifier's \see SetSubscriptionStateChangeHandler(). */
    virtual ara::core::Result<void> SetSubscriptionStateChangeHandler(
        ara::com::SubscriptionStateChangeHandler handler) override
    {
        if (notifier)
        {
            return notifier->SetSubscriptionStateChangeHandler(handler);
        }
        else
        {
            return ara::core::Result<void>::FromError(ComErrc::kServiceNotAvailable);
        }
    }

    /** \brief Redirection to the notifier's \see UnsetSubscriptionStateChangeHandler(). */
    virtual void UnsetSubscriptionStateChangeHandler() override
    {
        if (notifier)
        {
            notifier->UnsetSubscriptionStateChangeHandler();
        }
    }

    /** \brief Redirection to the notifier's \see SetReceiveHandler(). */
    virtual ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler) override
    {
        if (notifier)
        {
            return notifier->SetReceiveHandler(handler);
        }
        else
        {
            return ara::core::Result<void>::FromError(ComErrc::kServiceNotAvailable);
        }
    }

    /** \brief Redirection to the notifier's \see UnsetReceiveHandler(). */
    virtual ara::core::Result<void> UnsetReceiveHandler() override
    {
        if (notifier)
        {
            return notifier->UnsetReceiveHandler();
        }
        else
        {
            return ara::core::Result<void>::FromError(ComErrc::kUnsetFailure);
        }
    }

    /** \brief Redirection to the notifier's \see GetFreeSampleCount(). */
    virtual size_t GetFreeSampleCount() const override
    {
        if (notifier)
        {
            return notifier->GetFreeSampleCount();
        }
        else
        {
            return 0U;
        }
    }

    /** \brief Redirection to the notifier's \see GetSMState(). */
    virtual SMState GetSMState() const override
    {
        if (notifier)
        {
            return notifier->GetSMState();
        }
        else
        {
            return SMState::kStateMDisabled;
        }
    }

    /** \brief Redirection to the getter's \see Get(). */
    virtual ara::core::Future<FieldType> Get() override
    {
        if (getter)
        {
            return getter->operator()();
        }
        else
        {
            ara::core::Promise<FieldType> promise;
            promise.SetError(ComErrc::kServiceNotAvailable);
            return std::move(promise.get_future());
        }
    }

    /** \brief Redirection to the sgetter's \see Set(). */
    virtual ara::core::Future<FieldType> Set(const FieldType& value) override
    {
        if (setter)
        {
            return setter->operator()(value);
        }
        else
        {
            ara::core::Promise<FieldType> promise;
            promise.SetError(ComErrc::kServiceNotAvailable);
            return promise.get_future();
        }
    }

protected:
    /** \brief Default constructor for derived classes */
    FieldSubscriber() = default;

    /** \brief Constructor for unit testing */
    FieldSubscriber(NotifierUniquePtr&& _notifier, GetterUniquePtr&& _getter, SetterUniquePtr&& _setter)
        : notifier(std::move(_notifier)), getter(std::move(_getter)), setter(std::move(_setter))
    {
    }

    /** \brief Redirection to the notifier's \see GetSample() */
    ara::core::Result<SamplePointer, GetSampleReturnCode> GetSample(bool isFirstCall) override
    {
        if (notifier)
        {
            return notifier->GetSample(isFirstCall);
        }
        else
        {
            // TODO: Not a reasonable value, however, this should be removed anyway.
            return (ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(GetSampleReturnCode::kIpcTransportError));
        }
    }

    NotifierUniquePtr notifier; ///< The notifier event
    GetterUniquePtr getter;     ///< The getter method
    SetterUniquePtr setter;     ///< The setter method
};

} // namespace binding
} // namespace com

#endif // COM_BINDING_FIELD_SUBSCRIBER_HPP
