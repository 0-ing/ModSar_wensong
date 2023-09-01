//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/value_pair.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_VALUE_PAIR_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_VALUE_PAIR_H_

#include "ucm/lib/types.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace ara {
namespace client {

using ARATypes = bosch::vrte::ucm::lib::ara::ARATypes;

template<typename _VType, bool _FValue, _VType _PValue>
struct ValuePair final
{
    explicit ValuePair() = default;

    explicit ValuePair(_VType pvalue, bool valid)
        : valid_{valid}, value_{pvalue} {}

    ValuePair(ValuePair     &&) = default;
    ValuePair(ValuePair const&) = default;

    ValuePair& operator=(ValuePair     &&) = default;
    ValuePair& operator=(ValuePair const&) = default;

    ~ValuePair() = default;

    template<typename _AType>
    void operator()(bool valid, const _AType& value)
    {
        valid_ = valid;
        value_ = static_cast<_VType>(value);
    }

    bool   valid_{_FValue};
    _VType value_{_PValue};
};

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_VALUE_PAIR_H_
