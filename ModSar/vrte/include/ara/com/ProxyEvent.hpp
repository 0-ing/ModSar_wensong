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
/// @file      ProxyEvent.hpp
/// @brief     Front end class for proxy events
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_PROXY_EVENT_HPP
#define ARA_COM_PROXY_EVENT_HPP

#include "ara/com/IProxyEvent.hpp"

/** \brief Forward declaration of the ProxyFactory class */
namespace com
{
namespace service_deployment
{
template<ara::com::NetworkBindingEnum Binding>
class ProxyFactory;

} // namespace service_deployment
} // namespace com

namespace ara
{
namespace com
{
/**
 * \brief Front end class for \see IProxyEvent.
 *
 * The bridge pattern is used to enable access to event methods without a pointer
 * derefence, as required per AR API specification.
 */
template<typename SampleType_T>
class ProxyEvent
{
    // Make all Proxy Factories friend classes
    template<NetworkBindingEnum Binding>
    friend class ::com::service_deployment::ProxyFactory;

public:
    using SampleType     = SampleType_T;
    using IProxyEventPtr = UniquePtr<IProxyEvent<SampleType>>;
    using SamplePointer  = SamplePtr<const SampleType>;

    /** \brief Default constructor */
    ProxyEvent() = default;

    /** \brief Constructor for taking over concrete implementation of IProxyEvent */
    ProxyEvent(IProxyEventPtr&& f_proxyPtr) : pImpl(std::move(f_proxyPtr))
    {
    }

    ara::core::Result<void> Subscribe(size_t maxSampleCount)
    {
        return pImpl->Subscribe(maxSampleCount);
    }

    void Unsubscribe()
    {
        pImpl->Unsubscribe();
    }

    ara::com::SubscriptionState GetSubscriptionState() const
    {
        return pImpl->GetSubscriptionState();
    }

    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        return pImpl->SetReceiveHandler(handler);
    }

    ara::core::Result<void> UnsetReceiveHandler()
    {
        return pImpl->UnsetReceiveHandler();
    }

    template<typename F>
    ara::core::Result<size_t> GetNewSamples(F&& f, size_t maxNumberOfSamples = std::numeric_limits<size_t>::max())
    {
        return pImpl->GetNewSamples(std::forward<F&&>(f), maxNumberOfSamples);
    }

    ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler)
    {
        return pImpl->SetSubscriptionStateChangeHandler(handler);
    }

    void UnsetSubscriptionStateChangeHandler()
    {
        pImpl->UnsetSubscriptionStateChangeHandler();
    }

    size_t GetFreeSampleCount() const noexcept
    {
        return pImpl->GetFreeSampleCount();
    }

    ara::com::e2e::SMState GetSMState() const noexcept
    {
        return pImpl->GetSMState();
    }

protected:
    ara::core::Result<SamplePointer, ComErrc> GetSample()
    {
        return pImpl->GetSample();
    }

    IProxyEventPtr pImpl;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_PROXY_EVENT_HPP
