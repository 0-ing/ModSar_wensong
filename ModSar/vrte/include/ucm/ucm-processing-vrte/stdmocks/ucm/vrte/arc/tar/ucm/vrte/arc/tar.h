//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/vrte/arc/tar/ucm/vrte/arc/tar.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks


#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_TAR_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_TAR_H_

#include "ucm/lib/arc/archive.h"

#include <string>

#include "ucm/mock/sequence.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace arc   {


class Tar final
    : public lib::arc::Archive
    , protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Vrte_Arc_Tar, Simple);
#endif

public:
    virtual ~Tar() {}
    Tar() = default;

protected:
    Tar(Tar const&)            = delete;
    Tar(Tar     &&) noexcept   = delete;
    Tar& operator=(Tar const&) = delete;
    Tar& operator=(Tar     &&) = delete;

    // interface implementation
    void _open()                      override {}
    List _list()                      override { return pop<List>(); }
    void _close()                     override {}
    void _extract(std::string const&) override {}
};


} // namespace arc
} // namespace vrte
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_ARC_TAR_H_
