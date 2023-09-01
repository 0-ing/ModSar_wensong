//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/dev/flashing_adapter_file.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_dev

#ifndef UCM_AAP_LIBRARY__UCM_AAP_DEV__FLASHING_ADAPTER_FILE_H_
#define UCM_AAP_LIBRARY__UCM_AAP_DEV__FLASHING_ADAPTER_FILE_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/dev/posix.h"

/// @addtogroup bosch_vrte_ucm_app_dev
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace dev   {
    
/// @class FlashingAdapterFile
/// @ingroup bosch_vrte_ucm_app_dev
/// @brief Default implementation.
///

class FlashingAdapterFile : public lib::dev::Posix
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_aap_dev__FlashingAdapterNull, CTor);
#endif

public:

    explicit FlashingAdapterFile(const lib::dev::Device::Specs&) noexcept;

    FlashingAdapterFile(      FlashingAdapterFile &&) = default;
    FlashingAdapterFile(const FlashingAdapterFile  &) = delete;

    FlashingAdapterFile& operator=(      FlashingAdapterFile &&) = default;
    FlashingAdapterFile& operator=(const FlashingAdapterFile  &) = delete;

    virtual ~FlashingAdapterFile() = default;

    // =========================================================================
    // Own virtual methods
    // =========================================================================
    /// @brief Copy data from one location to another - invalid
    ///
    /// @param src Source offset
    /// @param dst Destination offset
    /// @param count The number of bytes to copy
    ///
    /// @return true on success, false otherwise
    __attribute__((warn_unused_result))
    virtual bool
    io_copy(off_t src, off_t dst, size_t count) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t
    io_pread(void *buff, size_t nbyte) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t
    io_pread(void *buff, size_t nbyte, off_t offset) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t
    io_pwrite(const void *buff, size_t count) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t
    io_pwrite(const void *buff, size_t count, off_t offset) noexcept;

protected:
};

}    // namespace dev
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_AAP_DEV__FLASHING_ADAPTER_FILE_H_
