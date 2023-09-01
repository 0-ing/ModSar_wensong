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
/// @file      Skeleton.hpp
/// @brief     Library part of the skeleton class
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef COM_SERVICE_DEPLOYMENT_SKELETON_HPP
#define COM_SERVICE_DEPLOYMENT_SKELETON_HPP

#include "SkeletonFactory.hpp"
#include "config/ServiceIntfCfgStatic.hpp"

namespace com
{
namespace service_deployment
{
/**
 * \brief Base class for a Skeleton
 *
 * This class is the entry point for all generated skeleton classes, which shall inherit from it.
 * It offers an API for skeleton creation and can be extended later to provide other common
 * functions, which AUTOSAR demands (e.g. move semantics).
 */
class Skeleton
{
public:
    /** \brief No copy or move operations allowed */
    Skeleton(const Skeleton& other) = delete;
    Skeleton(Skeleton&& other)      = delete;

protected:
    /** \brief This class is not constructible on its own */
    Skeleton() = default;

    /** \brief Function for instantiating a static config-based skeleton
     *
     * This function gets the instanceIdContainer, ConfigContainer and the actual events, field and methods
     * from the generated skeleton and creates the required impl objects for each InstanceId found in
     * instanceIdContainer.
     *
     * \remark We need to implement this as a function, it cannot be a constructor!
     * This function modifies objects of the base class, they have to be initialized first.
     * If an empty instanceIdContainer is given , an exception will be thrown.
     */
    template<typename... TArgs>
    void createSkeleton(const ara::com::InstanceIdentifierContainer& instanceIdContainer,
                        const config::ServiceCfg& config,
                        TArgs&&... args)
    {
        if (instanceIdContainer.size() != 1)
        {
            throw std::invalid_argument("no/more than on items found in the InstanceIdentifierContainer.Currently only one item is supported!");
            return;
        }

        //currently only one InstanceIdentifier per InstanceSpecifier is supported
        config::ServiceIntfCfgBaseStatic baseCfg{instanceIdContainer.front(), config};
        switch (baseCfg.getNetworkBinding())
        {
        case NetworkBindingEnum::IPC:
        {
            auto config = baseCfg.getIpcConfig();
            SkeletonFactory<NetworkBindingEnum::IPC> factory{config};
            factory.createObjects(std::forward<TArgs>(args)...);
            break;
        }
        case NetworkBindingEnum::SOME_IP:
        {
            auto config = baseCfg.getSomeIpConfig();
            SkeletonFactory<NetworkBindingEnum::SOME_IP> factory{config};
            factory.createObjects(std::forward<TArgs>(args)...);
            break;
        }
        default:
        {
            // ERROR!!!
            break;
        }
        }
    }
};

} // namespace service_deployment

} // namespace com

#endif // COM_SERVICE_DEPLOYMENT_SKELETON_HPP
