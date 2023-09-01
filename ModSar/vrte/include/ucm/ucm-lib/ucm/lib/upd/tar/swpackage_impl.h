//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/tar/swpackage_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UPD_TAR_SWPACKAGE_IMPL_H_
#define UCM_AAP_LIBRARY_LIB_UPD_TAR_SWPACKAGE_IMPL_H_

#include <memory>
#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/upd/swpackage.h"
#include "ucm/lib/arc/archive.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {
namespace tar   {

/// @brief This is an interface to extract artefacts and manifest

class SWPackageImpl : public lib::upd::SWPackage
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd_tar__SWPackageImpl, CTor);
#endif

public:

    /// @brief SWPackageImpl constructor.
    ///
    /// @param[in] outpath Output path for processing
    /// @param[in] swpfile The received SWP file
    /// @param[in] arc unique pointer to archive.
    SWPackageImpl(const std::string& outpath,
                  const std::string& swpfile,
                  std::unique_ptr<lib::arc::Archive>&&) noexcept;

    SWPackageImpl(SWPackageImpl     &&) = delete;
    SWPackageImpl(SWPackageImpl const&) = delete;

    SWPackageImpl& operator=(SWPackageImpl     &&) = delete;
    SWPackageImpl& operator=(SWPackageImpl const&) = delete;

    virtual ~SWPackageImpl() = default;

    Error swp_verify() noexcept override;

    /// @brief Virtual function to extract software package.
    /// @param[in] file Software package.
    /// @param[in] path Software package path.
    /// @return Error type.
    virtual Error swp_extract() noexcept override;
private:
    std::unique_ptr<lib::arc::Archive> arc_;
};


}    // namespace tar
}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TAR_SWPACKAGE_IMPL_H_
