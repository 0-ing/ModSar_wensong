//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/pkg/bin/v0102/auth_block/ucm/app/pkg/bin/v0102/auth_block.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__AUTH_BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__AUTH_BLOCK_H_

#include <array>
#include <cstddef>
#include <cstdint>

#include "ucm/app/pkg/bin/v01xx/auth_block.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

class AuthBlock final
    : public v01xx::AuthBlock
    , virtual protected ucm::mock::Sequence
{
    constexpr static size_t   consteval_sigsize = 4;
    constexpr static uint32_t consteval_fmt_version = 0x0102;
    constexpr static uint16_t consteval_block_htype = 0x02FC;
    constexpr static uint16_t consteval_block_ssize = 128;

    using hash_buff_t = std::array<std::uint8_t, consteval_sigsize>;

    struct secdata
    {
        uint8_t selfsig_[consteval_sigsize];
    } __attribute__((packed));

    using Base = v01xx::AuthBlock;
    using Root = lib::pkg::bin::AuthBlock;

public:
    struct Fields
    {
        secdata  sec_;         // Sec data
    } __attribute__((packed));

    constexpr static size_t fields_size() noexcept
    {
        return sizeof(Fields);
    }

    constexpr static size_t fixed_size() noexcept
    {
       // return fields_size() + Base::fixed_size();
        return 0;
       
    }

    constexpr static size_t float_size() noexcept
    {
        return 0;
    }

    constexpr static size_t total_size() noexcept
    {
        return fixed_size() + float_size();
    }

    static AuthBlock create(Context_Ptr, Buffer&)
    { return std::move(pop<AuthBlock&&>()); }


    explicit AuthBlock(Context_Ptr, Buffer& buff, bool flag)
        : Base{buff, flag}
    {}

    explicit AuthBlock(Context_Ptr, Buffer& buff, const Fields&,
                       const Base::Fields&, const Root::Fields&)
        : Base{buff, false}
    {}

    AuthBlock(AuthBlock     &&) = default;
    AuthBlock(AuthBlock const&) = delete;

    AuthBlock& operator=(AuthBlock     &&) = default;
    AuthBlock& operator=(AuthBlock const&) = delete;

    virtual ~AuthBlock() = default;

    virtual bool ready() const noexcept override { return pop<bool>(); }

    virtual Error verify() noexcept override { return pop<Error>(); }

    virtual Error fixed_verify() noexcept { return pop<Error>(); }

    virtual Error reset(bool) noexcept override { return pop<Error>(); }

    virtual void ntoh_virt() noexcept override {}

    virtual void hton_virt() noexcept override {}

    virtual Error sec_update() noexcept override { return pop<Error>(); }

    virtual std::size_t blk_fixed_size() const noexcept override
    { return pop<std::size_t>(); }

    virtual std::size_t blk_float_size() const noexcept override
    { return pop<std::size_t>(); }

    virtual std::size_t blk_total_size() const noexcept override
    { return pop<std::size_t>(); }

    virtual std::size_t fld_float_size() const noexcept override
    { return pop<std::size_t>(); }

protected:
    static Fields* mapcur(Buffer&) { return pop<Fields*>(); }
    static Fields* mapmem(Buffer&) { return pop<Fields*>(); }
};


}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__AUTH_BLOCK_H_
