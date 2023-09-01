/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PUB_SUB_SHMEM_LOAN_MSG_HPP
#define PUB_SUB_SHMEM_LOAN_MSG_HPP

#include "LoanId.hpp"
#include "pipc/Config.hpp"

#include <cstdint>

namespace pipc
{
namespace loan
{
/** @brief Message with a loan (identical to LoanId). */
using LoanMsg = LoanId;

/** @brief Message with a restitute (identical to LoanId). */
using RestituteMsg = LoanId;

} // namespace loan
} // namespace pipc

#endif // PUB_SUB_SHMEM_LOAN_MSG_HPP
