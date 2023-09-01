//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/utl/thread_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_APP_UTL_THREAD_FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY_APP_UTL_THREAD_FACTORY_IMPL_H_

#include <string>
#include <thread>
#include <atomic>
#include <functional>

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/thread_factory.h"
#include "ucm/app/utl/thread_handle_impl.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace utl {

class ThreadFactoryImpl
        : public lib::utl::ThreadFactory
        , virtual protected ucm::mock::Sequence
{
public:
    explicit ThreadFactoryImpl() noexcept = default;

    // copy semantics
    ThreadFactoryImpl(const ThreadFactoryImpl&) = default;
    ThreadFactoryImpl& operator=(const ThreadFactoryImpl&) = default;

    // move semantic
    ThreadFactoryImpl(ThreadFactoryImpl&&) noexcept = default;
    ThreadFactoryImpl& operator=(ThreadFactoryImpl&&) = default;

    virtual ~ThreadFactoryImpl() = default;

    virtual std::unique_ptr<lib::utl::ThreadHandle>
    create_handle(const lib::utl::ThreadAttr&) noexcept override { return pop<std::unique_ptr<lib::utl::ThreadHandle>&&>(); }
};


}    // namespace utl
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_APP_UTL_THREAD_FACTORY_IMPL_H_
