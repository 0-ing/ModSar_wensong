//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lip/dev/device.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_DEV_DEVICE_H_
#define UCM_AAP_LIBRARY_LIB_DEV_DEVICE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"
#include "ucm/lib/utl/object_locker.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace dev {

/// @brief An abstract description of a memory device.
/// The needed parameters of the device are described here, but no assumptions
/// about the device type are made. This is left to the back-end driver (more
/// over a device could be accessed by various means).
///
/// At the moment there are two unique keys - devid_ and node_. Since the
/// lookup table in TargetDB uses RB-trees this should lead to lower memory
/// footprint and faster searches
class Device final
    : public utl::ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_dev_Device, CTor);
#endif

public:
    constexpr static const usize_type devid_invalid   = id_type_max;
    constexpr static const usize_type octsize_invalid = ssize_type_max;
    constexpr static const usize_type blksize_invalid = ssize_type_max;
    constexpr static const usize_type erasesz_invalid = ssize_type_max;
    constexpr static const usize_type ioalign_invalid = ssize_type_max;
    constexpr static const usize_type address_invalid = ssize_type_max;

    constexpr static auto& invalid_devid() noexcept
    {
        return id_type_max;
    }

    struct Specs
    {
        bool ioexcl_        {false};            // exclusive I/O access
        bool syncio_        {false};            // O_SYNC
        bool wrerase_       {false};
        std::string node_   {};                 // OS node for the device
        std::string type_   {};                 // Device type
        id_type    devid_   {devid_invalid};    // Unique device id
        usize_type octsize_ {octsize_invalid};  // device size in bytes
        usize_type blksize_ {blksize_invalid};  // device's block size
        usize_type erasesz_ {erasesz_invalid};  // device erase block
        usize_type ioalign_ {ioalign_invalid};  // device I/O align block
        usize_type address_ {address_invalid};  // memory address
    };

    explicit Device(Specs&&) {}

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;
    Device(Device&&) noexcept = delete;
    Device& operator=(Device&&) = delete;
    virtual ~Device() = default;

    const auto& node() const noexcept { return mock::Sequence::pop<std::string const&>(); }
    const auto& type() const noexcept { return mock::Sequence::pop<std::string const&>(); }
    const auto& specs() const noexcept { return mock::Sequence::pop<Specs const&>(); }
    const auto& devid() const noexcept { return mock::Sequence::pop<id_type const&>(); }
    const auto& ioexcl() const noexcept { return mock::Sequence::pop<bool const&>(); }
    const auto& syncio() const noexcept { return mock::Sequence::pop<bool const&>(); }
    const auto& wrerase() const noexcept { return mock::Sequence::pop<bool const&>(); }
    const auto& octsize() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
    const auto& blksize() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
    const auto& erasesz() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
    const auto& ioalign() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
    const auto& address() const noexcept { return mock::Sequence::pop<usize_type const&>(); }
};


}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_DEV_DEVICE_H_
