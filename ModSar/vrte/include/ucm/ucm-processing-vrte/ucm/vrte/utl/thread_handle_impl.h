//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/utl/thread_handle_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_utl

#ifndef UCM_AAP_PROCESSING_VRTE_UTL_THREAD_HANDLE_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_UTL_THREAD_HANDLE_IMPL_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


#include "ucm/vrte/utl/exm_include.h"
#include "ucm/lib/utl/thread_handle.h"

/// @addtogroup bosch_vrte_ucm_vrte_utl
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {
namespace utl {

/// @brief Thread handling utility implementation.
///

class ThreadHandleImpl : public lib::utl::ThreadHandle
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_vrte_utl_ThreadHandleImpl, CTor);
    FRIEND_TEST(Test_ucm_vrte_utl_ThreadHandleImpl, Join);
    FRIEND_TEST(Test_ucm_vrte_utl_ThreadHandleImpl, Spawn);
#endif

public:
    explicit ThreadHandleImpl(const lib::utl::ThreadAttr&);

    // copy semantics
    ThreadHandleImpl(const ThreadHandleImpl&) = delete;
    ThreadHandleImpl& operator=(const ThreadHandleImpl&) = delete;

    // move semantic
    ThreadHandleImpl(ThreadHandleImpl&&) = delete;
    ThreadHandleImpl& operator=(ThreadHandleImpl&&) = delete;

    virtual ~ThreadHandleImpl() = default;

    /// @brief EXM thread join
    /// @param [IN] None
    /// @param [OUT] None
    /// @return void
    virtual void join() noexcept override;

    /// @brief Spawn ExM controlled thread
    /// @param [IN] Call back function of type: std::function
    /// @return void
    virtual void spawn(callback_type&&) noexcept override;

private:
    callback_type callback_{};
    std::unique_ptr<bosch::vrte::exm::Thread> exmthread_{};
};

}    // namespace utl
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE_UTL_THREAD_HANDLE_IMPL_H_
