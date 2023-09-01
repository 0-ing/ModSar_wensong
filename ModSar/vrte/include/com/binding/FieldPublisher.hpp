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
/// @file      FieldPublisher.hpp
/// @brief     Generic implementation for a Field Publisher
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================
#ifndef COM_BINDING_FIELD_PUBLISHER_HPP
#define COM_BINDING_FIELD_PUBLISHER_HPP

#include "ara/com/ISkeletonEvent.hpp"
#include "ara/com/ISkeletonField.hpp"
#include "ara/com/ISkeletonMethod.hpp"
#include "ara/core/promise.h"
#include "utils/Logger.hpp"

#include <mutex>

namespace com
{
namespace binding
{
/**
 * \brief Generic FieldPublisher class
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
class FieldPublisher : public ara::com::ISkeletonField<FieldType_T>
{
public:
    /** \brief Declarations for readability and forwarding to inherited classes */
    using FieldType      = FieldType_T;
    using SampleType     = FieldType;
    using ISkeletonField = ara::com::ISkeletonField<FieldType>;
    template<typename T>
    using SampleAllocateePtr = ara::com::SampleAllocateePtr<T>;
    using ComErrc            = ara::com::ComErrc;
    template<typename T>
    using UniquePtr    = ara::com::UniquePtr<T>;
    using NotifierType = ara::com::ISkeletonEvent<FieldType>;
    using GetterType   = ara::com::ISkeletonMethod<FieldType>;
    // TODO: Make setter input 'const FieldType&'
    using SetterType = ara::com::ISkeletonMethod<FieldType, FieldType>;

    using NotifierUniquePtr = UniquePtr<NotifierType>;
    using GetterUniquePtr   = UniquePtr<GetterType>;
    using SetterUniquePtr   = UniquePtr<SetterType>;
    using Logger            = com::utils::Logger;

    /**
     * \brief Function to register a SetHandler.
     *
     * The getHandler gets called whenever a Get() call is invoked on the Proxy side.
     *
     * \remark
     * @ID{[SWS_CM_10412]}
     */
    ara::core::Result<void> RegisterGetHandler(std::function<ara::core::Future<FieldType>()> getHandler) override
    {
        if (getter)
        {
            updateFieldValue = false;

            getter->RegisterProcessingFunction(std::move(getHandler));
            return ara::core::Result<void>::FromValue();
        }
        else
        {
            return ara::core::Result<void>::FromError(ComErrc::kServiceNotAvailable);
        }
    }

    /**
     * \brief Function to register a SetHandler.
     *
     * The sethandler() gets called whenver a Set() call is invoked on the Proxy side.
     * This function wraps the given setHandler around an internal handler, which takes care of
     * calling the Update() method to conditionally update the internal value and notify other subscribers about the
     * value change.
     *
     * \remark
     * @ID{[SWS_CM_10413]}
     * @ID{[SWS_CM_10415]}
     */
    ara::core::Result<void> RegisterSetHandler(
        std::function<ara::core::Future<FieldType>(const FieldType& value)> setHandler) override
    {
        if (setter)
        {
            std::function<ara::core::Future<FieldType>(const FieldType& value)> internalSetHandler =
                [this, setHandler](const FieldType& value) {
                    // Call the real setHandler and consume the future
                    // HINT: We can do a blocking wait here, since this lambda is a wrapper around an asynchronuous call
                    auto future = setHandler(value);
                    future.wait();
                    auto result = future.GetResult();
                    if (result.HasValue())
                    {
                        static_cast<void>(Update(result.Value()));
                    }

                    // Return a new future with the same content
                    ara::core::Promise<FieldType> promise;
                    if (result.HasValue())
                    {
                        promise.set_value(result.Value());
                    }
                    else
                    {
                        promise.SetError(result.Error());
                    }

                    return promise.get_future();
                };
            setter->RegisterProcessingFunction(std::move(internalSetHandler));
            setHandlerValid = true;

            return ara::core::Result<void>::FromValue();
        }
        else
        {
            return ara::core::Result<void>::FromError(ComErrc::kServiceNotAvailable);
        }
    }

    /**
     * \brief Update function of the field.
     *
     * \remark
     * @ID{[SWS_CM_00119]}
     */
    ara::core::Result<void> Update(const FieldType& value) override
    {
        ara::core::Result<void> result{};
        fieldValueValid = true;
        
        if (notifier && fieldNotifierIsOffered)
        {

            result = std::move(notifier->Send(value));
        }

        if (updateFieldValue)
        {
            std::lock_guard<std::mutex> guard(fieldValueLock);
            value_ = value;
        }

        return result;
    }

    /**
     * \brief Function to check the field.
     *
     * \remark
     * @ID{[SWS_CM_00128]}
     * @ID{[SWS_CM_00129]}
     */
    ara::core::Result<void> checkFieldReady() override
    {
        // Check whether the field is initialized as expected
        if ((notifier || getter) && !fieldValueValid)
        {
            Logger::GetInstance().LogError() << "Field has notifier or getter, but field value is not set when offered. Please set field value with Update() before offering the service.\n";
            return ara::core::Result<void>::FromError(ComErrc::kFieldValueIsNotValid);
        }

        // Check if a set handler has been registered
        if (setter && !setHandlerValid)
        {
            Logger::GetInstance().LogError() << "Field has setter, but no set handler has been set on when offered. Please register set handler with RegisterSetHandler() before offering the service.\n";
            return ara::core::Result<void>::FromError(ComErrc::kSetHandlerNotSet);
        }

        return ara::core::Result<void>::FromValue();
    }

    /**
     * \brief Function to offer the field.
     */
    ara::core::Result<void> Offer() override
    {
        if (notifier)
        {
            fieldNotifierIsOffered = true;
            return notifier->Offer();
        }
        else
        {
            return ara::core::Result<void>::FromValue();
        }
    }


    /** \brief Function to stop offering the field.  */
    void StopOffer() override
    {
        if (notifier)
        {
            fieldNotifierIsOffered = false;
            notifier->StopOffer();
        }
    }

protected:
    /** \brief Default constructor for derived classes */
    FieldPublisher() = default;

    /** \brief Constructor for unit testing */
    FieldPublisher(NotifierUniquePtr&& _notifier, GetterUniquePtr&& _getter, SetterUniquePtr&& _setter)
        : notifier(std::move(_notifier)), getter(std::move(_getter)), setter(std::move(_setter))
    {
    }

    /** \brief Function to set a default getter method */
    void setDefaultGetter()
    {
        updateFieldValue = true;

        std::function<ara::core::Future<FieldType>()> defaultGetter = [this]() {
            ara::core::Promise<FieldType> promise;
            std::lock_guard<std::mutex> guard(fieldValueLock);
            promise.set_value(this->value_);
            return promise.get_future();
        };
        getter->RegisterProcessingFunction(std::move(defaultGetter));
    }

    NotifierUniquePtr notifier; ///< The notifier event
    GetterUniquePtr getter;     ///< The getter method
    SetterUniquePtr setter;     ///< The setter method
    FieldType value_;           ///< The internal field value
    std::mutex
        fieldValueLock; ///< Lock to protect field value against concurrent access in defaultGetter and update call.

    /** \brief Info whether the field value needs to be updated.
     *
     * \remark The field value shall be updated, when the Field has a Getter and
     * no custom Getter has been registered.
     *
     * \remark
     * @ID{[SWS_CM_00119]}
     */
    bool updateFieldValue{false};

    /** \brief Info whether the field value is valid.
     *
     * \remark The field value is valid if Update() has been called at least once.
     * A Field with an invalid value cannot be offered.
     *
     * \remark
     * @ID{[SWS_CM_00128]}
     */
    bool fieldValueValid{false};

    /** \brief Info whether a valid setHandler has been configured.
     *
     * TODO: Extend the ISkeletonMethod interface for this check to have it available everywhere.
     *
     * \remark
     * @ID{[SWS_CM_00129]}
     */
    bool setHandlerValid{false};

    /**
     * @brief Info if the field notifier is currently offered or not.
     *
     * This is required to not disturb the underlying notifier implementation with send calls without being offered. 
     * According to SWS_CM_00010 and SWS_CM_00011 (Stop)OfferService is not reentrant, thus, no atomic is required.
     */
    bool fieldNotifierIsOffered{false}; 
};

} // namespace binding
} // namespace com

#endif // COM_BINDING_FIELD_PUBLISHER_HPP
