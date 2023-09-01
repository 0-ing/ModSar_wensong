//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         exm/ucm/ipc/exm_message.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__EXM_UCM_IPC__EXM_MESSAGE__H_
#define UCM_AAP_IPC__EXM_UCM_IPC__EXM_MESSAGE__H_

#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/ipc_message.h"

/// @addtogroup bosch_vrte_exm_ucm_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace exm   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around the IPC message implementation for EXM
class EXM_Message : public bosch::vrte::ucm::lib::ipc::IPC_Message
{
#if defined(GOOGLE_TEST)
    friend class Test__exm_ucm_ipc__EXM_Message;
#endif

public:
    enum class Action : uint32_t
    {
      kUpdate,
      kInstall,
      kRemove,
      kFailure
    };

    static const char *action_cstr(const Action&) noexcept;

    enum class Result : unsigned
    {
      kSuccess,
      kFailure
    };

    static const char *result_cstr(const Result&) noexcept;

    explicit EXM_Message(struct ucm_ipcmsg& ref) noexcept;

    EXM_Message(EXM_Message     &&) = default;
    EXM_Message(EXM_Message const&) = default;

    EXM_Message& operator=(EXM_Message     &&) = delete;
    EXM_Message& operator=(EXM_Message const&) = delete;

    virtual ~EXM_Message() = default;

    /// @brief EXM IPC Make message request
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure
    /// @param[in] SW cluster name   
    /// @return std::error_condition
    std::error_condition
    make_request(const Action&, const std::string&) noexcept;

    /// @brief EXM IPC read request
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure
    /// @param[in] SW cluster name   
    /// @return void
    void read_request(Action&, std::string&) noexcept;

    /// @brief EXM IPC save response
    /// @param[out] Result  Contains any of following values,
    ///                     - kSuccess
    ///                     - kFailure
    /// @return void
    void save_response(const Result&) noexcept;

    /// @brief EXM IPC message response
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure   
    /// @param[out] Result  Contains any of following values,
    ///                     - kSuccess
    ///                     - kFailure
    /// @param[in] SW cluster name          
    /// @return void
    void read_response(Action&, Result&, std::string&) noexcept;
};


}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__EXM_UCM_IPC__EXM_MESSAGE__H_

