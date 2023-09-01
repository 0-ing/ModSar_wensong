//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/thread_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_THREAD_FACTORY_H_
#define UCM_AAP_LIBRARY_LIB_UTL_THREAD_FACTORY_H_

#include <string>
#include <thread>
#include <atomic>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


#include "ucm/lib/utl/thread_handle.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class ThreadFactory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_ThreadFactory, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_ThreadFactory, CreateThread);
#endif

public:
    explicit ThreadFactory() noexcept = default;

    // copy semantics
    ThreadFactory(const ThreadFactory&) = default;
    ThreadFactory& operator=(const ThreadFactory&) = default;

    // move semantic
    ThreadFactory(ThreadFactory&&) noexcept = default;
    ThreadFactory& operator=(ThreadFactory&&) = default;

    virtual ~ThreadFactory() = default;

    virtual std::unique_ptr<ThreadHandle>
    create_handle(const ThreadAttr&) noexcept = 0;
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_THREAD_FACTORY_H_
