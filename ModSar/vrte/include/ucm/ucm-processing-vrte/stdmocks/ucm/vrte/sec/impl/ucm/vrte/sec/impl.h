//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/vrte/sec/impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_IMPL_H_

#include "ucm/mock/sequence.h"
#include "ucm/vrte/sec/ara_crypto_includes.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {
namespace sec {

inline ara::crypto::CryptoProviderUid& uid()
{
    return ucm::mock::Sequence::pop<ara::crypto::CryptoProviderUid&>();
}

inline ara::crypto::cryp::CryptoProvider& provider()
{
    return ucm::mock::Sequence::pop<ara::crypto::cryp::CryptoProvider&>();
}


}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_IMPL_H_
