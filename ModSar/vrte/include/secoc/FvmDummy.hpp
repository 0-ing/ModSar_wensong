/// @file FVMDummy.hpp
/// @copyright 2021 Robert Bosch GmbH. All rights reserved.


#ifndef FVM_DUMMY_HPP
#define FVM_DUMMY_HPP

#include <secoc/fvm/FVM.h>
#include <secoc/fvm/fvm_error_domain.h>
#include <secoc/secoc.h>
#include <ara/core/array.h>
#include <ara/core/result.h>

namespace ara
{
namespace com
{
namespace secoc
{

/// @brief Freshness Value management Implementation class
class FvmDummy : public FVM
{
private:
  uint8_t mAttempts;

public:
  using Uptr = std::unique_ptr<FVM>;

  ara::core::Result<void> Initialize() noexcept;

  ara::core::Result<FVContainer, SecOcFvmErrc> GetTxFreshness(std::uint16_t freshnessValueId) noexcept;

  ara::core::Result<FVContainer, SecOcFvmErrc> GetRxFreshness(std::uint16_t      freshnessValueId,
                                                              const FVContainer& txFreshnessValue,
                                                              std::uint16_t      authVerifyAttempts) noexcept;

  ara::core::Result<void> SetTxCompletion(std::uint16_t freshnessValueId) noexcept;

  ara::core::Result<void> SetVerificationStatus(std::uint16_t            freshnessValueId,
                                                VerificationStatusResult SecOCVerificationStatusResult) noexcept;
};

ara::core::Result<FvmDummy::Uptr> CreateFvmDummyInstance() noexcept;

} // namespace secoc
} // namespace com
} // namespace ara

#endif // FVM_DUMMY_HPP
