//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/pkg/bin/block/ucm/lib/pkg/bin/block.h
/// @brief        UT mock for SWP base block
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__BLOCK_H_


#include "ucm/lib/buf/model.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/buf/iterator.h"

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/types.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

class Block : virtual protected ucm::mock::Sequence
{
protected:
    using Buffer        = lib::buf::Model;
    using ErrorValue    = lib::pkg::bin::ErrorValue;
    using iofile_offset = lib::pkg::bin::iofile_offset;
    using memory_offset = lib::pkg::bin::memory_offset;

public:

    constexpr static size_t fixed_size()  noexcept { return 0; }
    constexpr static size_t float_size()  noexcept { return 0; }
    constexpr static size_t total_size()  noexcept { return 0; }
    constexpr static size_t fields_size() noexcept { return 0; }

    explicit Block(Buffer& buffer) noexcept
        : buffer_{buffer}
    {}

    Block(Block     &&) = default;
    Block(Block const&) = delete;

    Block& operator=(Block     &&) = default;
    Block& operator=(Block const&) = delete;

    virtual ~Block() = default;

    void clear() noexcept {}

    Buffer& buffer() noexcept { return buffer_; }

    Error load_fixed(utl::FileIO&) noexcept
    { return pop<Error>(); }

    Error load_float(utl::FileIO&) noexcept
    { return pop<Error>(); }

    Error load(utl::FileIO&) noexcept
    { return pop<Error>(); }

    Error save_float(utl::FileIO&) noexcept
    { return pop<Error>(); }

    Error save(utl::FileIO&) noexcept
    { return pop<Error>(); }

    virtual std::size_t write(const void *, std::size_t) noexcept
    { return pop<std::size_t>(); }

    virtual bool ready() const noexcept
    { return pop<bool>(); }

    virtual Error verify() noexcept
    { return pop<Error>(); }

    virtual Error fixed_verify() noexcept
    { return pop<Error>(); }

    virtual Error reset(bool) noexcept
    { return pop<Error>(); }

    virtual void ntoh_virt() noexcept {}
    virtual void hton_virt() noexcept {}

    virtual Error sec_update() noexcept = 0;

    virtual std::size_t blk_fixed_size() const noexcept = 0;
    virtual std::size_t blk_float_size() const noexcept = 0;
    virtual std::size_t blk_total_size() const noexcept = 0;
    virtual std::size_t fld_float_size() const noexcept = 0;

protected:
    Buffer& buffer_; ///< Reference to the associated with the Block Buffer
                     ///< object.
};


}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__BLOCK_H_
