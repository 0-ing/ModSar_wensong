//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/block.h
/// @brief        Base functionality for the SWP related block operations.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__BLOCK_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__BLOCK_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/buf/model.h"
#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/buf/iterator.h"

#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/types.h"


/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

/// @class Block block.h ucm/lib/pkg/bin/block.h
/// @ingroup bosch_vrte_ucm_lib_pkg_bin
/// @brief A model of the basic SWP data block.
///
/// The SWP processing/composition facility recognises two types of blocks :
/// DataBlock and AuthBlock. The AuthBlock is used to identify the SWP structure
/// and bootstrap the security mechanism related with verifying authenticity of
/// each DataBlock in the SWP. There is only one AuthBlock per SWP.
/// The DataBlock(s) carry the payload associated with the SWP - internal
/// information structures and artefacts (manifes, update artefacts).
///
/// The Class defines the API of the basic functionality required by a SWP
/// block. A SWP block binds together a memory buffer (buf::Model), some fixed
/// size fields structure (header) and variable size data (payload) together.
///
class Block
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Block, TEST__CTor);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Block, TEST__Write);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Block, TEST__Load);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Block, TEST__Save);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Block, TEST__LoadFixed);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Block, TEST__LoadFloat);
    FRIEND_TEST(Test__ucm_lib_pkg_bin__Block, TEST__SaveFloat);
#endif

protected:
    using Buffer        = lib::buf::Model;
    using ErrorValue    = lib::pkg::bin::ErrorValue;
    using iofile_offset = lib::pkg::bin::iofile_offset;
    using memory_offset = lib::pkg::bin::memory_offset;

public:

    /// @brief Returns the size of the associated Fields.
    ///
    /// @return The method always returns '0;
    ///
    constexpr static size_t fields_size() noexcept;

    /// @brief Recursively returns the size of the associated Fields.
    ///
    /// @return The method always returns '0;
    ///
    constexpr static size_t fixed_size() noexcept;

    /// @brief Returns the size of the non-fixed length data.
    ///
    /// @return The method always returns '0'
    ///
    constexpr static size_t float_size() noexcept;

    /// @brief Returns the total size of the block.
    ///
    /// @return The method always returns '0'
    ///
    constexpr static size_t total_size() noexcept;


    /// @brief Construct a Block and associate a Buffer with it.
    ///
    /// @test A test case checking if the stored Buffer reference is the same as
    /// the Buffer passed to the constructor.
    ///
    explicit Block(Buffer&) noexcept;

    Block(Block     &&) = default;
    Block(Block const&) = delete;

    Block& operator=(Block     &&) = delete;
    Block& operator=(Block const&) = delete;

    virtual ~Block() = default;

    /// @brief Clears the content of the associated buffer.
    ///
    /// @test A test case checking all the memory segments of the underlying
    /// buffer are set to '0'.
    ///
    void clear() noexcept;

    /// @brief Return the Buffer associated with he Block.
    ///
    /// @test A test case checking if the returned Buffer is the same as
    /// the Buffer passed at object construction time.
    ///
    Buffer& buffer() noexcept;

    /// @brief Load and verify the Block preamble from a file.
    ///
    /// The method tries to load blk_fixed_size() bytes from a file.
    /// If the preamble is loaded return the result of fixed_verify().
    ///
    /// @param[in] fio An open utl::FileIO descriptor.
    /// @returns An error value associated with the operation.
    ///
    /// @note The method expects that the data is in network byte order.
    ///
    Error load_fixed(utl::FileIO& fio) noexcept;

    /// @brief Load and verify the Block non-fixed data.
    ///
    /// @param[in] fio An open utl::FileIO descriptor.
    /// @returns An error value associated with the operation.
    ///
    Error load_float(utl::FileIO& fio) noexcept;

    /// @brief Attempt to load and verify a complete block of data.
    ///
    /// @param[in] fio An open utl::FileIO descriptor.
    /// @returns An error value associated with the operation.
    ///
    /// @note The method expects that the header data is in network byte order.
    ///
    Error load(utl::FileIO& fio) noexcept;

    /// @brief Save the Block non-fixed data to a file.
    ///
    /// @param[in] fio An open utl::FileIO descriptor.
    /// @returns An error value associated with the operation.
    ///
    Error save_float(utl::FileIO& fio) noexcept;

    /// @brief Save the complete Block to a file.
    ///
    /// @param[in] fio An open utl::FileIO descriptor.
    /// @returns An error value associated with the operation.
    ///
    Error save(utl::FileIO& fio) noexcept;

    /// @brief Write no more than size bytes to the underlying buffer.
    ///
    /// @param[in] data Pointer to the external data block.
    /// @param[in] size Size of the external data block.
    /// @retval Number of bytes actually written.
    ///
    virtual std::size_t write(const void *data, std::size_t size) noexcept;

    /// @brief Check if the Block loading into the buffer is complete.
    ///
    /// @return true,  if the Block is logically complete.
    /// @return false, if there is not enough data in the Buffer, to form a
    /// logically complete block.
    ///
    /// @note This class implementation always returns true.
    ///
    virtual bool ready() const noexcept;

    /// @brief Verify the integrity of the buffer.
    ///
    /// @returns The method returns an object of type Error, holding the
    /// effective error code and the source location which detected the error.
    /// On success the Error == ErrorValue::kSuccess.
    ///
    /// @note This class implementation merely returns
    /// Error{ErrorValue::kSuccess}.
    ///
    virtual Error verify() noexcept;

    /// @brief Verify the integrity of the fixed part of the block
    /// (i.e. the header).
    ///
    /// @returns The method returns an object of type Error, holding the
    /// effective error code and the source location which detected the error.
    /// On success the Error == ErrorValue::kSuccess.
    ///
    /// @note This class implementation merely returns
    /// Error{ErrorValue::kSuccess}.
    ///
    virtual Error fixed_verify() noexcept;

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
    virtual Error reset(bool alloc) noexcept;

    /// @brief Perform a network to host byte order conversion of the block.
    ///
    virtual void ntoh_virt() noexcept;

    /// @brief Perform a host to network byte order conversion of the block.
    ///
    virtual void hton_virt() noexcept;

    /// @brief Update the authentication data for the block.
    ///
    virtual Error sec_update() noexcept = 0;

    /// @brief Return the size of the block preamble.
    ///
    virtual std::size_t blk_fixed_size() const noexcept = 0;

    /// @brief Return the maximum data size of the block.
    ///
    virtual std::size_t blk_float_size() const noexcept = 0;

    /// @brief Return the maximum total size of the block.
    ///
    virtual std::size_t blk_total_size() const noexcept = 0;

    /// @brief Return the computed data size of the block.
    ///
    virtual std::size_t fld_float_size() const noexcept = 0;

protected:
    Buffer& buffer_; ///< Reference to the associated with the Block Buffer
                     ///< object.
};

inline constexpr size_t Block::fields_size() noexcept
{
    return 0;
}

inline constexpr size_t Block::fixed_size() noexcept
{
    return fields_size();
}

inline constexpr size_t Block::float_size() noexcept
{
    return 0;
}

inline constexpr size_t Block::total_size() noexcept
{
    return 0;
}

inline void Block::clear() noexcept
{
    buffer_.clear();
}

inline Block::Buffer& Block::buffer() noexcept
{
    return buffer_;
}

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__BLOCK_H_
