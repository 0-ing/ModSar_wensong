//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/utl/pidfile.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_UTL_PIDFILE_H_
#define UCM_AAP_LIBRARY_LIB_UTL_PIDFILE_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

///
/// @brief RAI style pidfile
///
class PidFile
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_PidFile, PidfileCreate);
    FRIEND_TEST(Test_ucm_lib_utl_PidFile, PidfileLock);
    FRIEND_TEST(Test_ucm_lib_utl_PidFile, PidfileFull);
    FRIEND_TEST(Test_ucm_lib_utl_PidFile, PidfileFork);
#endif

public:
    // copy semantics
    PidFile(const PidFile&) = delete;
    PidFile& operator=(const PidFile&) = delete;

    // move semantic
    PidFile(PidFile&&) = delete;
    PidFile& operator=(PidFile&&) = delete;

    explicit PidFile(const char* file) noexcept(true);
    explicit PidFile(const std::string& file) noexcept(true);
    ~PidFile();

    void lock() noexcept(false);
    void unlock() noexcept(true);
    void update() noexcept(false);

    void closefd() noexcept(false);
    void closefd(bool doit) noexcept(false);
    void daemonize() noexcept(false);
    void daemonize(bool doit) noexcept(false);

private:
    int fd_ = -1;
    bool isdaemon_{false};
    bool stdioclosed_{false};
    const std::string file_;

    void pidfile_open() noexcept(false);
    void pidfile_lock() noexcept(false);
    void pidfile_close() noexcept(true);
    void pidfile_write() noexcept(false);
    void pidfile_unlock() noexcept(true);
    void pidfile_truncate() noexcept(false);
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif  // UCM_AAP_LIBRARY_LIB_UTL_PIDFILE_H_
