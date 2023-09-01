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


#ifndef UCM_AAP_LIBRARY_APP_SEC_VERIFY_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_VERIFY_IMPL_H_

#include "ucm/lib/sec/verify.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace sec   {


class VerifyImpl final
    : public lib::sec::Verify
    , virtual protected ucm::mock::Sequence
{
public:

    using Digest    = Verify::Digest;

protected:

    bool _verify(Digest const& , Digest const& ) override { return pop<bool>(); }

};


}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_APP_SEC_VERIFY_IMPL_H_
