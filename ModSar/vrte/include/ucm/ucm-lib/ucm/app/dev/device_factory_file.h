//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/dev/device_factory_file.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_dev

#ifndef UCM_AAP_LIBRARY__UCM_APP_DEV__DEVICE_FACTORY_FILE_H_
#define UCM_AAP_LIBRARY__UCM_APP_DEV__DEVICE_FACTORY_FILE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/dev/device_factory.h"

/// @addtogroup bosch_vrte_ucm_app_dev
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace dev   {

/// @class DeviceFactoryFile
/// @ingroup bosch_vrte_ucm_app_dev
/// @brief Default implementation.
///

class DeviceFactoryFile : public lib::dev::DeviceFactory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_dev__DeviceFactoryFile, CTor);
#endif

public:
    explicit DeviceFactoryFile();

    DeviceFactoryFile(      DeviceFactoryFile &&) = default;
    DeviceFactoryFile(const DeviceFactoryFile  &) = default;

    DeviceFactoryFile& operator=(       DeviceFactoryFile &&) = default;
    DeviceFactoryFile& operator=(const  DeviceFactoryFile  &) = default;

    virtual ~DeviceFactoryFile() = default;

    virtual std::unique_ptr<lib::dev::Posix>
    create(const lib::dev::Device::Specs& specs) override;
};

}    // namespace dev
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_DEV__DEVICE_FACTORY_FILE_H_
