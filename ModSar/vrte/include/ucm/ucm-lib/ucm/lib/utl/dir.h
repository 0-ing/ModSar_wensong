//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/dir.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_DIR_H_
#define UCM_AAP_LIBRARY_LIB_UTL_DIR_H_

#include <sys/stat.h>

#include <string>
#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/syserror.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class Dir final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_Dir, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_Dir, CTor2);
    FRIEND_TEST(Test_ucm_lib_utl_Dir, Filescount);
    FRIEND_TEST(Test_ucm_lib_utl_Dir, ScanFiles);
#endif

public:
    explicit Dir(const mode_t&, std::string&&);
    explicit Dir(const mode_t&, const std::string&);

    Dir(const Dir&) = delete;
    Dir& operator=(const Dir&) = delete;

    // move semantic
    Dir(Dir&&) noexcept(true) = default;
    Dir& operator=(Dir&&) noexcept(true) = default;

    ~Dir() = default;

    auto syserror() const noexcept;

    const auto& path() const noexcept;
    const auto& oserror() const noexcept;

    std::size_t files_count(const std::string&);

    std::vector<std::string> scan_files(const std::string&);

private:
    int oserror_{0};
    std::string path_{};
    std::vector<std::string> files_{};

    void create(const std::string&, mode_t mode);
};

inline auto Dir::syserror() const noexcept
{
    return SysError(oserror_);
}

inline const auto& Dir::path() const noexcept
{
    return path_;
}

inline const auto& Dir::oserror() const noexcept
{
    return oserror_;
}


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif /* UCM_AAP_LIBRARY_LIB_UTL_DIR_H_ */
