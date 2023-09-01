//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/utl/thread_handle_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_utl

#ifndef UCM_AAP_LIBRARY_APP_UTL_THREAD_HANDLE_IMPL_H_
#define UCM_AAP_LIBRARY_APP_UTL_THREAD_HANDLE_IMPL_H_

#include <thread>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


#include "ucm/lib/utl/thread_handle.h"

/// @addtogroup bosch_vrte_ucm_app_utl
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace utl {

/// @class ThreadHandleImpl
/// @ingroup bosch_vrte_ucm_app_utl
/// @brief Provide default implementation of ThreadHandle.
/// 

class ThreadHandleImpl : public lib::utl::ThreadHandle
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_app_utl_ThreadHandleImpl, CTor);
    FRIEND_TEST(Test_ucm_app_utl_ThreadHandleImpl, Join);
    FRIEND_TEST(Test_ucm_app_utl_ThreadHandleImpl, Spawn);
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

    virtual void join() noexcept override;

    virtual void spawn(callback_type&&) noexcept override;

private:
    std::thread cppthread_{};
};

}    // namespace utl
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY_APP_UTL_THREAD_HANDLE_IMPL_H_
