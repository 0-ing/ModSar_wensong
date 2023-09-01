//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/thread_attr.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_THREAD_ATTR_H_
#define UCM_AAP_LIBRARY_LIB_UTL_THREAD_ATTR_H_

#include <string>
#include <thread>
#include <atomic>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/syserror.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class ThreadAttr final
      : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_ThreadAttr, CTor);
#endif

public:
    constexpr static int invalid_prio =
            std::numeric_limits<int>::max();

    explicit ThreadAttr(const std::string& name, const std::string& attr)
             : ThreadAttr(name, attr, ThreadAttr::invalid_prio)
    {
      
    }

    explicit ThreadAttr(const std::string& name, const std::string& attr, int prio)
             : prio_{prio}
             , attr_{attr}
             , name_{name}
    {
        
    }

    explicit ThreadAttr(std::string&& name, std::string&& attr) noexcept
             : ThreadAttr(std::move(name), std::move(attr), ThreadAttr::invalid_prio)
    {
        
    }

    explicit ThreadAttr(std::string&& name, std::string&& attr, int prio) noexcept
             : prio_{prio}
             , attr_(std::move(attr))
             , name_(std::move(name))
    {
        
    }

    // copy semantics
    ThreadAttr(const ThreadAttr&) = default;
    ThreadAttr& operator=(const ThreadAttr&) = default;

    // move semantic
    ThreadAttr(ThreadAttr&&) noexcept = default;
    ThreadAttr& operator=(ThreadAttr&&) = default;

    ~ThreadAttr() = default;

    const auto& prio() const noexcept;
    const auto& attr() const noexcept;
    const auto& name() const noexcept;

private:
    int prio_;
    std::string attr_;
    std::string name_;
};

inline const auto& ThreadAttr::prio() const noexcept
{
    return pop<int const&>();
}

inline const auto& ThreadAttr::attr() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& ThreadAttr::name() const noexcept
{
    return pop<std::string const&>();
}


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_THREAD_ATTR_H_
