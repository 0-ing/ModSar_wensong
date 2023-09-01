//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/swp_compose.h
/// @brief        Generic binary SWP composer base class.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SWP_COMPOSE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SWP_COMPOSE_H_

#include <array>
#include <vector>
#include <memory>
#include <utility>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/sec/provider.h"
#include "ucm/lib/pkg/bin/types.h"
#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/auth_block.h"

/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

/// @class SWP_Compose swp_compose.h ucm/lib/pkg/bin/swp_compose.h
/// @ingroup bosch_vrte_ucm_lib_pkg_bin
/// @brief Base class for a SWP composer.
///
class SWP_Compose
{
#if defined(GOOGLE_TEST)
    friend class Test_ucm_lib_pkg_bin_swp_compose;
    FRIEND_TEST(Test_ucm_lib_pkg_bin_swp_compose, swp_file_make);
#endif

protected:
    /// @brief Construct the base class for SWP composer.
    ///
    /// @param[in] sec_provider UCM wide security provider object.
    /// @param[in] file Output file for the generated SWP.
    ///
    explicit SWP_Compose(sec::Provider& sec_provider,
                         const std::string& file);

    SWP_Compose(SWP_Compose     &&) = default;
    SWP_Compose(SWP_Compose const&) = delete;

    SWP_Compose& operator=(SWP_Compose     &&) = delete;
    SWP_Compose& operator=(SWP_Compose const&) = delete;

public:
    virtual ~SWP_Compose() = default;

    /// @brief Add and artefact to the software package.
    ///
    /// @param file The sfile_pair object to be added.
    /// @returns ErrorValue == kSuccess, on success
    /// @returns ErrorValue != kSuccess, on failure
    Error add_file(sfile_pair&& file) noexcept;

    /// @brief Add artefacts to the software package.
    ///
    /// @param files A list of file_pair objects
    /// @returns ErrorValue == kSuccess, on success
    /// @returns ErrorValue != kSuccess, on failure
    Error add_files(std::vector<sfile_pair>&& files) noexcept;

    /// @brief Generate the SW package.
    virtual Error generate() noexcept = 0;

    virtual void log_info() const noexcept;

protected:
    /// @brief Output file for the generated SWP.
    utl::FileIO swp_file_;

    /// @brief A set of input files for the SWP generation.
    /// @note The update manifest should come first.
    std::vector<sfile_pair> src_files_{};

    /// @brief Reference to UCM wide security provider.
    sec::Provider& sec_provider_;

private:
    static utl::FileIO swp_file_make(const std::string&);
};


}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SWP_COMPOSE_H_
