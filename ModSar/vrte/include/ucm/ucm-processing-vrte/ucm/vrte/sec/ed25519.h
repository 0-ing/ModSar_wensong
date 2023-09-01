//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/sec/ed25519.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec


#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_ED25519_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_ED25519_H_

#include "ucm/vrte/sec/verify_impl.h"

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief Verification implementation for Ed25519.
///

class ED25519 final : public VerifyImpl
{
public:
    explicit ED25519(std::shared_ptr<ara::core::InstanceSpecifier>&
                     instance,
                     std::shared_ptr<ara::core::InstanceSpecifier>&
                     key_instance)
    : VerifyImpl("Ed25519", instance, key_instance) {};
};

}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_ED25519_H_
