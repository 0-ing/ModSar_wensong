//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/bit_compose.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_COMPOSE_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_COMPOSE_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/log/ref_logger.h"
#include "ucm/app/pkg/bin/v01xx/bitable.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

/// @class BIT_Compose bit_compose.h ucm/app/pkg/bin/v01xx/bit_compose.h
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @brief BIT Composer for vendor=0x00 and format=0x01xx
///
class BIT_Compose final : public BITable
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__BIT_Compose, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__BIT_Compose, add_files);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__BIT_Compose, block_reset);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__BIT_Compose, save_package);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__BIT_Compose, save_package2);
#endif

    using Base = BITable;

public:

    /// @brief Construct a BITcomposer object.
    ///
    /// Construct a BIT composer, setting the initial stream offset to the sum
    /// of the total size of authenticatiob block and the fixed size of the
    /// data block (since the BIT itself is placed in a data block).
    ///
    /// @param[in] afixed Fixed size of the AuthBlock
    /// @param[in] afloat Float size of the AuthBlock
    /// @param[in] dfixed Fixed size of the DataBlock
    /// @param[in] dfloat Float size of the DataBlock
    ///
    explicit BIT_Compose(std::size_t afixed, std::size_t afloat,
                         std::size_t dfixed, std::size_t dfloat) noexcept;

    BIT_Compose(BIT_Compose     &&) = default;
    BIT_Compose(BIT_Compose const&) = delete;

    BIT_Compose& operator=(BIT_Compose     &&) = default;
    BIT_Compose& operator=(BIT_Compose const&) = delete;

    ~BIT_Compose() = default;

    /// @brief Return the calculated size of the generated SWP.
    ///
    size_t swp_size() const noexcept;

    /// @brief Add files to the BITable and generate their records.
    ///
    Error add_files(const std::vector<sfile_pair>&) noexcept;

    Error save_package(lib::utl::FileIO&, DataBlock& blk,
                       const std::vector<sfile_pair>&) noexcept;

private:
    std::size_t ablock_fixed_{0};               ///< AuthBlock fixed size
    std::size_t ablock_float_{0};               ///< AuthBlock float size
    std::size_t dblock_fixed_{0};               ///< DataBlock fixed size
    std::size_t dblock_float_{0};               ///< DataBlock float size
    std::size_t stream_sofar_{0};               ///< Offset in the stream

    Error add_file(Fields&, const sfile_pair&) noexcept;

    Error save_file(lib::utl::FileIO&, DataBlock& blk,
                    const std::string&, size_t group) noexcept;

    Error save_files(lib::utl::FileIO&, DataBlock& blk,
                     const std::vector<sfile_pair>&) noexcept;

    static Error block_reset(DataBlock& blk, size_t grp, size_t seq) noexcept;
};

inline size_t BIT_Compose::swp_size() const noexcept
{
    return stream_sofar_;
}


}    // namespace v01xx
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_COMPOSE_H_
