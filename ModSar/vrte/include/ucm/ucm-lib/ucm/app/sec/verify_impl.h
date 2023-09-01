//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/app/sec/verify.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_sec


#ifndef UCM_AAP_LIBRARY_APP_SEC_VERIFY_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_VERIFY_IMPL_H_

#include "ucm/lib/sec/verify.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

/// @addtogroup bosch_vrte_ucm_app_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace sec   {

/// @class VerifyImpl
/// @ingroup bosch_vrte_ucm_app_sec
/// @brief Signature verification implementation.
///

class VerifyImpl final : public lib::sec::Verify
{
#if defined(GOOGLE_TEST)
    friend class VerifyImplUt;
#endif
public:

    using Digest    = Verify::Digest;

protected:
    bool _verify(Digest const& hash, Digest const& signature) override;
};


}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY_APP_SEC_VERIFY_IMPL_H_
