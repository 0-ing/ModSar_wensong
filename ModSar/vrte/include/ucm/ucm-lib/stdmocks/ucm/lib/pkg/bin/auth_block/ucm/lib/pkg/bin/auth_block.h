//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocs/ucm/lib/pkg/bin/auth_block/ucm/lib/pkg/bin/auth_block.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       dsh8cob
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_pkg_bin

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__AUTH_BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__AUTH_BLOCK_H_

#include <cstddef>
#include <cstdint>

#include "ucm/lib/utl/cutils.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/log/ref_logger.h"

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/block.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

class AuthBlock
        : public Block
        , virtual protected ucm::mock::Sequence
{
    using Base = Block;

public:
    struct Fields
    {
        uint64_t  swps_;           ///< total SWP size
        uint32_t  cfmt_;           ///< container format version
        uint32_t  tags_;           ///< Authentication tag size
        uint32_t  vtag_;           ///< vendor tag
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
        return 0;
    }

    constexpr static size_t total_size() noexcept
    {
        return fixed_size() + float_size();
    }

    static AuthBlock create(Buffer& tb, uint32_t vendor, uint32_t format)
    {
        auto pfields = mapcur(tb);
        pfields->swps_ = fixed_size();
        pfields->cfmt_ = format;
        pfields->tags_ = fixed_size();
        pfields->vtag_ = vendor;
        return AuthBlock(tb, false);
    }

    explicit AuthBlock(Buffer& buffer, bool)
        : Block(buffer)
    {}

    explicit AuthBlock(Buffer& buffer, const Fields&)
        : Block(buffer)
    {}

    AuthBlock(AuthBlock     &&) = default;
    AuthBlock(AuthBlock const&) = delete;

    AuthBlock& operator=(AuthBlock     &&) = default;
    AuthBlock& operator=(AuthBlock const&) = delete;

    virtual ~AuthBlock() = default;

    uint64_t field_swps() const noexcept
    {
        return pop<uint64_t>();
    }

    uint32_t field_tags() const noexcept
    {
        return pop<uint32_t>();
    }

    uint32_t field_vtag() const noexcept
    {
        return pop<uint32_t>();
    }

    uint32_t field_cfmt() const noexcept
    {
        return pop<uint32_t>();
    }

    void field_swps(uint64_t) noexcept {}

    void field_tags(uint32_t) noexcept {}

    void field_vtag(uint32_t) noexcept {}

    void field_cfmt(uint32_t) noexcept {}

    virtual bool ready() const noexcept override { return pop<bool>(); }

    virtual Error verify() noexcept override { return pop<Error>(); }

    virtual Error fixed_verify() noexcept { return pop<Error>(); }

    virtual Error reset(bool) noexcept override  { return pop<Error>(); }

    virtual void ntoh_virt() noexcept override {}

    virtual void hton_virt() noexcept override {}

    virtual Error sec_update() noexcept override  { return pop<Error>(); }

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

    static void hton_fields(Fields*) noexcept {}

};

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__AUTH_BLOCK_H_
