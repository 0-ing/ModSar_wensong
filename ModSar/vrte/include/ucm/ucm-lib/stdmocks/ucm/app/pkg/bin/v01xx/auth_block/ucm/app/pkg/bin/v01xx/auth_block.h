//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/auth_block.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__AUTH_BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__AUTH_BLOCK_H_

#include "ucm/lib/pkg/bin/auth_block.h"

#include "ucm/app/pkg/bin/context.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

class AuthBlock
        : public lib::pkg::bin::AuthBlock
		, virtual protected ucm::mock::Sequence
{
    using Base = lib::pkg::bin::AuthBlock;

protected:
    constexpr static uint16_t consteval_block_htype = 0x02FC;
    constexpr static uint16_t consteval_block_ssize = 128;
    constexpr static uint64_t consteval_sec_padding = 0;
    constexpr static uint32_t consteval_vendor_tag  = 0;

protected:
    using ErrorValue = lib::pkg::bin::ErrorValue;
    using Context_Ptr = std::shared_ptr<Context>;

public:
    struct Fields
    {
        uint16_t bht_;         ///< Block hash type
        uint16_t bss_;         ///< Block signature size
        uint64_t sdp_;         ///< Security data padding
    } __attribute__((packed));

    constexpr static size_t fields_size() noexcept;

    constexpr static size_t fixed_size() noexcept;

    constexpr static size_t float_size() noexcept;

    constexpr static size_t total_size() noexcept;

    static AuthBlock create(Buffer& buff, uint32_t) {
        return AuthBlock(buff, true);
    }

    explicit AuthBlock(Buffer& buff, bool flag)
        : Base(buff, flag)
    {}

    explicit AuthBlock(Buffer& buff,
                     const Fields&,
                     const Base::Fields&)
        : Base(buff, false)
    {}

    AuthBlock(AuthBlock     &&) = default;
    AuthBlock(AuthBlock const&) = default;

    AuthBlock& operator=(AuthBlock     &&) = default;
    AuthBlock& operator=(AuthBlock const&) = default;

    virtual ~AuthBlock() = default;

    uint16_t field_htype() const noexcept { return pop<uint16_t>(); }
    uint16_t field_ssize() const noexcept { return pop<uint16_t>(); }
    uint64_t field_sdpad() const noexcept { return pop<uint64_t>(); }

    bool ready() const noexcept override
    { return pop<bool>(); }

    Error verify() noexcept override
    { return pop<Error>(); }

    Error fixed_verify() noexcept
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

protected:
    static Fields* mapcur(Buffer&)
    { return pop<Fields*>(); }

    static Fields* mapmem(Buffer&)
    { return pop<Fields*>(); }

    static void hton_fields(Fields*) noexcept {}
};

inline constexpr size_t AuthBlock::fields_size() noexcept
{
    return sizeof(Fields);
}

inline constexpr size_t AuthBlock::fixed_size() noexcept
{
    return fields_size() + Base::fixed_size();
}

inline constexpr size_t AuthBlock::float_size() noexcept
{
    return 0;
}

inline constexpr size_t AuthBlock::total_size() noexcept
{
    return fixed_size() + float_size();
}

}    // namespace v01xx
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__AUTH_BLOCK_H_
