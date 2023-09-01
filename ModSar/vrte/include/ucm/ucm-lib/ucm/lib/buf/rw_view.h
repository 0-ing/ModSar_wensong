//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/buf/rw_view.h
/// @brief        Read/Write buffer view implementation.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_lib_buf

#ifndef UCM_AAP_LIBRARY__UCM_LIB_BUF__RW_VIEW_H_
#define UCM_AAP_LIBRARY__UCM_LIB_BUF__RW_VIEW_H_

#if defined(GOOGLE_TEST)
#include <gtest/gtest_prod.h>
#endif

#include "ucm/lib/buf/view.h"


/// @addtogroup bosch_vrte_ucm_lib_buf
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace buf   {

/// @class RW_View rw_view.h ucm/lib/buf/rw_view.h
/// @ingroup bosch_vrte_ucm_lib_buf
/// @brief Read/Write buffer view class.
///
/// The class defines a set of operations on a contiguous region of memory
/// possibly part of a UCM memory buffer. This level of abstraction is required
/// since UCM memory buffers are not necessarily contiguous - i.e. they can be
/// a set of disjoint memory chunks.
/// The operations defined by the class include:
/// - file to memory
/// - memory to file
/// - memory to memory
///
/// The memory managed by the buffer view should not be manipulated directly
/// (i.e. via a pointer), but for safety reasons always via the public API
/// provided by the class.
///
class RW_View final : public View
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, CTor);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Save1);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Save2);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Save3);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Load1);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Fill1);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, MapMem);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, MapCur);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Write1);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Write2);
    FRIEND_TEST(Test__ucm_lib_buf__RW_View, Write3);
#endif

public:
    /// @brief Construct a read-only View for a memory region.
    ///
    /// @param[in] arena The start of the controlled memory region.
    /// @param[in] msize Size of the controlled memory region.
    /// @param[in] csize Current size of the data in the memory region.
    ///
    /// @note arena parameter is consumed by the constructor itself, the
    /// rest is passed to the base class constructor.
    ///
    explicit RW_View(void *arena,
                     std::size_t msize,
                     std::size_t csize) noexcept;

    /// @brief Construct a buffer RW_View with invalid memory region.
    ///
    /// @note all unreferenced member variables are set to 0.
    ///
    RW_View() noexcept = default;

    RW_View(RW_View     &&) = default;
    RW_View(RW_View const&) = default;

    RW_View& operator=(RW_View     &&) = default;
    RW_View& operator=(RW_View const&) = delete;

    ~RW_View() = default;

protected:
    void* mregion() & noexcept override;

    const void* mregion() const & noexcept override;


private:
    void* mregion_{nullptr};
};


}    // namespace buf
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_BUF__RW_VIEW_H_
