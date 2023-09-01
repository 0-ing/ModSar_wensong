//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/client/tuple.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_CLIENT_TUPLE_H_
#define UCM_AAP_PKGMANAGER_ARA_CLIENT_TUPLE_H_

#include "ucm/ara/client/gtuple.h"

namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace ara    {
namespace client {

class Tuple final
{
public:
    explicit Tuple(GTuple& gtuple);

    Tuple(Tuple     &&) = default;
    Tuple(Tuple const&) = delete;

    Tuple& operator=(Tuple     &&) = delete;
    Tuple& operator=(Tuple const&) = delete;

    ~Tuple() = default;

    auto& araproxy() noexcept;

    auto& gtuple();

private:
    GTuple& gtuple_;
    std::unique_ptr<AraProxy> araproxy_{};
};

inline auto& Tuple::gtuple()
{
    return gtuple_;
}

inline auto& Tuple::araproxy() noexcept
{
    return *araproxy_;
}

}    // namespace client
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PKGMANAGER_ARA_CLIENT_TUPLE_H_
