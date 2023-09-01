//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/tmpdir.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_TMPDIR_H_
#define UCM_AAP_LIBRARY_LIB_UTL_TMPDIR_H_

#include <string>
#include <cstdint>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/file.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class TmpDir
        : public File
        , protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_TmpDir, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_TmpDir, Make);
#endif

public:
    TmpDir(const TmpDir&) = delete;
    TmpDir& operator=(const TmpDir&) = delete;

    // move semantic
    TmpDir(TmpDir&&) noexcept(true) = default;
    TmpDir& operator=(TmpDir&&) noexcept(true) = default;

    explicit TmpDir(const std::string& templ,
                     bool autodel) noexcept(false)
             : File(autodel)
    {}
    virtual ~TmpDir() = default;

    static std::string make(const std::string&) noexcept(false) { return pop<std::string>();}

private:
    std::string maketemp(char* ) noexcept(false) { return pop<std::string>();}
    std::string maketemp(const std::string& ) noexcept(false) { return pop<std::string>();}
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif /* UCM_AAP_LIBRARY_LIB_UTL_TMPDIR_H_ */
