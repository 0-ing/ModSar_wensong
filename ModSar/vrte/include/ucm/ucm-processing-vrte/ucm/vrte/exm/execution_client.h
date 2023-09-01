//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/exm/execution_client.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_exm

#ifndef UCM_AAP_PROCESSING_VRTE_EXM_EXECUTION_CLIENT_H_
#define UCM_AAP_PROCESSING_VRTE_EXM_EXECUTION_CLIENT_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

/// @addtogroup bosch_vrte_ucm_vrte_exm
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {
namespace exm {

/// @brief EXM state handling implementation.
///

class ExecutionClient final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_vrte_exm_ExecutionClient, CTor);
    FRIEND_TEST(Test_ucm_vrte_exm_ExecutionClient, ExmState);
#endif

public:
    /// @brief Possible states
    enum class State : unsigned
    {
        /// Undefined state
        kUndef,
        /// Starting state
        kStarting,
        /// Running state
        kRunning,
        /// Stopping state
        kStopping
    };

    explicit ExecutionClient() = default;

    // copy semantics
    ExecutionClient(const ExecutionClient&) = delete;
    ExecutionClient& operator=(const ExecutionClient&) = delete;

    // move semantic
    ExecutionClient(ExecutionClient&&) = delete;
    ExecutionClient& operator=(ExecutionClient&&) = delete;

    ~ExecutionClient() = default;

    /// @brief Notify execution state to EXM
    /// @param [IN] State to report of type: enum class State
    /// @return  Reporting status success or failure,
    ///          - TRUE : Execution state notified
    ///          - FALSE : Failed to report current state
    bool exm_state(State state) noexcept;
};

}    // namespace exm
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE_EXM_EXECUTION_CLIENT_H_
