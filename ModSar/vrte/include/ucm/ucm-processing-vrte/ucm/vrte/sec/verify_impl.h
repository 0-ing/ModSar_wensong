//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/sec/verify_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec


#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_VERIFY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_VERIFY_IMPL_H_

#include "ucm/lib/sec/verify.h"
#include "ucm/vrte/sec/ara_crypto_includes.h"

#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief Hash verification implementation.
///

class VerifyImpl : public lib::sec::Verify
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Vrte_Sec_VerifyImpl, verify_success);
    FRIEND_TEST(Test_Vrte_Sec_VerifyImpl, verify_failure);
#endif
protected:

    explicit VerifyImpl(ara::core::String arg,
                        std::shared_ptr<ara::core::InstanceSpecifier>&,
                        std::shared_ptr<ara::core::InstanceSpecifier>&);

    virtual ~VerifyImpl() = default;
    VerifyImpl(VerifyImpl const&) = delete;
    VerifyImpl(VerifyImpl     &&) = default;
    VerifyImpl& operator= (VerifyImpl const&) = delete;
    VerifyImpl& operator= (VerifyImpl     &&) = default;

    /// @brief Signature verification interface
    /// @param [IN]  Hash - Calculated hash
    ///              Signature - Signature to be verified
    /// @param [OUT] None
    /// @return Signature verification status
    ///          - TRUE  Signature verified
    ///          - FALSE Signature verification failed
    bool _verify(
            Digest    const& hash,
            Digest    const& signature) override;

private:
    ara::core::String                             primitive_ {};
    std::shared_ptr<ara::core::InstanceSpecifier> instance_;
    std::shared_ptr<ara::core::InstanceSpecifier> key_instance_;
};


}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_VERIFY_IMPL_H_
