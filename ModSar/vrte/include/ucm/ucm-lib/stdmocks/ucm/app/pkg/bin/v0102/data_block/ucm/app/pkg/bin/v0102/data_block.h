//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/pkg/bin/v0102/data_block/ucm/app/pkg/bin/v0102/data_block.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
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

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

class DataBlock final : public v01xx::DataBlock
                      , virtual protected ucm::mock::Sequence
{
    constexpr static std::size_t sigsize_value = 4;
    constexpr static std::size_t maxsize_value = 65536;

    using Base = v01xx::DataBlock;
    using hash_buff_t = std::array<std::uint8_t, sigsize_value>;

public:
    struct Fields
    {
        uint8_t  signature_[sigsize_value];
    } __attribute__((packed));

    constexpr static size_t fields_size() noexcept
    {
        return sizeof(Fields);
    }

    constexpr static size_t fixed_size() noexcept
    {
        return Base::fixed_size() + fields_size();
    }

    constexpr static size_t float_size() noexcept
    {
        return total_size() - fixed_size();
    }

    constexpr static size_t total_size() noexcept
    {
        return maxsize_value;
    }

    constexpr static size_t signature_size() noexcept
    {
        return sigsize_value;
    }


    static DataBlock create(Context_Ptr, Buffer&)
    { return std::move(pop<DataBlock&&>()); }

    explicit DataBlock(Context_Ptr, Buffer& buff, bool flag)
        : Base{buff, flag}
    {}

    DataBlock(DataBlock     &&) = default;
    DataBlock(DataBlock const&) = delete;

    DataBlock& operator=(DataBlock     &&) = default;
    DataBlock& operator=(DataBlock const&) = delete;

    ~DataBlock() = default;

    virtual bool ready() const noexcept override { return pop<bool>(); }

    virtual Error verify() noexcept override
    { return pop<Error>(); }

    virtual Error fixed_verify() noexcept
    { return pop<Error>(); }

    virtual Error reset(bool) noexcept override
    { return pop<Error>(); }

    virtual void ntoh_virt() noexcept override {}

    virtual void hton_virt() noexcept override {}

    /// @brief Update the authentication data for the block.
    ///
    virtual Error sec_update() noexcept override
    { return pop<Error>(); }

    virtual std::size_t blk_fixed_size() const noexcept override
    { return pop<std::size_t>(); }

    virtual std::size_t blk_float_size() const noexcept override
    { return pop<std::size_t>(); }

    virtual std::size_t blk_total_size() const noexcept override
    { return pop<std::size_t>(); }

    virtual std::size_t fld_float_size() const noexcept override
    { return pop<std::size_t>(); }

protected:
    static Fields* mapmem(Buffer&) { return pop<Fields*>(); }
    static Fields* mapcur(Buffer&) { return pop<Fields*>(); }
};

}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__DATA_BLOCK_H_
