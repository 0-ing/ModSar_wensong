//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/error.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC__ERROR_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC__ERROR_H_

#include <string>
#include <exception>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/types.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class Error : public std::exception
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc__Error, CTor1);
    FRIEND_TEST(Test_ucm_lib_swc__Error, CTor2);
    FRIEND_TEST(Test_ucm_lib_swc__Error, CTor3);
    FRIEND_TEST(Test_ucm_lib_swc__Error, CTor4);
#endif

public:

    explicit Error(std::string&&)
        noexcept(std::is_nothrow_constructible<astate_type>::value &&
                 std::is_nothrow_constructible<aerror_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value);

    explicit Error(const std::string&)
        noexcept(std::is_nothrow_constructible<astate_type>::value &&
                 std::is_nothrow_constructible<aerror_type>::value &&
                 std::is_nothrow_copy_constructible<std::string>::value);

    explicit Error(const astate_type&, const aerror_type&, std::string&&)
        noexcept(std::is_nothrow_copy_constructible<astate_type>::value &&
                 std::is_nothrow_copy_constructible<aerror_type>::value &&
                 std::is_nothrow_move_constructible<std::string>::value);

    explicit Error(const astate_type&, const aerror_type&, const std::string&)
        noexcept(std::is_nothrow_copy_constructible<astate_type>::value &&
                 std::is_nothrow_copy_constructible<aerror_type>::value &&
                 std::is_nothrow_copy_constructible<std::string>::value);

    virtual const char* what() const noexcept override;

    virtual ~Error() = default;

private:
    std::string text_{};
    astate_type astate_{};
    aerror_type aerror_{};
};


}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC__ERROR_H_
