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
/// @file      Proxy.hpp
/// @brief     Library part of the proxy class
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef COM_SERVICE_DEPLOYMENT_PROXY_HPP
#define COM_SERVICE_DEPLOYMENT_PROXY_HPP

#include "ProxyFactory.hpp"
#include "ara/com/types.h"
#include "config/ServiceIntfCfgStatic.hpp"

namespace com
{
namespace service_deployment
{
/**
 * \brief Base class for a Proxy
 *
 * This class is the entry point for all generated proxy classes, which shall inherit from it.
 * It offers an API for proxy creation and can be extended later to provide other common
 * functions, which AUTOSAR demands (e.g. move semantics).
 */
class Proxy
{
protected:
    /** \brief This class is not constructible on its own */
    Proxy() = default;

    /**
     * \brief Function for instantiating a static config-based skeleton
     *
     * This function gets the instanceId, ConfigContainer and the actual events, field and methods
     * from the generated skeleton and creates the required impl objects.
     *
     * \remark We need to implement this as a function, it cannot be a constructor!
     * This function modifies objects of the base class, they have to be initialized first.
     */
    template<typename... TArgs>
    void createProxy(const InstanceIdentifier& instanceId, const config::ServiceCfg& config, TArgs&&... args)
    {
        config::ServiceIntfCfgBaseStatic baseCfg{instanceId, config};
        switch (baseCfg.getNetworkBinding())
        {
            case NetworkBindingEnum::IPC:
            {
                auto config = baseCfg.getIpcConfig();
                ProxyFactory<NetworkBindingEnum::IPC> factory{config};
                factory.createObjects(std::forward<TArgs>(args)...);
                break;
            }
            case NetworkBindingEnum::SOME_IP:
            {
                auto config = baseCfg.getSomeIpConfig();
                ProxyFactory<NetworkBindingEnum::SOME_IP> factory{config};
                factory.createObjects(std::forward<TArgs>(args)...);
                break;
            }
            default:
            {
                // ERROR!!!
                break;
            }
        }

        // Give the method clients some time to connect to prevent race conditions
        // TODO: Reconsider this, WI 26908
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
};

} // namespace service_deployment

} // namespace com

#endif // COM_SERVICE_DEPLOYMENT_PROXY_HPP
