//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/upd/tar/swpackage_impl/ucm/lib/upd/tar/swpackage_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD_TAR__SWPACKAGE_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD_TAR__SWPACKAGE_IMPL_H_

#include <string>

#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/pkg/bin/service.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {
namespace tar   {

class SWPackageImpl : public lib::upd::SWPackage
{
public:
    explicit SWPackageImpl(const std::string& p1,
                           const std::string& p2,
                           std::unique_ptr<lib::arc::Archive>&&) noexcept
        : SWPackage(p1, p2)
    {}

    SWPackageImpl(SWPackageImpl     &&) = delete;
    SWPackageImpl(SWPackageImpl const&) = delete;

    SWPackageImpl& operator=(SWPackageImpl     &&) = delete;
    SWPackageImpl& operator=(SWPackageImpl const&) = delete;

    virtual ~SWPackageImpl() = default;

    Error swp_verify() noexcept override
    { return pop<Error>(); }

    Error swp_extract() noexcept override
    { return pop<Error>(); }
};

}    // namespace tar
}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD_TAR__SWPACKAGE_IMPL_H_
