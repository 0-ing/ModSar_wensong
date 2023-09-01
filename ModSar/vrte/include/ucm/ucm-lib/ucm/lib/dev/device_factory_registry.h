//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/dev/device_factory_registry.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_REGISTRY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_REGISTRY_H_

#include <mutex>
#include <vector>
#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/dev/device_factory.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace dev   {

/// @brief A registry for Device Factories
///
/// To find the correct device driver factory for a given node the Device
/// Factory Registry will search over its registeres Device Factories which
/// supports this node
class DeviceFactoryRegistry final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_dev_DeviceFactoryRegistry, add_factory);
    FRIEND_TEST(Test_ucm_lib_dev_DeviceFactoryRegistry, get_factory);
#endif

public:
    explicit DeviceFactoryRegistry();

    DeviceFactoryRegistry(      DeviceFactoryRegistry &&) = delete;
    DeviceFactoryRegistry(const DeviceFactoryRegistry  &) = delete;

    DeviceFactoryRegistry& operator=(       DeviceFactoryRegistry &&) = delete;
    DeviceFactoryRegistry& operator=(const  DeviceFactoryRegistry  &) = delete;

    virtual ~DeviceFactoryRegistry() = default;

    /// Adds a factory to the registry
    /// @param factory The factory to be added
    void add_factory(std::unique_ptr<DeviceFactory>&& factory);

    /// Searches the most specific device driver factory for the given type and
    /// node
    /// @param type Type of the node
    /// @param node Name of the node
    /// @return Reference to the device factory
    DeviceFactory& get_factory(const std::string& type,
                               const std::string& node);

private:
    mutable std::mutex mutex_{};
    std::vector<std::unique_ptr<DeviceFactory>> cache_{};
};

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_REGISTRY_H_
