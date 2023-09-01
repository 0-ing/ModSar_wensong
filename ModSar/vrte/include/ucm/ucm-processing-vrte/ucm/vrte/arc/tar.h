//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/vrte/arc/tar.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_arc


#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_TAR_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_TAR_H_

#include "ucm/lib/arc/archive.h"

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

/// @addtogroup bosch_vrte_ucm_vrte_arc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace arc   {

/// @brief Archive service interface implementation

class Tar final
    : public lib::arc::Archive
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Vrte_Arc_Tar, Simple);
#endif

public:
    virtual ~Tar();
    Tar() = default;

protected:
    Tar(Tar const&)            = delete;
    Tar(Tar     &&) noexcept   = delete;
    Tar& operator=(Tar const&) = delete;
    Tar& operator=(Tar     &&) = delete;

    /// @brief Open archive
    /// @param [in] None.
    /// @return void.
    void _open()                      override;

    /// @brief Generate list of data in archive
    /// @param [in] None.
    /// @return List of path and size of files in archive.
    List _list()                      override;

    /// @brief Close archive
    /// @param[in] None.
    /// @return void.
    void _close()                     override;

    /// @brief Extract archive
    /// @param [in] glob of type std::string.
    /// @return void.
    void _extract(std::string const&) override;
};


} // namespace arc
} // namespace vrte
} // namespace ucm
} // namespace vrte
} // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_TAR_H_
