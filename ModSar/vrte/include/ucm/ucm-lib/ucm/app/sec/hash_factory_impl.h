//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/app/sec/hash_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_sec

#ifndef UCM_AAP_LIBRARY_APP_SEC_HASH_FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_HASH_FACTORY_IMPL_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/hash_factory.h"

/// @addtogroup bosch_vrte_ucm_app_sec
/// @{

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace sec {

/// @class HashFactoryImpl
/// @ingroup bosch_vrte_ucm_app_sec
/// @brief Hash factory implementation.
///

class HashFactoryImpl final : public lib::sec::HashFactory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_app_sec_HashFactoryImpl, CTor);
    FRIEND_TEST(Test_ucm_app_sec_HashFactoryImpl, CreateHash);
#endif
public:
    std::unique_ptr<lib::sec::Hash> create(std::string const&) override;
};

}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY_APP_SEC_HASH_FACTORY_IMPL_H_
