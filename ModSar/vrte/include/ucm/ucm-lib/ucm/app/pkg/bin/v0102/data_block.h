//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v0102/data_block.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       vsa8cob
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__DATA_BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__DATA_BLOCK_H_

#include <array>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/pkg/bin/error.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

/// @class DataBlock
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @brief DataBlock implementation.

class DataBlock final : public v01xx::DataBlock
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, Ready);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, Reset);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, Verify);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, SecUpdate);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, VerifySelf);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, FixedVerify);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__DataBlock, FixedVerifySelf);
#endif

    constexpr static std::size_t sigsize_value = 4;
    constexpr static std::size_t maxsize_value = 65536;

    using Base = v01xx::DataBlock;
    using hash_buff_t = std::array<std::uint8_t, sigsize_value>;

public:
    struct Fields
    {
        uint8_t  signature_[sigsize_value];
    } __attribute__((packed));

    constexpr static size_t fields_size() noexcept;

    constexpr static size_t fixed_size() noexcept;

    constexpr static size_t float_size() noexcept;

    constexpr static size_t total_size() noexcept;

    constexpr static size_t signature_size() noexcept;

    /// @brief Create a data block.
    ///
    /// Construct a data block for vendor=0x000 and format=0x0102.
    ///
    /// @param[in] ctx SWP processing/composition context.
    /// @param[in] buff Flexible UCM buffer to use.
    /// @returns A constructed data block.
    /// @throws std::runtime_error if no mapping is possible.
    ///
    static DataBlock create(Context_Ptr ctx, Buffer& buff);

    /// @brief Construct a data block.
    ///
    /// @param[in] ctx SWP processing/composition context.
    /// @param[in] buff Flexible UCM buffer to use.
    /// @param[in] alloc Flag to show how the memory mapping is performed.
    ///
    explicit DataBlock(Context_Ptr ctx, Buffer&, bool alloc);

    DataBlock(DataBlock     &&) = default;
    DataBlock(DataBlock const&) = delete;

    DataBlock& operator=(DataBlock     &&) = delete;
    DataBlock& operator=(DataBlock const&) = delete;

    ~DataBlock() = default;

    //**************************************************************************
    // The methods below are declared in the lib::pkg::bin::Block class
    //**************************************************************************

    /// @brief Check if the Block loading into the buffer is complete.
    ///
    /// @return true,  if the Block is logically complete.
    /// @return false, if there is not enough data in the Buffer, to form a
    /// logically complete block.
    ///
    /// @note This class implementation returns true only if the buffer current
    /// size is equal to the Fields::tags_ member.
    ///
    /// @test The metrue only if the buffer current
    /// size is equal to the Fields::tags_ member.
    ///
    virtual bool ready() const noexcept override;

    /// @brief Verify the integrity of the buffer.
    ///
    /// @returns The method returns an object of type Error, holding the
    /// effective error code and the source location which detected the error.
    /// On success the Error == ErrorValue::kSuccess.
    ///
    virtual Error verify() noexcept override;

    /// @brief Verify the integrity of the fixed part of the block
    /// (i.e. the header).
    ///
    /// @returns The method returns an object of type Error, holding the
    /// effective error code and the source location which detected the error.
    /// On success the Error == ErrorValue::kSuccess.
    ///
    virtual Error fixed_verify() noexcept override;

    /// @brief Reset the block to an initial state.
    ///
    /// @param[in] alloc Re-allocate any structures mapped on the buffer.
    /// @returns The method returns an object of type Error, holding the
    /// effective error code and the source location which detected the error.
    /// On success the Error == ErrorValue::kSuccess.
    ///
    /// @note This class implementation merely resets the underlying buffer
    /// and returns Error{ErrorValue::kSuccess}.
    ///
    virtual Error reset(bool alloc) noexcept override;

    /// @brief Perform a network to host byte order conversion of the block.
    ///
    virtual void ntoh_virt() noexcept override;

    /// @brief Perform a host to network byte order conversion of the block.
    ///
    virtual void hton_virt() noexcept override;

    /// @brief Update the authentication data for the block.
    ///
    virtual Error sec_update() noexcept override;

    /// @brief Return the size of the block preamble.
    ///
    virtual std::size_t blk_fixed_size() const noexcept override;

    /// @brief Return the maximum data size of the block.
    ///
    virtual std::size_t blk_float_size() const noexcept override;

    /// @brief Return the maximum total size of the block.
    ///
    virtual std::size_t blk_total_size() const noexcept override;

    /// @brief Return the computed data size of the block.
    ///
    virtual std::size_t fld_float_size() const noexcept override;

    //**************************************************************************
    // The methods above are declared in the lib::pkg::bin::Block class
    //**************************************************************************

protected:
    static Fields* mapmem(Buffer&);
    static Fields* mapcur(Buffer&);

private:
    Fields *fields_;
    Context_Ptr context_;

    void ntoh_self() noexcept;
    void hton_self() noexcept;

    Error hash_block(hash_buff_t&) noexcept;

    Error verify_self() noexcept;

    Error fixed_verify_self() const noexcept;
};

inline constexpr size_t DataBlock::fields_size() noexcept
{
    return sizeof(Fields);
}

inline constexpr size_t DataBlock::fixed_size() noexcept
{
    return Base::fixed_size() + fields_size();
}

inline constexpr size_t DataBlock::float_size() noexcept
{
    return total_size() - fixed_size();
}

inline constexpr size_t DataBlock::total_size() noexcept
{
    return maxsize_value;
}

inline constexpr size_t DataBlock::signature_size() noexcept
{
    return sigsize_value;
}


}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__DATA_BLOCK_H_
