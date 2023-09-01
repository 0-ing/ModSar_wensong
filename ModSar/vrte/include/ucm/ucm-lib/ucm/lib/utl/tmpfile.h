//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/tmpfile.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_TMPFILE_H_
#define UCM_AAP_LIBRARY_LIB_UTL_TMPFILE_H_

#include <string>
#include <cstdint>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/file.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class TmpFile : public File
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_TmpFile, FileName);
    FRIEND_TEST(Test_ucm_lib_utl_TmpFile, FileSize);
    FRIEND_TEST(Test_ucm_lib_utl_TmpFile, FileMisc);
#endif

public:
    TmpFile(const TmpFile&) = delete;
    TmpFile& operator=(const TmpFile&) = delete;

    // move semantic
    TmpFile(TmpFile&&) noexcept(true) = default;
    TmpFile& operator=(TmpFile&&) noexcept(true) = default;

    explicit TmpFile(const char* templ, bool autodel = true) noexcept(false);
    explicit TmpFile(const std::string& templ,
                     bool autodel = true) noexcept(false);
    explicit TmpFile(off_t size, const char* templ,
                     bool autodel = true) noexcept(false);
    explicit TmpFile(off_t size, const std::string& templ,
                     bool autodel = true) noexcept(false);
    virtual ~TmpFile() = default;

    static std::string make(const std::string& templ) noexcept(false);
    static std::string
    make(off_t size, const std::string& templ) noexcept(false);

    off_t size_ = 0;

private:
    std::string maketemp(char* path) noexcept(false);
    std::string maketemp(const std::string& path) noexcept(false);
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif /* UCM_AAP_LIBRARY_LIB_UTL_TMPFILE_H_ */
