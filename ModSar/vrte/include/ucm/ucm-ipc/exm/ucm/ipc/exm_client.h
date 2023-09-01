//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         exm/ucm/ipc/exm_client.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_IPC__EXM_UCM_IPC__EXM_CLIENT__H_
#define UCM_AAP_IPC__EXM_UCM_IPC__EXM_CLIENT__H_

#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ipc/ipc_client.h"
#include "exm/ucm/ipc/exm_mqconf.h"
#include "exm/ucm/ipc/exm_message.h"

/// @addtogroup bosch_vrte_exm_ucm_ipc
/// @{

namespace bosch {
namespace vrte  {
namespace exm   {
namespace ucm   {
namespace ipc   {

/// @brief Wrapper around the IPC client implementation for EXM
class EXM_Client : public bosch::vrte::ucm::lib::ipc::IPC_Client
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__exm_ucm_ipc__EXM_Client, CTor_TEST);
#endif

public:
    explicit EXM_Client(uint64_t uuid);

    EXM_Client(EXM_Client     &&) = default;
    EXM_Client(EXM_Client const&) = default;

    EXM_Client& operator=(EXM_Client     &&) = default;
    EXM_Client& operator=(EXM_Client const&) = default;

    virtual ~EXM_Client() = default;
    
    /// @brief EXM IPC client Request
    /// @param[in] Action  Contains any of following values,
    ///                    -  kUpdate
    ///                    -  kInstall
    ///                    -  kRemove
    ///                    -  kFailure
    /// @param[in] SW cluster name   
    /// @return std::error_condition
    std::error_condition request(
            const EXM_Message::Action&, const std::string&) noexcept;

    /// @brief EXM IPC client Response
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
    std::error_condition response(EXM_Message::Action&,
                                  EXM_Message::Result&,
                                  std::string& swc) noexcept;
};

}    // namespace ipc
}    // namespace ucm
}    // namespace exm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_IPC__EXM_UCM_IPC__EXM_CLIENT__H_

