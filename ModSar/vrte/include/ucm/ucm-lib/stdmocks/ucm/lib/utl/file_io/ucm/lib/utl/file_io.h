//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/ucm/lib/utl/file_io/ucm/lib/utl/file_io.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_FILE_IO_H_
#define UCM_AAP_LIBRARY_LIB_UTL_FILE_IO_H_

#include <fcntl.h>

#include <string>
#include <cinttypes>

#include "ucm/lib/utl/syserror.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class FileIO
      : virtual protected ucm::mock::Sequence
{
public:
    static int
    fsync(int) noexcept {return pop<int>();}

    static int
    close(int) noexcept {return pop<int>();}

    static int
    unlink(const char*) noexcept {return pop<int>();}

    static int
    open(const char* , int ) noexcept {return pop<int>();}

    static int
    open(const char* , int , mode_t ) noexcept {return pop<int>();}

    static ssize_t
    write(int , const void*, size_t ) noexcept {return pop<int>();}

    static ssize_t
    pwrite(int, const void*, size_t , off_t ) noexcept {return pop<int>();}

    static ssize_t
    read(int, void*, size_t ) noexcept {return pop<int>();}

    static ssize_t
    pread(int, void*, size_t , off_t ) noexcept {return pop<int>();}

    static off_t
    lseek(int , off_t , int ) noexcept {return pop<off_t>();}

    static int
    stat(const char *) noexcept {return pop<int>();}

    static int
    stat(const char*, struct stat* status) noexcept {status->st_mode = pop<mode_t>(); return pop<int>();}

    static int
    fstat(int , struct stat*) noexcept {return pop<int>();}

    static off_t
    size(const char* ) noexcept  {return pop<off_t>();}

    static off_t
    fsize(int ) noexcept  {return pop<off_t>();}

    FileIO() noexcept = default;

    explicit FileIO(int filedes) noexcept
             : fd_{filedes}
    {
    }

    explicit FileIO(int filedes, bool closeflag) noexcept
             : fd_{filedes}
             , do_close_{closeflag}
    {
    }

    /// @brief Construct FileIO object
    explicit FileIO(const std::string& file)
             : filename_{file}
    {
    }

    explicit FileIO(const std::string& file, int)
             : filename_{file}
    {
    }

    /// @brief Construct FileIO object end open the file
    /// @note flags and mode are as per open()
    explicit FileIO(const std::string& file, int, mode_t)
             : filename_{file}
    {
    }

    // copy semantics
    FileIO(const FileIO&) = default;
    FileIO& operator=(const FileIO&) = default;

    // move semantic
    FileIO(FileIO&&) noexcept = default;
    FileIO& operator=(FileIO&&) = default;

    virtual ~FileIO() = default;

    auto syserror() const noexcept;

    const auto& fd() const noexcept;

    const auto& oserror() const noexcept;

    const auto& filename() const noexcept;

    virtual void fd_close() noexcept { pop<void>();}

    __attribute__((warn_unused_result))
    virtual int fd_fsync() noexcept { return pop<int>();}

    __attribute__((warn_unused_result))
    virtual int fd_open(int ) noexcept { return pop<int>();}

    __attribute__((warn_unused_result))
    virtual int fd_open(int , mode_t ) noexcept { return pop<int>();}

    __attribute__((warn_unused_result))
    virtual off_t fd_seek(off_t , int ) noexcept { return pop<off_t>();}

    __attribute__((warn_unused_result))
    virtual off_t fd_size() noexcept { return pop<off_t>();}

    __attribute__((warn_unused_result))
    virtual ssize_t fd_write(const void*, size_t ) noexcept { return pop<ssize_t>();}

    __attribute__((warn_unused_result))
    virtual ssize_t fd_pwrite(
            const void*, size_t , off_t ) noexcept  { return pop<ssize_t>();}

    __attribute__((warn_unused_result))
    virtual ssize_t fd_read(void*, size_t ) noexcept  { return pop<ssize_t>();}

    __attribute__((warn_unused_result))
    virtual ssize_t fd_pread(void*, size_t , off_t ) noexcept  { return pop<ssize_t>();}

    __attribute__((warn_unused_result))
    virtual int fd_truncate(off_t ) noexcept  { return pop<int>();}

    __attribute__((warn_unused_result))
    virtual bool fd_lseek(off_t , int ) noexcept  { return pop<bool>();}


protected:
    int fd_{-1};
    int oserror_{0};
    bool do_close_{true};
    std::string filename_{};
};

inline auto FileIO::syserror() const noexcept
{
    return pop<SysError>();
}

inline const auto& FileIO::fd() const noexcept
{
    return pop<int const&>();
}

inline const auto& FileIO::oserror() const noexcept
{
    return pop<const int&>();
}

inline const auto& FileIO::filename() const noexcept
{
    return pop<std::string const&>();
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UTL_FILE_IO_H_
