//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/sec/keys_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_SEC_KEYS_FACTORY_H_
#define UCM_AAP_LIBRARY_LIB_SEC_KEYS_FACTORY_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/keys.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace sec {

class KeysFactory
{
public:
    virtual ~KeysFactory() = default;
    virtual std::unique_ptr<Keys> create() = 0;

protected:
    KeysFactory() = default;
    KeysFactory(KeysFactory const&)            = default;
    KeysFactory(KeysFactory     &&) noexcept   = default;
    KeysFactory& operator=(KeysFactory const&) = default;
    KeysFactory& operator=(KeysFactory     &&) = default;
};

}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SEC_KEYS_FACTORY_H_
