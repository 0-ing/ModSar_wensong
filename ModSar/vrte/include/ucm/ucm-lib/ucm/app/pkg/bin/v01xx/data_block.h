//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/data_block.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       vsa8cob
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__DATA_BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__DATA_BLOCK_H_

#include <limits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/buf/model.h"
#include "ucm/lib/utl/file_io.h"

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/types.h"
#include "ucm/lib/pkg/bin/block.h"

#include "ucm/app/pkg/bin/context.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

/// @class DataBlock
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @brief DataBlock implementation.

class DataBlock : public lib::pkg::bin::Block
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__DataBlock, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__DataBlock, Write);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__DataBlock, Ready);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__DataBlock, Reset);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__DataBlock, Verify);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__DataBlock, FixedVerify);
#endif

    constexpr static std::size_t maxsize_value = 65536;

    using Base = lib::pkg::bin::Block;

protected:
    using Buffer        = lib::buf::Model;
    using ErrorValue    = lib::pkg::bin::ErrorValue;
    using Context_Ptr   = std::shared_ptr<Context>;
    using iofile_offset = lib::pkg::bin::iofile_offset;
    using memory_offset = lib::pkg::bin::memory_offset;
public:
    struct Fields
    {
        std::uint64_t bsize_;        ///< Block total size
        std::uint32_t group_;        ///< Block group number
        std::uint32_t seqno_;        ///< Block sequence number
    } __attribute__((packed));

    constexpr static size_t fields_size() noexcept;

    constexpr static size_t fixed_size() noexcept;

    constexpr static size_t float_size() noexcept;

    constexpr static size_t total_size() noexcept;

    explicit DataBlock(Buffer&, bool alloc);

    DataBlock(DataBlock     &&) = default;
    DataBlock(DataBlock const&) = delete;

    DataBlock& operator=(DataBlock     &&) = delete;
    DataBlock& operator=(DataBlock const&) = delete;

    virtual ~DataBlock() = default;

    /// @brief Return the block total size.
    ///
    std::uint64_t field_bsize()  const noexcept;

    /// @brief Return the block group number.
    ///
    std::uint32_t field_group()  const noexcept;

    /// @brief Return the block sequence number.
    ///
    std::uint32_t field_seqno()  const noexcept;

    /// @brief Set the the block size value.
    ///
    void field_bsize(std::uint64_t) noexcept;

    /// @brief Set the the block group number.
    ///
    void field_group(std::uint32_t) noexcept;

    /// @brief Set the block sequence number.
    ///
    void field_seqno(std::uint32_t) noexcept;

    //**************************************************************************
    // The methods below are declared in the lib::pkg::bin::Block class
    //**************************************************************************

    /// @brief Write no more than size bytes to the underlying buffer.
    ///
    /// @param[in] data Pointer to the external data block.
    /// @param[in] size Size of the external data block.
    /// @retval Number of bytes actually written.
    ///
    virtual std::size_t write(const void *data, std::size_t size) noexcept override;

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
    static Fields* mapcur(Buffer&);
    static Fields* mapmem(Buffer&);

private:
    Fields *fields_;

    void ntoh_self() noexcept;
    void hton_self() noexcept;

    Error verify_self() const noexcept;

    Error fixed_verify_self() const noexcept;
};

inline constexpr size_t DataBlock::fields_size() noexcept
{
    return sizeof(Fields);
}

inline constexpr size_t DataBlock::fixed_size() noexcept
{
    return fields_size();
}

inline constexpr size_t DataBlock::float_size() noexcept
{
    return total_size() - fixed_size();
}

inline constexpr size_t DataBlock::total_size() noexcept
{
    return maxsize_value;
}

inline std::uint64_t DataBlock::field_bsize() const noexcept
{
    return fields_->bsize_;
}

inline std::uint32_t DataBlock::field_group() const noexcept
{
    return fields_->group_;
}

inline std::uint32_t DataBlock::field_seqno() const noexcept
{
    return fields_->seqno_;
}

inline void DataBlock::field_bsize(std::uint64_t value) noexcept
{
    fields_->bsize_ = value;
}

inline void DataBlock::field_group(std::uint32_t value) noexcept
{
    fields_->group_ = value;
}

inline void DataBlock::field_seqno(std::uint32_t value) noexcept
{
    fields_->seqno_ = value;
}

}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__DATA_BLOCK_H_
