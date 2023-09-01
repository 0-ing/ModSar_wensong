//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         mock/vrte_if/globals.hpp
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks


#include "packagemanagement_skeleton.h"
#include "triggerinout_statemachinestate_proxy.h"

namespace ara {
namespace ucm {
namespace pkgmgr {
namespace skeleton {

bool PackageManagementSkeleton::OfferService_throw_{false};
bool PackageManagementSkeleton::OfferService_custom_throw_{false};

void PackageManagementSkeleton::OfferService()
{
    if (OfferService_throw_)
        throw std::runtime_error("Global variable induced exception");
    if (OfferService_custom_throw_)
        throw "Global variable induced custom exception";
}

void PackageManagementSkeleton::StopOfferService()
{
    if (OfferService_throw_)
        throw std::runtime_error("Global variable induced exception");
    if (OfferService_custom_throw_)
        throw "Global variable induced custom exception";
}


} // namespace skeleton
} // namespace pkgmgr
} // namespace ucm
} // namespace ara
