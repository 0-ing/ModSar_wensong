//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/sec/verify_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks      Implemented in impl.cpp


#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_VERIFY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_VERIFY_IMPL_H_

#include "ucm/lib/sec/verify.h"

#include <memory>

namespace bosch {
namespace vrte {
namespace ucm {
namespace vrte {
namespace sec {

class VerifyImpl : public lib::sec::Verify
{
protected:
    enum class Algorithm
    {
        ED25519,
        ED25519PH,
        ECC_NIST_P256
    };
    template<typename T> static T translate(Algorithm) { return pop<T>(); }

    explicit VerifyImpl(Algorithm) { pop<void>(); }

   ~VerifyImpl() = default;
    VerifyImpl(VerifyImpl const&) = delete;
    VerifyImpl(VerifyImpl     &&) = default;
    VerifyImpl& operator=(VerifyImpl const&) = delete;
    VerifyImpl& operator=(VerifyImpl     &&) = default;

    // interface implementation
    bool _verify(
            slot_type const&,
            Digest    const&,
            Digest    const&) override { return pop<bool>(); }
    bool _verify(
            key_type  const&,
            EKey      const&,
            Digest    const&,
            Digest    const&) override { return pop<bool>(); }
};


}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_VERIFY_IMPL_H_
