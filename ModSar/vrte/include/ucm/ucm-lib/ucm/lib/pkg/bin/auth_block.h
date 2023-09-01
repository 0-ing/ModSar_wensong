//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/auth_block.h
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
#include "ucm/lib/utl/cpputils.h"
#include "ucm/lib/log/ref_logger.h"

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/block.h"

/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

/// @class AuthBlock auth_block.h ucm/lib/pkg/bin/auth_block.h
/// @ingroup bosch_vrte_ucm_lib_pkg_bin
/// @brief A model of the basic authentication tag.
///
/// The basic authentication tag represents the preamble of the authentication
/// tag block. This preamble is defined by the specification that will never
/// change its structure with future versions of the SWP format - i.e. it will
/// stay the same. The AuthBlock::Fields structure defines its format.
///
class AuthBlock : public Block
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__Const);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__Ready);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__Verify);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__Create);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__VerifySelf);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__FixedVerify);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__AuthBlock, TEST__FixedVerifySelf);
#endif

    using Base = Block;

public:
    /// @struct AuthBlock::Fields auth_block.h ucm/lib/pkg/bin/auth_block.h
    /// @brief A packed structure representing the preamble of the
    /// authentication tag.
    ///
    struct Fields
    {
        uint64_t  swps_;           ///< total SWP size
        uint32_t  cfmt_;           ///< container format version
        uint32_t  tags_;           ///< Authentication tag size
        uint32_t  vtag_;           ///< vendor tag
    } __attribute__((packed));

    /// @brief Returns the size of the associated Fields.
    ///
    /// @return sizeof(Fields)
    ///
    constexpr static size_t fields_size() noexcept;

    /// @brief Recursively returns the size of the associated Fields.
    ///
    /// @return fields_size() + Base::fixed_size()
    ///
    constexpr static size_t fixed_size() noexcept;

    /// @brief Returns the size of the non-fixed length data.
    ///
    /// @return The method always returns '0'
    ///
    constexpr static size_t float_size() noexcept;

    /// @brief Returns the total size of the block.
    ///
    /// @return fixed_size() + float_size()
    ///
    constexpr static size_t total_size() noexcept;

    /// @brief Create an authentication tag for vendor and format.
    ///
    /// @param[in] vendor The vendor tag field.
    /// @param[in] format The container format version.
    /// @returns A constructed authentication tag.
    /// @throws std::runtime_error if no mapping is possible.
    ///
    static AuthBlock create(Buffer& buff, uint32_t vendor, uint32_t format);

    /// @brief Construction as authentication tag copying the Fields.
    ///
    /// @param[in] buff Buffer to map the Fields on.
    /// @throws std::runtime_error if no fields mapping is possible.
    ///
    explicit AuthBlock(Buffer& buff, bool alloc);

    /// @brief Construction as authentication tag copying the Fields.
    ///
    /// @param[in] buff Buffer to map the Fields on.
    /// @param[in] fields Variable to copy the AuthBlock fields from.
    /// @throws std::runtime_error if no mapping is possible.
    ///
    /// @note The size of the underlying buffer is increased by fields_size(),
    /// for every constructor of the base classes.
    ///
    explicit AuthBlock(Buffer& buff, const Fields&);

    AuthBlock(AuthBlock     &&) = default;
    AuthBlock(AuthBlock const&) = delete;

    AuthBlock& operator=(AuthBlock     &&) = delete;
    AuthBlock& operator=(AuthBlock const&) = delete;

    virtual ~AuthBlock() = default;

    /// @brief Read accessor for Fields::swps_
    ///
    uint64_t field_swps() const noexcept;

    /// @brief Read accessor for Fields::tags_
    ///
    uint32_t field_tags() const noexcept;

    /// @brief Read accessor for Fields::vtag_
    ///
    uint32_t field_vtag() const noexcept;

    /// @brief Read accessor for Fields::cfmt
    ///
    uint32_t field_cfmt() const noexcept;

    /// @brief Write accessor for Fields::swps_
    ///
    void field_swps(uint64_t value) noexcept;

    /// @brief Write accessor for Fields::tags_
    ///
    void field_tags(uint32_t value) noexcept;

    /// @brief Write accessor for Fields::vtag_
    ///
    void field_vtag(uint32_t value) noexcept;

    /// @brief Write accessor for Fields::cfmt_
    ///
    void field_cfmt(uint32_t value) noexcept;

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

    static void hton_fields(Fields*) noexcept;

private:
    Fields* fields_;

    Error verify_self() noexcept;

    Error fixed_verify_self() noexcept;
};

inline constexpr size_t AuthBlock::fields_size() noexcept
{
    return sizeof(Fields);
}

inline constexpr size_t AuthBlock::fixed_size() noexcept
{
    return Base::fixed_size() + fields_size();
}

inline constexpr size_t AuthBlock::float_size() noexcept
{
    return 0;
}

inline constexpr size_t AuthBlock::total_size() noexcept
{
    return fixed_size() + float_size();
}

inline uint64_t AuthBlock::field_swps() const noexcept
{
    return utl::ntoh(fields_->swps_);
}

inline uint32_t AuthBlock::field_tags() const noexcept
{
    return utl::ntoh(fields_->tags_);
}

inline uint32_t AuthBlock::field_vtag() const noexcept
{
    return utl::ntoh(fields_->vtag_);
}

inline uint32_t AuthBlock::field_cfmt() const noexcept
{
    return utl::ntoh(fields_->cfmt_);
}

inline void AuthBlock::field_swps(uint64_t value) noexcept
{
    fields_->swps_ = utl::hton(value);
}

inline void AuthBlock::field_tags(uint32_t value) noexcept
{
    fields_->tags_ = utl::hton(value);
}

inline void AuthBlock::field_vtag(uint32_t value) noexcept
{
    fields_->vtag_ = utl::hton(value);
}

inline void AuthBlock::field_cfmt(uint32_t value) noexcept
{
    fields_->cfmt_ = utl::hton(value);
}

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__AUTH_BLOCK_H_
