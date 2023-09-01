//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/swpackage.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UPD_SWPACKAGE_H_
#define UCM_AAP_LIBRARY_LIB_UPD_SWPACKAGE_H_

#include <string>
#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

/// @brief This is an method to extract artefacts and manifest

class SWPackage
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd_SWPackage, TEST__CTor);
#endif

public:

    explicit SWPackage(const std::string& outpath,
                       const std::string& swpfile);

    SWPackage(SWPackage     &&) = delete;
    SWPackage(SWPackage const&) = delete;

    SWPackage& operator=(SWPackage     &&) = delete;
    SWPackage& operator=(SWPackage const&) = delete;

    virtual ~SWPackage() = default;

    /// @brief Check the integrity of the SWPackage.
    ///
    /// @return Error typer.
    virtual Error swp_verify() noexcept = 0;

    /// @brief Virtual function to extract software package.
    /// @param[in] file Software package.
    /// @return Error type.
    virtual Error swp_extract() noexcept = 0;

    /// @brief Function to get the manifest file path.
    /// @return manifest manifest file path.
    const std::string& manifest() const noexcept;

    /// @brief Function to get the artefact.
    /// @param[in] idx index value.
    /// @return artefact at index idx.
    const std::string& artefact(size_t idx) const noexcept;

protected:
    std::string              outpath_;
    std::string              swpfile_;
    std::string              manifest_ {};
    std::vector<std::string> artefacts_{};

    /// @brief Function to sort the artefacts.
    void sort_artefacts();

private:
    std::string phony_{};
};

inline const std::string& SWPackage::manifest() const noexcept
{
    return manifest_;
}


}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_SWPACKAGE_H_

