//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/vrte/sec/keys.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks      Implemented in impl.cpp

#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_KEYS_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_KEYS_IMPL_H_

#include "ucm/lib/sec/keys.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {
namespace sec {

class Keys final : public lib::sec::Keys
{
protected:
    bool _import(key_type  const&) override               { return pop<bool>(); }
    bool _load  (slot_type const&) override               { return pop<bool>(); }
    bool _load  (key_type  const&, EType const&) override { return pop<bool>(); }
};


}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_KEYS_IMPL_H_
