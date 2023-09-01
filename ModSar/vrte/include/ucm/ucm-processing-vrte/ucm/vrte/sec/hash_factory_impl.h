//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/sec/hash_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec

#ifndef UCM_AAP_LIBRARY_VRTE_SEC_HASH_FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY_VRTE_SEC_HASH_FACTORY_IMPL_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/hash_factory.h"
#include "ucm/vrte/sec/ara_crypto_includes.h"

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief Hash Factory implementation.
///

class HashFactoryImpl final : public lib::sec::HashFactory
{
    std::shared_ptr<ara::core::InstanceSpecifier> instance_;
public:
    explicit HashFactoryImpl(std::shared_ptr<ara::core::InstanceSpecifier>&);

    /// @brief Provide instance of input hash type
    /// @param [IN] Hash algo (SHA512/SHA256/CRC32) of type : std::string
    /// @param [OUT] None
    /// @return Instance Ptr of type : std::unique_ptr<lib::sec::Hash>
    std::unique_ptr<lib::sec::Hash> create(std::string const&) override;
};

}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY_VRTE_SEC_HASH_FACTORY_IMPL_H_
