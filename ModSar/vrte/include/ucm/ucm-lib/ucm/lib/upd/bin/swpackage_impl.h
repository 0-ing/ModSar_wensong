//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/bin/swpackage_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD_BIN__SWPACKAGE_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD_BIN__SWPACKAGE_IMPL_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/pkg/bin/service.h"

/// @defgroup bosch_vrte_ucm_lib_upd_bin__SWPackageImpl
/// @ingroup bosch_vrte_ucm_lib_upd_bin
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {
namespace bin   {

class SWPackageImpl : public lib::upd::SWPackage
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd_bin__SWPackageImpl, CTor);
#endif
public:
    explicit SWPackageImpl(const std::string& outpath,
                           const std::string& swpfile,
                           pkg::bin::Service& service) noexcept;

    SWPackageImpl(SWPackageImpl     &&) = delete;
    SWPackageImpl(SWPackageImpl const&) = delete;

    SWPackageImpl& operator=(SWPackageImpl     &&) = delete;
    SWPackageImpl& operator=(SWPackageImpl const&) = delete;

    virtual ~SWPackageImpl() = default;

    Error swp_verify() noexcept override;

    virtual Error swp_extract() noexcept override;

private:
    pkg::bin::Service& service_;
};

/// @}

}    // namespace bin
}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD_BIN__SWPACKAGE_IMPL_H_
