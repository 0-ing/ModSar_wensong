//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/bitable.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BITABLE_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BITABLE_H_

#include <array>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/buf/model.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/pkg/bin/error.h"
#include "ucm/app/pkg/bin/types.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

/// @class BITable bitable.h ucm/app/pkg/bin/v01xx/bitable.h
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @brief Block information table for vendor=0x00 and format=0x01xx
///
class BITable
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__BITable, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__BITable, record);
#endif

protected:
    constexpr static size_t maxrecs = 128;

    using Buffer     = lib::buf::Model;
    using ErrorValue = lib::pkg::bin::ErrorValue;

public:

    /// @brief BIT Record types.
    enum class Type : uint16_t
    {
        kUCM_BITable        = 0x0009,
        kUCMS_AuthTag       = 0x0001,
        kUCMS_Manifest      = 0x0003,
        kUCMS_Application   = 0x0005,
        kUCMS_BinaryImage   = 0x0007,
        kUCMM_AuthTag       = 0xA009,
        kUCMM_Manifest      = 0xA00B,
        kUCMM_SWPackage     = 0xA00D,
    };

    static Type str2type(const std::string&);

    static const char* type2str(const Type&) noexcept;

    /// @brief BIT Record fields.
    struct Fields
    {
        uint64_t bofft_;    ///< Offset of the first block
        uint64_t tsize_;    ///< Total size of the blocks in sequence group
        uint64_t dsize_;    ///< Total size of the data in sequence group
        uint64_t count_;    ///< Number of blocks for this group
        uint32_t group_;    ///< Group to which the record belongs
        uint16_t ident_;    ///< Identification of the record
        uint16_t asize_;    ///< Address size
    } __attribute__((packed));

    constexpr static size_t fields_size() noexcept;

    explicit BITable() noexcept;

    BITable(BITable     &&) = default;
    BITable(BITable const&) = delete;

    BITable& operator=(BITable     &&) = default;
    BITable& operator=(BITable const&) = delete;

    virtual ~BITable() = default;

    /// @brief Log information about the BIT - i.e. its records.
    ///
    void log_info() noexcept;

    void hton_table() noexcept;
    void ntoh_table() noexcept;

    size_t rec_count() const noexcept;
    size_t rec_bytes() const noexcept;

    size_t get_index(const Type&);
    size_t get_index(const Type&, size_t);

    const Fields& get_record(size_t) const;

    /// @brief Reset the BIT, setting count_ to 0.
    ///
    virtual void reset() noexcept;

protected:
    std::size_t record_count_{0};               ///< Number of records
    std::array<Fields, maxrecs> records_{};     ///< Buffer for records

    static void ntoh_record(Fields&) noexcept;
    static void hton_record(Fields&) noexcept;

    Error add_record(Fields&&) noexcept;
};

inline constexpr size_t BITable::fields_size() noexcept
{
    return sizeof(Fields);
}

inline size_t BITable::rec_count() const noexcept
{
    return record_count_;
}

inline size_t BITable::rec_bytes() const noexcept
{
    return rec_count() * fields_size();
}



}    // namespace v01xx
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BITABLE_H_
