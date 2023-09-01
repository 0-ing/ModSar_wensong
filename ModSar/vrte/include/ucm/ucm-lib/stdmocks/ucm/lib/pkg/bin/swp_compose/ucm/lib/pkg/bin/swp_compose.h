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

#include "ucm/lib/utl/file_io.h"
#include "ucm/lib/sec/provider.h"
#include "ucm/lib/pkg/bin/types.h"
#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/auth_block.h"

#include "ucm/mock/sequence.h"


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
class SWP_Compose : virtual protected ucm::mock::Sequence
{

protected:
    /// @brief Construct the base class for SWP composer.
    ///
    /// @param[in] sec_provider UCM wide security provider object.
    /// @param[in] file Output file for the generated SWP.
    ///
    explicit SWP_Compose(sec::Provider& sec_provider,
                         const std::string& file)
        : swp_file_{file}
        , sec_provider_{sec_provider}
    {}

    SWP_Compose(SWP_Compose     &&) = default;
    SWP_Compose(SWP_Compose const&) = delete;

    SWP_Compose& operator=(SWP_Compose     &&) = default;
    SWP_Compose& operator=(SWP_Compose const&) = delete;

public:
    virtual ~SWP_Compose() = default;

    Error add_file(sfile_pair&&) noexcept
    { return pop<Error>(); }

    Error add_files(std::vector<sfile_pair>&&) noexcept
    { return pop<Error>(); }

    virtual Error generate() noexcept = 0;

    virtual void log_info() const noexcept {}

protected:
    utl::FileIO swp_file_;

    std::vector<sfile_pair> src_files_{};

    sec::Provider& sec_provider_;
};


}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch


#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SWP_COMPOSE_H_
