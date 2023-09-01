//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/syserror.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_SYSERROR_H_
#define UCM_AAP_LIBRARY_LIB_UTL_SYSERROR_H_

#include <string>
#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class SysError final
      : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_SysError, CTor);
#endif

public:
    static std::string strerror(int) noexcept { return pop<std::string>(); }

    SysError() = default;
    SysError(int error)
    : errnum_{error}
    , errstr_(std::move(SysError::strerror(error)))
    {

    }

    // copy semantics
    SysError(const SysError&) = default;
    SysError& operator=(const SysError&) = default;

    // move semantic
    SysError(SysError&&) noexcept = default;
    SysError& operator=(SysError&&) = default;

    ~SysError() = default;

    void seterror(int) noexcept { pop<void>();}

    int errnum() const noexcept;

    const std::string& errstr() const noexcept;

private:
    int errnum_{0};
    std::string errstr_{};
};

inline int SysError::errnum() const noexcept
{
    return pop<int>();
}

inline const std::string& SysError::errstr() const noexcept
{
    return pop<std::string const&>();
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UTL_SYSERROR_H_
