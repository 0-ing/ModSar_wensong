//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/dev/device_factory_posix.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_POSIX_H_
#define UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_POSIX_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/dev/device_factory.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace dev   {

/// @brief A device factory for posix device drivers
class DeviceFactoryPosix : public DeviceFactory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_dev__DeviceFactoryPosix, CTor);
#endif

public:
    explicit DeviceFactoryPosix();

    DeviceFactoryPosix(      DeviceFactoryPosix &&) = default;
    DeviceFactoryPosix(const DeviceFactoryPosix  &) = default;

    DeviceFactoryPosix& operator=(       DeviceFactoryPosix &&) = default;
    DeviceFactoryPosix& operator=(const  DeviceFactoryPosix  &) = default;

    virtual ~DeviceFactoryPosix() = default;

    virtual std::unique_ptr<Posix>
    create(const Device::Specs& specs) override;
};

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_DEV__DEVICE_FACTORY_POSIX_H_
