//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/app/sec/keys.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_APP_SEC_KEYS_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_KEYS_IMPL_H_

#include "ucm/lib/sec/keys.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace sec {


class KeysImpl final
    : public lib::sec::Keys
    , virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    friend class KeysImplUt;
#endif
protected:
    using key_type  = lib::sec::Keys::key_type;
    using slot_type = lib::sec::Keys::slot_type;
    using EType     = lib::sec::Keys::EType;

    bool _import(key_type  const&) override { return pop<bool>(); }
    bool _load  (slot_type const&) override { return pop<bool>(); }
    bool _load  (key_type  const&, EType const&) override { return pop<bool>(); }
};


}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_APP_SEC_KEYS_IMPL_H_
