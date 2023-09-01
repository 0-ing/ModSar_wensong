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

#include "ucm/lib/buf/model.h"
#include "ucm/lib/utl/file_io.h"

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/types.h"
#include "ucm/lib/pkg/bin/block.h"
#include "ucm/app/pkg/bin/context.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

class DataBlock
		: public lib::pkg::bin::Block
		, virtual protected ucm::mock::Sequence
{
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

    explicit DataBlock(Buffer& buff, bool)
    	: Base(buff)
    {}

    DataBlock(DataBlock     &&) = default;
    DataBlock(DataBlock const&) = delete;

    DataBlock& operator=(DataBlock     &&) = default;
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

    std::size_t write(const void *, std::size_t) noexcept override
    { return pop<std::size_t>(); }

    bool ready() const noexcept override
    { return pop<bool>(); }

    Error verify() noexcept override
    { return pop<Error>(); }

    Error fixed_verify() noexcept override
    { return pop<Error>(); }

    Error reset(bool) noexcept override
    { return pop<Error>(); }

    void ntoh_virt() noexcept override {}

    void hton_virt() noexcept override {}

    std::size_t blk_fixed_size() const noexcept override
    { return pop<std::size_t>(); }

    std::size_t blk_float_size() const noexcept override
    { return pop<std::size_t>(); }

    std::size_t blk_total_size() const noexcept override
    { return pop<std::size_t>(); }

    std::size_t fld_float_size() const noexcept override
    { return pop<std::size_t>(); }

    Error sec_update() noexcept override
    { return Error(ErrorValue::kSuccess); }

    //**************************************************************************
    // The methods above are declared in the lib::pkg::bin::Block class
    //**************************************************************************

protected:
    static Fields* mapcur(Buffer&) { return pop<Fields*>(); }
    static Fields* mapmem(Buffer&) { return pop<Fields*>(); }

private:
    Fields *fields_{nullptr};
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
    return pop<std::uint64_t>();
}

inline std::uint32_t DataBlock::field_group() const noexcept
{
    return pop<std::uint32_t>();
}

inline std::uint32_t DataBlock::field_seqno() const noexcept
{
   // return fields_->seqno_;
   return pop<std::uint32_t>();
}

inline void DataBlock::field_bsize(std::uint64_t) noexcept
{
    //fields_->bsize_ = value;
}

inline void DataBlock::field_group(std::uint32_t) noexcept
{
    //fields_->group_ = value;
}

inline void DataBlock::field_seqno(std::uint32_t) noexcept
{
    //fields_->seqno_ = value;
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
