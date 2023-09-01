//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/sec/ed25519ph.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec


#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_ED25519PH_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_ED25519PH_H_

#include "ucm/vrte/sec/verify_impl.h"

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief Verification implementation for ED25519PH.
///

class ED25519PH final : public VerifyImpl
{
public:
    explicit ED25519PH(std::shared_ptr<ara::core::InstanceSpecifier>&
                       instance,
                       std::shared_ptr<ara::core::InstanceSpecifier>&
                       key_instance)
    : VerifyImpl("Ed25519ph", instance, key_instance) {};
};


}    // namespace vrte
}    // namespace sec
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_ED25519PH_H_
