//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/vrte/sec/sha2_256.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec


#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_SHA2_256_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_SHA2_256_H_

#include "ucm/vrte/sec/sha2_impl.h"

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief SHA-256 implementation.
///

class SHA2_256 : public SHA2Impl
{
public:
    explicit SHA2_256(std::shared_ptr<ara::core::InstanceSpecifier>& instance)
    : SHA2Impl("SHA-256", instance) {}
};


}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_SHA2_256_H_
