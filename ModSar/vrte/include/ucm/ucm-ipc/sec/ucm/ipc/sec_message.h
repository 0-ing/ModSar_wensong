//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         sec/ucm/ipc/sec_message.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__SEC_UCM_IPC__SEC_MESSAGE__H_
#define UCM_AAP_IPC__SEC_UCM_IPC__SEC_MESSAGE__H_

#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/ipc_message.h"

/// @addtogroup bosch_vrte_sec_ucm_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace sec   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around the IPC message implementation for SEC
class SEC_Message : public bosch::vrte::ucm::lib::ipc::IPC_Message
{
#if defined(GOOGLE_TEST)
    friend class Test__sec_ucm_ipc__SEC_Message;
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

    explicit SEC_Message(struct ucm_ipcmsg& ref) noexcept;

    SEC_Message(SEC_Message     &&) = default;
    SEC_Message(SEC_Message const&) = default;

    SEC_Message& operator=(SEC_Message     &&) = delete;
    SEC_Message& operator=(SEC_Message const&) = delete;

    virtual ~SEC_Message() = default;

    /// @brief SEC IPC Make message request
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure
    /// @param[in] SW cluster name   
    /// @return std::error_condition
    std::error_condition
    make_request(const Action&, const std::string&) noexcept;

    /// @brief SEC IPC read request
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure
    /// @param[in] SW cluster name   
    /// @return void
    void read_request(Action&, std::string&) noexcept;

    /// @brief SEC IPC save response
    /// @param[out] Result  Contains any of following values,
    ///                     - kSuccess
    ///                     - kFailure
    /// @return void
    void save_response(const Result&) noexcept;

    /// @brief SEC IPC message response
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
}    // namespace sec
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__SEC_UCM_IPC__SEC_MESSAGE__H_

