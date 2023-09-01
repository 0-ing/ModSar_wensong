//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/thread_handle.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_THREAD_HANDLE_H_
#define UCM_AAP_LIBRARY_LIB_UTL_THREAD_HANDLE_H_

#include <string>
#include <thread>
#include <atomic>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/syserror.h"
#include "ucm/lib/utl/thread_attr.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class ThreadHandle
        : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_ThreadHandle, CTor);
#endif

public:
    using callback_type = std::function<void () noexcept>;

    explicit ThreadHandle(const ThreadAttr& attrs)
    : attrs_{attrs}
    {
        
    }

    // copy semantics
    ThreadHandle(const ThreadHandle&) = delete;
    ThreadHandle& operator=(const ThreadHandle&) = delete;

    // move semantic
    ThreadHandle(ThreadHandle&&) = delete;
    ThreadHandle& operator=(ThreadHandle&&) = delete;

    virtual ~ThreadHandle() = default;

    virtual void join() noexcept {}

    virtual void spawn(callback_type&&) noexcept {}

protected:
    const ThreadAttr& attrs_;
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_THREAD_HANDLE_H_
