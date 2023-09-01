//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/api/state_observer.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_UCM_ARA_API__STATE_OBSERVER_H_
#define UCM_AAP_PKGMANAGER_ARA_UCM_ARA_API__STATE_OBSERVER_H_

#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/stm/ucm_state.h"

/// @addtogroup bosch_vrte_ucm_ara_api
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace ara   {
namespace api   {

/// @class StateObserver
/// @ingroup bosch_vrte_ucm_ara_api
/// @brief ARA state observer.
///

class StateObserver
        : public ucm::lib::utl::ObserverClient<
          ucm::lib::stm::UCM_State::state_type>
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_ara_api__StateObserver, CTor);
#endif
public:
    /// Use STM state type from library
    using state_type = ucm::lib::stm::UCM_State::state_type;
    
    /// Default Constructor
    explicit StateObserver() = default;
    
    /// Parameterized constructor 
    explicit StateObserver(std::function<void(const state_type&)>&&)
        noexcept(std::is_nothrow_move_constructible<
                 std::function<void(const state_type&)>>::value         &&
                 std::is_nothrow_constructible<ucm::lib::utl::ObserverClient<
                 ucm::lib::stm::UCM_State::state_type>>::value);

    /// Copy Semantics
    StateObserver(StateObserver     &&) = default;
    
    /// Copy Semantics
    StateObserver(StateObserver const&) = default;

    /// Move Semantics
    StateObserver& operator=(StateObserver     &&) = default;
    
    /// Move Semantics
    StateObserver& operator=(StateObserver const&) = default;
    
    /// Default Destructor
    virtual ~StateObserver() = default;

    /// \brief State updater.
    /// \param [IN] state
    virtual void update(const state_type& state) noexcept override;

private:
    /// \brief General-purpose polymorphic function wrapper.
    /// \param [IN] state_type
    std::function<void(const state_type&)> callback_{};
};

}    // namespace api
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PKGMANAGER_ARA_UCM_ARA_API__STATE_OBSERVER_H_
