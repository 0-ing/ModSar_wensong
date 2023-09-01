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

#include "ucm/lib/utl/cpputils.h"
#include "ucm/app/pkg/bin/context.h"
#include "ucm/lib/pkg/bin/auth_block.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

/// @class AuthBlock
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v01xx
/// @brief AuthBlock implementation.

class AuthBlock : public lib::pkg::bin::AuthBlock
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__AuthBlock, CTor);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__AuthBlock, Reset);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__AuthBlock, Verify);
    FRIEND_TEST(Test__ucm_app_pkg_bin_v01xx__AuthBlock, FixedVerify);
#endif

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
    /// @brief A packed structure representing the version specific part of the
    /// authentication tag without security data.
    struct Fields
    {
        uint16_t bht_;         ///< Block hash type
        uint16_t bss_;         ///< Block signature size
        uint64_t sdp_;         ///< Security data padding
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

    /// @brief Create an authentication tag for format.
    ///
    /// Construct an authentication tag for vendor=0x000 and format=0x01xx.
    ///
    /// @param[in] format The container format version.
    /// @returns A constructed authentication tag.
    /// @throws std::runtime_error if no mapping is possible.
    ///
    static AuthBlock create(Buffer& buff, uint32_t format);

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
    /// @param[in] bfields Variable to copy the Base::Fields from.
    /// @throws std::runtime_error if no mapping is possible.
    ///
    /// @note The size of the underlying buffer is increased by fields_size(),
    /// for every constructor of the base classes.
    ///
    explicit AuthBlock(Buffer& buff,
                     const Fields& fields,
                     const Base::Fields& bfields);

    AuthBlock(AuthBlock     &&) = default;
    AuthBlock(AuthBlock const&) = delete;

    AuthBlock& operator=(AuthBlock     &&) = delete;
    AuthBlock& operator=(AuthBlock const&) = delete;

    virtual ~AuthBlock() = default;

    uint16_t field_htype() const noexcept;
    uint16_t field_ssize() const noexcept;
    uint64_t field_sdpad() const noexcept;

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

    static void hton_fields(Fields*) noexcept;

private:
    Fields* fields_;

    Error verify_self() const noexcept;

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

inline uint16_t AuthBlock::field_htype() const noexcept
{
    return lib::utl::ntoh(fields_->bht_);
}

inline uint16_t AuthBlock::field_ssize() const noexcept
{
    return lib::utl::ntoh(fields_->bss_);
}

inline uint64_t AuthBlock::field_sdpad() const noexcept
{
    return lib::utl::ntoh(fields_->sdp_);
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
