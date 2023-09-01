//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/ucm_state.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_STM__UCM_STATE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_STM__UCM_STATE_H_

#include <mutex>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/utl/observer.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

class UCM_State final
    : public utl::ObserverSubject<ara::ARATypes::PackageManagerStatusType>
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_stm__UCM_State, CTor);
    FRIEND_TEST(Test_ucm_lib_stm__UCM_State, SetState);
    FRIEND_TEST(Test_ucm_lib_stm__UCM_State, StateTypeCstr);
#endif

public:
    using state_type = ara::ARATypes::PackageManagerStatusType;

    static const char *state_type_cstr(const state_type&);

    explicit UCM_State();

    UCM_State(UCM_State     &&) = delete;
    UCM_State(UCM_State const&) = delete;

    UCM_State& operator=(UCM_State     &&) = delete;
    UCM_State& operator=(UCM_State const&) = delete;

    ~UCM_State() = default;

    void set_state(const state_type&) noexcept;

    state_type get_state() const noexcept;
};

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_UCM_LIB_STM__UCM_STATE_H_
