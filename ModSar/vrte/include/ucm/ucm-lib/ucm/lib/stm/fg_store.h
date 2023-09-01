//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/fg_store.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__FG_STORE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__FG_STORE_H_

#include <set>
#include <memory>
#include <unordered_map>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/stm/error.h"
#include "ucm/lib/stm/fg_entry.h"

/// @defgroup bosch_vrte_ucm_lib_stm__FG_Store__ut Function group store
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief Provides facility to store the FGs.
class FG_Store final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_stm__FG_Store, CTor);
    FRIEND_TEST(Test__ucm_lib_stm__FG_Store, IsStateAllowed);
    FRIEND_TEST(Test__ucm_lib_stm__FG_Store, InsertRemove);
    FRIEND_TEST(Test__ucm_lib_stm__FG_Store, RequestChange);
    FRIEND_TEST(Test__ucm_lib_stm__FG_Store, AckChange);
    FRIEND_TEST(Test__ucm_lib_stm__FG_Store, ClearChange);
#endif

public:
    /// @brief Create an instance of the class.
    /// @param astates A set with the allowed states.
    explicit FG_Store(std::set<FG_State>&& astates);

    FG_Store(FG_Store     &&) = delete;
    FG_Store(FG_Store const&) = delete;

    FG_Store& operator=(FG_Store     &&) = delete;
    FG_Store& operator=(FG_Store const&) = delete;

    ~FG_Store() = default;

    /// @brief Check if the state is a valid state for this FG_Store.
    ///
    /// @returns true if allowed
    /// @returns false if not allowed
    bool is_state_allowed(const FG_State& state) noexcept;

    /// @brief Try to insert a FG entry into the cache.
    ///
    /// @return true if entry has been inserted.
    /// @return false if an entry with the same FG_Ident is already in cache
    Error insert(FG_Ident&& ident, FG_State&& state) noexcept;

    /// @brief Try to remove a FG entry from the cache.
    ///
    /// @return FG_ErrorValue:: if entry has been removed.
    /// @return false if no such entry can be found
    Error remove(const FG_Ident&) noexcept;

    /// @brief Lookup an FG_Entry and return pointer to it.
    ///
    /// @param[in] ident FG ident
    /// @returns on success, non-owning pointer to the entry
    /// @returns on failure, nullptr - i.e. entry not found
    FG_Entry* lookup(const FG_Ident& ident) noexcept;

    /// @brief Forward the call to entry_.req_change.
    Error req_change(const FG_Ident& ident, FG_State&& state) noexcept;

    /// @brief Forward the call to FG_Entry::ack_change
    Error ack_change(const FG_Ident& ident) noexcept;

    /// @brief Forward the call to FG_Entry::clr_change
    Error clr_change(const FG_Ident& ident) noexcept;

    /// @brief Forward the call to FG_Entry::clr_change
    Error clr_change(const FG_Ident& ident, FG_State&& state) noexcept;

private:
    std::set<FG_State> allowed_states_{};
    std::unordered_map<FG_Ident, FG_Entry> entries_{};
};

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__FG_STORE_H_
