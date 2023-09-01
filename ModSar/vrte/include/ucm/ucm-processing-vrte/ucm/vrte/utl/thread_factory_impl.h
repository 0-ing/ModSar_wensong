//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/utl/thread_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_utl

#ifndef UCM_AAP_PROCESSING_VRTE_UTL_THREAD_FACTORY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_UTL_THREAD_FACTORY_IMPL_H_

#include <string>
#include <thread>
#include <atomic>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/thread_factory.h"
#include "ucm/vrte/utl/thread_handle_impl.h"

/// @addtogroup bosch_vrte_ucm_vrte_utl
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {
namespace utl {

/// @brief Thread factory utility implementation.
///

class ThreadFactoryImpl : public lib::utl::ThreadFactory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_vrte_utl_ThreadFactoryImpl, CTor);
    FRIEND_TEST(Test_ucm_vrte_utl_ThreadFactoryImpl, CreateHandle);
#endif

public:
    explicit ThreadFactoryImpl() noexcept = default;

    // copy semantics
    ThreadFactoryImpl(const ThreadFactoryImpl&) = default;
    ThreadFactoryImpl& operator=(const ThreadFactoryImpl&) = default;

    // move semantic
    ThreadFactoryImpl(ThreadFactoryImpl&&) noexcept = default;
    ThreadFactoryImpl& operator=(ThreadFactoryImpl&&) = default;

    virtual ~ThreadFactoryImpl() = default;

    /// @brief Create Thread Handle
    /// @param [IN] Attributes of type lib::utl::ThreadAttr
    /// @return Unique ptr to a thread handle
    virtual std::unique_ptr<lib::utl::ThreadHandle>
    create_handle(const lib::utl::ThreadAttr&) noexcept override;
};


}    // namespace utl
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE_UTL_THREAD_FACTORY_IMPL_H_
