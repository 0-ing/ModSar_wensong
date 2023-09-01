//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/instance.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_INSTANCE_H_
#define UCM_AAP_LIBRARY_LIB_PPL_INSTANCE_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/worker.h"
#include "ucm/lib/utl/object_locker.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Instance final : public utl::ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, CTor);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, Flush);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, Reset);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, Write1);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, Write2);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, Worker);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, Terminate);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, WorkerCreate);
    FRIEND_TEST(Test_ucm_lib_ppl_Instance, TerminateWait);
#endif

public:

    explicit Instance(std::size_t nelem, std::size_t esize) noexcept;

    // copy semantics
    Instance(const Instance& other) = delete;
    Instance& operator=(const Instance&) = delete;

    // move semantic
    Instance(Instance&&) noexcept = delete;
    Instance& operator=(Instance&&) = delete;

    ~Instance();

    void flush() noexcept;

    void reset() noexcept;

    void terminate(const Signal::Command&) noexcept;

    void terminate_wait() noexcept;

    void write(Signal&&) noexcept;

    void write(const void *buff, std::size_t size) noexcept;

    std::shared_ptr<Worker> worker(std::size_t);

    std::shared_ptr<Worker> worker_create(const std::string& name);

private:
    Tag tag_{};
    Token* token_{nullptr};
    std::shared_ptr<Bucket> bucket_;
    std::vector<std::shared_ptr<Worker>> workers_{};
};

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_INSTANCE_H_
