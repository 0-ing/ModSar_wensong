//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/swp_process.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SWP_PROCESS_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SWP_PROCESS_H_

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "ucm/lib/utl/file_io.h"
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

/// @class SWP_Process swp_process.h ucm/lib/pkg/bin/swp_process.h
/// @ingroup bosch_vrte_ucm_lib_pkg_bin
/// @brief Base class for a SWP processor.
///
class SWP_Process
{

protected:
    /// @brief Create a SWP processor to extract to directory.
    explicit SWP_Process(const std::string&,
                         const std::string&) {}

    SWP_Process(SWP_Process     &&) = default;
    SWP_Process(SWP_Process const&) = delete;

    SWP_Process& operator=(SWP_Process     &&) = default;
    SWP_Process& operator=(SWP_Process const&) = delete;

public:
    virtual ~SWP_Process() = default;

    /// @brief Verify the package without extracting it.
    Error verify() noexcept;

    /// @brief Extract all of the artefacts from swpfile_ to outdir_.
    Error extract() noexcept;

    const std::string& manifest_file() const noexcept;

    const std::vector<uint8_t>& manifest_buffer() noexcept;

    const std::vector<std::string>& artefacts() const noexcept;

protected:
    std::string outdir_ {};
    utl::FileIO swpfile_{};
    std::string mnffile_{};
    std::vector<uint8_t> manifest_{};
    std::vector<std::string> artefacts_{};

    virtual Error verify_file() noexcept = 0;

    virtual Error process_file() noexcept = 0;

private:
    static const std::string& check_outdir(const std::string&);
    static const std::string& check_swpfile(const std::string&);
};

inline const std::vector<uint8_t>& SWP_Process::manifest_buffer() noexcept
{
    return manifest_;
}

inline const std::string& SWP_Process::manifest_file() const noexcept
{
    return mnffile_;
}

inline const std::vector<std::string>& SWP_Process::artefacts() const noexcept
{
    return artefacts_;
}

}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SWP_PROCESS_H_
