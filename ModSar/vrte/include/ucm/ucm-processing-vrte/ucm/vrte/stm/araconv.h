//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// \file         ucm/vrte/stm/araconv.h
/// \brief
/// \copyright    Robert Bosch GmbH 2021
/// \author
/// \version
/// \remarks
/// \ingroup      bosch_vrte_ucm_vrte_stm

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__ARACONV_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__ARACONV_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/vrte/stm/aracom_includes.h"

/// @addtogroup bosch_vrte_ucm_vrte_stm
/// @{


namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace vrte   {
namespace stm    {

using Status = ::ara::sm::stmStateManagementErrorType;


/// @brief Represents the state of STM.
enum class StateManagerErrorType : std::uint8_t
{
    /// FunctionGroup State change request was executed successfully
    kSuccess = 0,
    /// FunctionGroup State change request was invalid e,g, unknown state
    kInvalid = 1,
    /// FunctionGroup State change request failed due to other reason
    kFailed = 2,
    /// FunctionGroup State change request failed due to other reason
    kDelay = 3,
    /// Requested operation was rejected due to State Managements/machines
    /// internal state
    kRejected = 5,
    /// Verification step of update failed.
    kVerifyFailed = 6,
    /// Preparation step of update failed.
    kPrepareFailed = 7,
    /// Rollback step of update failed
    kRollbackFailed = 8,
#ifndef ARA_VERSION_20_11
    /// Request Update session rejected in case of an already active update session
    kNotAllowedMultipleUpdateSessions = 9
#endif
};

/// \brief AraConv provides methods to coovert internal types to ara defined
/// types and vice-versa.
class Araconv
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_stm__Araconv, CTor);
    FRIEND_TEST(Test__ucm_vrte_stm__Araconv, StatusCstr);
#endif

public:
    /// \brief Default constructor
    Araconv() = default;

    Araconv(Araconv     &&) = delete;
    Araconv(Araconv const&) = delete;

    Araconv& operator=(Araconv     &&) = delete;
    Araconv& operator=(Araconv const&) = delete;

    virtual ~Araconv() = default;

    /// @brief Convert status from enum to string.
    /// @param [IN] status of type enum class PackageManagerStatusType : std::uint8_t
    /// @return Status in the form of string
    static const char* status_cstr(const Status& status) noexcept;
};

}    // namespace stm
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_STM__ARACONV_H_
