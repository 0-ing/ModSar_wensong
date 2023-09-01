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

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

///
/// @brief RAI style pidfile
///
class PidFile
        : virtual protected ucm::mock::Sequence
{

public:
    // copy semantics
    PidFile(const PidFile&) = delete;
    PidFile& operator=(const PidFile&) = delete;

    // move semantic
    PidFile(PidFile&&) = delete;
    PidFile& operator=(PidFile&&) = delete;

    explicit PidFile(const char* file) noexcept(true)
             : file_(file)
    {}
    explicit PidFile(const std::string& file) noexcept(true)
             : PidFile(file.c_str())
    {}
    ~PidFile() = default;

    void lock() noexcept(false) { pop<void>();}
    void unlock() noexcept(true) { pop<void>();}
    void update() noexcept(false) { pop<void>();}

    void closefd() noexcept(false) { pop<void>();}
    void closefd(bool) noexcept(false) { pop<void>();}
    void daemonize() noexcept(false) { pop<void>();}
    void daemonize(bool) noexcept(false) { pop<void>();}

private:
    int fd_ = -1;
    bool isdaemon_{false};
    bool stdioclosed_{false};
    const std::string file_;

    void pidfile_open() noexcept(false) { pop<void>();}
    void pidfile_lock() noexcept(false) { pop<void>();}
    void pidfile_close() noexcept(true) { pop<void>();}
    void pidfile_write() noexcept(false) { pop<void>();}
    void pidfile_unlock() noexcept(true) { pop<void>();}
    void pidfile_truncate() noexcept(false) { pop<void>();}
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif  // UCM_AAP_LIBRARY_LIB_UTL_PIDFILE_H_
