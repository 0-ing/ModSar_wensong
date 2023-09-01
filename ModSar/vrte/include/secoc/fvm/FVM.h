/// @file FVM.h
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.

#ifndef FVM_H
#define FVM_H

#include <secoc/secoc.h>
#include <secoc/fvm/fvm_error_domain.h>
#include <ara/core/result.h>
#include <ara/core/array.h>

namespace ara
{
namespace com
{
namespace secoc
{

struct FVContainer
{
    using FvArray = ara::core::Array<std::uint8_t, 8>;
    std::uint64_t length;
    FvArray value = {0};
};

/// @brief Freshness value manager
class FVM
{
public:

    using Uptr = std::unique_ptr<FVM>;

    virtual ara::core::Result<void> Initialize () noexcept = 0;

    virtual ara::core::Result<FVContainer, SecOcFvmErrc> GetTxFreshness(
        std::uint16_t SecOCFreshnessValueID) noexcept = 0;

    virtual ara::core::Result<FVContainer, SecOcFvmErrc> GetRxFreshness(
        std::uint16_t SecOCFreshnessValueID, 
        const FVContainer &SecOCTruncatedFreshnessValue, 
        std::uint16_t SecOCAuthVerifyAttempts) noexcept = 0;

    virtual ara::core::Result<void> SetTxCompletion(
        std::uint16_t SecOCFreshnessValueID) noexcept = 0;

    virtual ara::core::Result<void> SetVerificationStatus(
        std::uint16_t SecOCFreshnessValueID, 
        VerificationStatusResult SecOCVerificationStatusResult) noexcept = 0;
};

// ara::core::Result<FVM::Uptr> CreateFvmInstance() noexcept;

}  // namespace secoc
}  // namespace com
}  // namespace ara

#endif  // FVM_H
