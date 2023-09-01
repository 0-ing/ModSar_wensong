//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         sec/ucm/ipc/sec_client.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__SEC_UCM_IPC__SEC_CLIENT__H_
#define UCM_AAP_IPC__SEC_UCM_IPC__SEC_CLIENT__H_

#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/ipc_client.h"
#include "sec/ucm/ipc/sec_mqconf.h"
#include "sec/ucm/ipc/sec_message.h"

/// @addtogroup bosch_vrte_sec_ucm_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace sec   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around the IPC client implementation for SEC
class SEC_Client : public bosch::vrte::ucm::lib::ipc::IPC_Client
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__exm_ucm_ipc__SEC_Client, CTor_TEST);
#endif

public:
    explicit SEC_Client(uint64_t uuid);

    SEC_Client(SEC_Client     &&) = default;
    SEC_Client(SEC_Client const&) = default;

    SEC_Client& operator=(SEC_Client     &&) = default;
    SEC_Client& operator=(SEC_Client const&) = default;

    virtual ~SEC_Client() = default;

    /// @brief SEC IPC client Request
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure
    /// @param[in] SW cluster name   
    /// @return std::error_condition
    std::error_condition request(
            const SEC_Message::Action&, const std::string&) noexcept;

    /// @brief SEC IPC client Response
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure   
    /// @param[out] Result  Contains any of following values,
    ///                     - kSuccess
    ///                     - kFailure
    /// @param[in] SW cluster name          
    /// @return std::error_condition
    std::error_condition response(SEC_Message::Action&,
                                  SEC_Message::Result&,
                                  std::string& swc) noexcept;
};

}    // namespace ipc
}    // namespace ucm
}    // namespace sec
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__SEC_UCM_IPC__SEC_CLIENT__H_

