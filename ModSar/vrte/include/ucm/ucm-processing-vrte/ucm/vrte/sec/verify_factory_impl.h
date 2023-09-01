//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/sec/verify_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec

#ifndef UCM_AAP_LIBRARY_VRTE_SEC_VERIFY_FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY_VRTE_SEC_VERIFY_FACTORY_IMPL_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/verify_factory.h"
#include "ucm/vrte/sec/ara_crypto_includes.h"

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief Verify factory implementation.
///

class VerifyFactoryImpl final : public lib::sec::VerifyFactory
{
    std::shared_ptr<ara::core::InstanceSpecifier> instance_;
    std::shared_ptr<ara::core::InstanceSpecifier> key_instance_;

public:
    explicit VerifyFactoryImpl(std::shared_ptr<ara::core::InstanceSpecifier>&,
                               std::shared_ptr<ara::core::InstanceSpecifier>&);

    /// @brief Provide instance of input Signature type
    /// @param [IN] Signature algo of type : std::string
    ///             Following algorithms supported,
    ///             - ECDSA_Bernstein_25519
    ///             - ECDSA_Bernstein_25519PH
    ///             - ECDSA_NIST_P256
    /// @param [OUT] None
    /// @return Instance Ptr of type : std::unique_ptr<lib::sec::Verify>
    std::unique_ptr<lib::sec::Verify> create(std::string const&) override;
};

}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY_VRTE_SEC_VERIFY_FACTORY_IMPL_H_
