//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      ProxyMethod.hpp
/// @brief     Interface class for proxy method
/// @copyright Robert Bosch GmbH 2020
/// @author    huy7si
//=============================================================================

#ifndef PROXY_METHOD_HPP_INCLUDED
#define PROXY_METHOD_HPP_INCLUDED

#include "ara/com/IProxyMethod.hpp"
#include "ara/com/IProxyMethodFireForget.hpp"

#include <memory>

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
 * \brief Class for fireforget method binding on proxy side, which is also responsible for the lifetime of the
 *underlying objects.
 **/
template<typename... TArgs>
class ProxyMethodFireForget : public IProxyMethodFireForget<TArgs...>
{
    // Make all Proxy Factories friend classes
    template<NetworkBindingEnum Binding>
    friend class ::com::service_deployment::ProxyFactory;

public:
    /** \brief Default constructor */
    ProxyMethodFireForget() = default;

    ProxyMethodFireForget(UniquePtr<IProxyMethodFireForget<TArgs...>> iPtr) : pImpl(std::move(iPtr))
    {
    }

    /* Method call operator */
    void operator()(const TArgs... args) override
    {
        pImpl->operator()(args...);
    }

private:
    UniquePtr<IProxyMethodFireForget<TArgs...>> pImpl;
};

/**
 * \brief Class for method binding on proxy side, which is also responsible for the lifetime of the underlying objects.
 **/
template<typename MethodOutput_T, typename... TArgs>
class ProxyMethod : public IProxyMethod<MethodOutput_T, TArgs...>
{
    // Make all Proxy Factories friend classes
    template<NetworkBindingEnum Binding>
    friend class ::com::service_deployment::ProxyFactory;

public:
    /** \brief Default constructor */
    ProxyMethod() = default;

    ProxyMethod(UniquePtr<IProxyMethod<MethodOutput_T, TArgs...>> iPtr) : pImpl(std::move(iPtr))
    {
    }

    /* Method call operator */
    ara::core::Future<MethodOutput_T> operator()(const TArgs... args) override
    {
        return pImpl->operator()(args...);
    }

    ara::com::e2e::SMState GetSMState() const noexcept override
    {
        return pImpl->GetSMState();
    }

private:
    UniquePtr<IProxyMethod<MethodOutput_T, TArgs...>> pImpl;
};
} // namespace com
} // namespace ara

#endif // PROXY_METHOD_HPP_INCLUDED
