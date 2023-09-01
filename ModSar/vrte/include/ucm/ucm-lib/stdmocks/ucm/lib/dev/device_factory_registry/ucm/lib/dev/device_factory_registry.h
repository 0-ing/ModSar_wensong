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

#include "ucm/lib/dev/device_factory.h"
#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace dev   {

class DeviceFactoryRegistry final : virtual protected ucm::mock::Sequence
{
public:
    explicit DeviceFactoryRegistry() {};

    DeviceFactoryRegistry(      DeviceFactoryRegistry &&) = delete;
    DeviceFactoryRegistry(const DeviceFactoryRegistry  &) = delete;

    DeviceFactoryRegistry& operator=(       DeviceFactoryRegistry &&) = delete;
    DeviceFactoryRegistry& operator=(const  DeviceFactoryRegistry  &) = delete;

    virtual ~DeviceFactoryRegistry() = default;

    void add_factory(std::unique_ptr<DeviceFactory>&& ) {
    };

    DeviceFactory& get_factory(const std::string&,
                               const std::string& ) {
                                   return *pop<std::shared_ptr<DeviceFactory>>();
                               }
};

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_REGISTRY_H_
