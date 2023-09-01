//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/fg_cache.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__FG_CACHE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__FG_CACHE_H_

#include <mutex>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/stm/error.h"
#include "ucm/lib/stm/proxy.h"
#include "ucm/lib/stm/fg_store.h"


/// @defgroup bosch_vrte_ucm_lib_stm__FG_Cache__ut Function group cache
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief Maintain the FG store and forward the STM requests.
/// The class maintains all FG instances and the interactions with them.
/// In order to avoid redundant interactions with STM, the class provides a
/// write-through mechanism if there is real state change.
class FG_Cache final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, CTor);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, ProxySet);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, Remove);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, Insert);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, Update);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, FG_Verify);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, FG_Activate);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Cache, FG_Rollback);
#endif

    constexpr static unsigned long timeout = 60000; // milliseconds

    static std::set<FG_State> stateset();

public:
    /// @brief Construct a FG_Cache object, initializing its members.
    explicit FG_Cache();

    FG_Cache(FG_Cache     &&) = delete;
    FG_Cache(FG_Cache const&) = delete;

    FG_Cache& operator=(FG_Cache     &&) = delete;
    FG_Cache& operator=(FG_Cache const&) = delete;

    ~FG_Cache() = default;

    /// @brief Install a proxy that executes the platform requests.
    ///
    /// @param[in] proxy The
    void proxy_set(Proxy* proxy) noexcept;

    /// @brief Try to remove a FG entry from the cache.
    ///
    /// @param ident Identity of the FG to be removed
    /// @return true if entry has been removed.
    /// @return false if no such entry can be found
    Error remove(const FG_Ident& ident) noexcept;

    /// @brief Try to insert a FG entry into the cache.
    ///
    /// @param ident Identity of the FG to be created in FG_Store
    /// @return true if entry has been inserted.
    /// @return false if an entry with the same FG_Ident is already in cache
    Error insert(FG_Ident&& ident, FG_State&& state) noexcept;

    /// @brief Update the state for a FG registered in FG_Cache.
    ///
    /// @param[in] ident Target FG identification
    /// @param[in] state Target FG new state
    /// @return Error variable as a result of operation
    Error update(const FG_Ident& ident, FG_State&& state) noexcept;

    /// @brief Update the state for a FG registered in FG_Cache.
    ///
    /// @param[in] state Target FG new state
    /// @param[in] names List of FG to be updated.
    /// @return Error variable as a result of operation
    Error update(const FG_State& state,
                 const std::vector<std::string> names) noexcept;

    /// @brief Set a list of FGs to a verifying state.
    ///
    /// @param[in] fg_list List of FG to be updated.
    /// @return Error variable as a result of operation
    Error fg_verify(const std::vector<std::string>& fg_list) noexcept;

    /// @brief Set a list of FGs to a activation state.
    ///
    /// @param[in] fg_list List of FG to be updated.
    /// @return Error variable as a result of operation
    Error fg_activate(const std::vector<std::string>& fg_list) noexcept;

    /// @brief Set a list of FGs to a rollback state.
    ///
    /// @param[in] fg_list List of FG to be updated.
    /// @return Error variable as a result of operation
    Error fg_rollback(const std::vector<std::string>& fg_list) noexcept;

private:
    Proxy*   proxy_;    ///< Implementation of the Proxy class, doing the job
    FG_Store store_;    ///< Store for the FG entries maintained by the cache
    bool     fgv_allow_empty_;  ///< Allow STM call with empty verify list
    bool     fga_allow_empty_;  ///< Allow STM call with empty activate list
    bool     fgr_allow_empty_;  ///< Allow STM call with empty rollback list
    mutable std::mutex mutex_{};

    Error update_log(Error, const FG_Ident&, const FG_State&,
                    const lib::utl::source_location&) noexcept;

    Error update_impl(const FG_Ident& ident, FG_State&& state) noexcept;

    Error update_impl(const FG_State& state,
                      const std::vector<std::string> names) noexcept;

    std::vector<FG_Ident> mkidents(const std::vector<std::string> names);
};

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__FG_CACHE_H_
