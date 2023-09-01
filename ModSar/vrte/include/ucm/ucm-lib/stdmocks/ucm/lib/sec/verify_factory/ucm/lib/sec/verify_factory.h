//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/sec/verify_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_SEC_VERIFY_FACTORY_H_
#define UCM_AAP_LIBRARY_LIB_SEC_VERIFY_FACTORY_H_

#include "ucm/lib/sec/verify.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace sec {

class VerifyFactory
{
public:
    virtual ~VerifyFactory() = default;
    virtual std::unique_ptr<Verify> create(std::string const&) = 0;

protected:
    VerifyFactory() = default;
    VerifyFactory(VerifyFactory const&)            = default;
    VerifyFactory(VerifyFactory     &&) noexcept   = default;
    VerifyFactory& operator=(VerifyFactory const&) = default;
    VerifyFactory& operator=(VerifyFactory     &&) = default;
};

}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SEC_VERIFY_FACTORY_H_
