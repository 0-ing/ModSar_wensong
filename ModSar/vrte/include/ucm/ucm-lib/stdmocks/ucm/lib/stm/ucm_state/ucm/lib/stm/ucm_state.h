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

#include "ucm/lib/types.h"
#include "ucm/lib/log/logger.h"
#include "ucm/lib/utl/observer.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

class UCM_State final
    : public utl::ObserverSubject<ara::ARATypes::PackageManagerStatusType>
    , virtual protected ucm::mock::Sequence
{

public:
    using state_type = ara::ARATypes::PackageManagerStatusType;

    static const char *state_type_cstr(const state_type&) noexcept {
        return pop<const char *>();
    }

    explicit UCM_State()
        : utl::ObserverSubject<state_type>(UCM_State::state_type::kIdle) {}

    UCM_State(UCM_State     &&) = delete;
    UCM_State(UCM_State const&) = delete;

    UCM_State& operator=(UCM_State     &&) = delete;
    UCM_State& operator=(UCM_State const&) = delete;

    virtual ~UCM_State() = default;

    void set_state(const state_type&) noexcept {}

    state_type get_state() const noexcept { return pop<state_type>(); }
};

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_UCM_LIB_STM__UCM_STATE_H_
