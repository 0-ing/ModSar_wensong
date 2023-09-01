//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/frame.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_FRAME_H_
#define UCM_AAP_LIBRARY_LIB_PPL_FRAME_H_

#include <cstddef>
#include "ucm/mock/sequence.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Frame final
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Lib_Pipeline_Frame, Simple1);
    FRIEND_TEST(Test_Lib_Pipeline_Frame, Simple2);
    FRIEND_TEST(Test_Lib_Pipeline_Frame, UpdateCptr1);
    FRIEND_TEST(Test_Lib_Pipeline_Frame, UpdateCptr2);
    FRIEND_TEST(Test_Lib_Pipeline_Frame, UpdateVptr1);
    FRIEND_TEST(Test_Lib_Pipeline_Frame, UpdateVptr2);
    FRIEND_TEST(Test_Lib_Pipeline_Frame, UpdateVptr3);
#endif

public:
    Frame() noexcept = default;

    explicit Frame(void *vptr, std::size_t size) noexcept
    : fsize_{size}
    , vptr_{vptr}
    {
    }

    // copy semantics
    Frame(const Frame& other) = delete;
    Frame& operator=(const Frame&) = delete;

    // move semantic
    Frame(Frame&&) noexcept = default;
    Frame& operator=(Frame&&) = default;

    ~Frame() = default;

    /// @brief reset the frame, i.e. clear associated data
    void reset() noexcept { pop<void>(); }

    /// @brief return the size of the associated vptr_ buffer
    auto fsize() const noexcept;

    /// @brief return the size of the data the buffer carries
    /// @return vsize_ if vsize_ > 0
    /// @return csize_ othersize
    auto dsize() const noexcept;

    /// @brief return true if vsize_ >= fsize_
    auto full() const noexcept;

    /// @brief returns a pointer to the data the frame carries.
    /// @return vptr_ if vptr_ != nullptr and vsize_ > 0
    /// @return cptr_ otherwise
    const void* dptr() const noexcept;

    /// @brief returns a pointer to the vptr_buffer
    void* vptr() noexcept;

    /// @brief set the cptr_ = data and csize_ = size
    void cptr_reset(const void *data, std::size_t size) noexcept;

    /// @brief set the vsize_ = size
    void vsize_reset(std::size_t size) noexcept;

    /// @brief append the contents of data to vptr_ buffer
    /// @return the number of bytes written
    /// @throw std::runtime_error if data == nullptr
    /// @throw std::runtime_error if vptr_ == nullptr
    std::size_t vptr_append(const void *, std::size_t)
    {
        return pop<std::size_t>();
    }

    /// @brief Check if the frame may be discarded
    /// @return true if vptr_ == nullptr
    /// @return false otherwise
    auto may_discard() const noexcept;

private:
    std::size_t fsize_{0};       // Size of the frame
    std::size_t vsize_{0};       // Size of the stored data in vptr
    std::size_t csize_{0};       // Size of the stored data in cptr

    void *vptr_{nullptr};        // Pointer to the own buffer
    const void* cptr_{nullptr};  // Pointer to externally supplied data
};

inline auto Frame::fsize() const noexcept
{
    return pop<std::size_t>();
}

inline auto Frame::dsize() const noexcept
{
    return pop<std::size_t>();
}

inline auto Frame::full() const noexcept
{
    return pop<bool>();
}

inline const void* Frame::dptr() const noexcept
{
    return pop<void*>();
}

inline void* Frame::vptr() noexcept
{
    return pop<void*>();
}

inline void Frame::vsize_reset(std::size_t) noexcept
{
    pop<void>();
}

inline void Frame::cptr_reset(const void *, std::size_t) noexcept
{
    pop<void>();
}

inline auto Frame::may_discard() const noexcept
{
    return  pop<bool>();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_FRAME_H_
