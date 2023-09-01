//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
//  Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
//=============================================================================

#ifndef E2E_RESULT_H_INCLUDED
#define E2E_RESULT_H_INCLUDED

#include "ara/com/e2e/e2e_error_domain.h"

namespace ara
{
namespace com
{
namespace e2e
{
/// @brief Class used by E2E Checkers to return the result
class Result
{
public:
    /// @brief Check result of the sample
    ProfileCheckStatus checkStatus;

    /// @brief State Machine status after the sample was checked
    SMState smStatus;
};

} // namespace e2e
} // namespace com
} // namespace ara

#endif // E2E_RESULT_H_INCLUDED
