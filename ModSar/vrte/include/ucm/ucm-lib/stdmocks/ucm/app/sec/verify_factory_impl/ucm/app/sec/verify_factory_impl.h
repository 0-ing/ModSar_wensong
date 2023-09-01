//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/app/sec/verify_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_APP_SEC_VERIFY_FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_VERIFY_FACTORY_IMPL_H_

#include "ucm/lib/sec/verify_factory.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace sec {

class VerifyFactoryImpl
        : public lib::sec::VerifyFactory
        , virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_app_sec_KeysFactoryImpl, CTor);
    FRIEND_TEST(Test_ucm_app_sec_KeysFactoryImpl, CreateVerify);
#endif
public:
    std::unique_ptr<lib::sec::Verify> create(std::string const&) override { return pop<std::unique_ptr<lib::sec::Verify>&&>(); }
};

}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_APP_SEC_VERIFY_FACTORY_IMPL_H_
