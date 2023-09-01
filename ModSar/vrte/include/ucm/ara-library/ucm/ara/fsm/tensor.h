//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/fsm/tensor.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks      Auto-generated on 05-01-2021 18:00:29


#ifndef UCM_AAP_PKGMANAGER_ARA_FSM_TENSOR_H_
#define UCM_AAP_PKGMANAGER_ARA_FSM_TENSOR_H_

#include <mutex>
#include <cstddef>
#include <functional>


/// @addtogroup bosch_vrte_ucm_ara_fsm
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace fsm {

/// @class Tensor
/// @ingroup bosch_vrte_ucm_ara_fsm
/// @brief Provides helper methods for ARA state transitions.   
///

class Tensor final
{
public:
    constexpr static const std::size_t input_size = 10; /// Input size
    constexpr static const std::size_t state_size = 10; /// Size of state
    constexpr static const std::size_t output_size = 2; /// Output size


    enum class Input : unsigned /// Input command
    {
        kProcessSwPackage,               // ProcessSwPackage
        kCancel,                         // Cancel
        kActivate,                       // Activate
        kFinish,                         // Finish
        kRollback,                       // Rollback
        kRevertProcessedSwPackages,      // RevertProcessedSwPackages
        kTransferData,                   // TransferData
        kTransferExit,                   // TransferExit
        kTransferStart,                  // TransferStart
        kDeleteTransfer,                 // DeleteTransfer
    };

    enum class State : unsigned /// UCM states
    {
        kInvalid,                        // Invalid state
        kIdle,                           // Idle state
        kReady,                          // Ready state
        kActivated,                      // Activated state
        kActivating,                     // Activating state
        kVerifying,                      // Verifying state
        kProcessing,                     // Processing state
        kCleaningup,                     // Cleaningup state
        kRolledback,                     // Rolledback state
        kRollingback,                    // Rollingback state
    };


    enum class Output : unsigned /// Output result
    {
        kSuccess,                        // job done -> success
        kFailure,                        // job done -> failure
    };
    
    /// \brief Method to convert Input command enum to string.
    /// \param [IN] Enum input command
    /// \return Returns a string of given Input command.
    static const char* enum_toname(const Input&) noexcept;
    
    /// \brief Method to convert state enum to string.
    /// \param [IN] Enum state.
    /// \return Returns a string of given enum state.
    static const char* enum_toname(const State&) noexcept;
    
    /// \brief Method to convert Output result enum to string.
    /// \param [IN] Enum output result.
    /// \return Returns a string of given output status.
    static const char* enum_toname(const Output&) noexcept;

    using state_tuple = std::tuple<State, Output>; /// State tuple
    using callback_type = std::function<bool(void)>; /// Callback type
    using callback_tuple = std::tuple<callback_type, callback_type>; /// Callback tuple

    /// explicit parameterized constructor
    explicit Tensor(const State&) noexcept;

    /// Copy Semantics
    Tensor(Tensor&&) noexcept = delete;
    
    /// Copy Semantics
    Tensor& operator=(Tensor&&) = delete;

    /// Move Semantics
    Tensor(const Tensor&) = delete;
    
    /// Move Semantics
    Tensor& operator=(const Tensor&) = delete;

    /// Default destructor
    ~Tensor() = default;

    /// \brief Method to return next state based on input command.
    /// \param [IN] Input command.
    /// \return Next state from state table.
    state_tuple input(const Input&) noexcept;

    /// \brief Method to return next state based on input command.
    /// \param [IN] TRUE: If next state is valid 
    ///             FALSE: If next state is invalid.
    /// \return Next state from state table.
    bool input_exec(const Input&) noexcept;

    void callback(const Input&, const State&, callback_tuple&&) noexcept;

private:
    State state_; /// state variable
    callback_tuple callback_array_[input_size][state_size]; /// callback array

    mutable std::mutex mutex_{}; /// mutex object


    state_tuple switch_state(const Input&) noexcept;
};

}    // namespace fsm
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PKGMANAGER_ARA_FSM_TENSOR_H_
