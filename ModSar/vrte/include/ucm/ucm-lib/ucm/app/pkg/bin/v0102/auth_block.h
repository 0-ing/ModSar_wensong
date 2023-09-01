//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v0102/auth_block.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__AUTH_BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__AUTH_BLOCK_H_

#include <array>
#include <cstddef>
#include <cstdint>

#include "ucm/lib/utl/cpputils.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

/// @class AuthBlock
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102
/// @brief AuthBlock implementation.

class AuthBlock final : public v01xx::AuthBlock
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, Ready);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, Reset);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, Verify);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, SecUpdate);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, VerifySelf);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, FixedVerify);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v0102__AuthBlock, FixedVerifySelf);
#endif

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

    /// @brief Create an authentication tag.
    ///
    /// The authentication tag is created for vendor=0x0000 and format=0x0102.
    ///
    /// @returns A constructed authentication tag.
    /// @throws std::runtime_error if no mapping is possible.
    ///
    static AuthBlock create(Context_Ptr ctx, Buffer&);

    /// @brief Construction as authentication tag copying the Fields.
    ///
    /// @param[in] buff Buffer to map the Fields on.
    /// @throws std::runtime_error if no fields mapping is possible.
    ///
    explicit AuthBlock(Context_Ptr ctx, Buffer&, bool alloc);

    explicit AuthBlock(Context_Ptr ctx, Buffer&, const Fields&,
                       const Base::Fields&, const Root::Fields&);

    AuthBlock(AuthBlock     &&) = default;
    AuthBlock(AuthBlock const&) = delete;

    AuthBlock& operator=(AuthBlock     &&) = delete;
    AuthBlock& operator=(AuthBlock const&) = delete;

    virtual ~AuthBlock() = default;

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
    static Fields* mapcur(Buffer&);
    static Fields* mapmem(Buffer&);

private:
    Fields* fields_;
    Context_Ptr context_;

    void ntoh_self() noexcept;
    void hton_self() noexcept;

    Error hash_block(hash_buff_t&) noexcept;

    Error verify_self() noexcept;

    Error fixed_verify_self() const noexcept;
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


}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__AUTH_BLOCK_H_
