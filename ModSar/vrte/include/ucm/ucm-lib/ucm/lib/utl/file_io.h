//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/file_io.h
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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/utl/syserror.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class FileIO
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_FileIO, Close);
    FRIEND_TEST(Test_FileIO, Open);
    FRIEND_TEST(Test_FileIO, Write);
    FRIEND_TEST(Test_FileIO, PWrite);
    FRIEND_TEST(Test_FileIO, Read);
    FRIEND_TEST(Test_FileIO, PRead);
    FRIEND_TEST(Test_FileIO, Seek);
    FRIEND_TEST(Test_FileIO, Truncate);
    FRIEND_TEST(Test_FileIO, Construction);
    FRIEND_TEST(Test_FileIO, Fsync);
    FRIEND_TEST(Test_FileIO, Fsize);
#endif

    constexpr static std::size_t zero_repeat = 32;

public:
    static int
    fsync(int fd) noexcept;

    static int
    close(int fd) noexcept;

    static int
    unlink(const char* name) noexcept;

    static int
    open(const char* name, int flags) noexcept;

    static int
    open(const char* name, int flags, mode_t mode) noexcept;

    static ssize_t
    write(int fd, const void *buff, size_t count) noexcept;

    static ssize_t
    pwrite(int fd, const void *buff, size_t count, off_t offset) noexcept;

    static ssize_t
    read(int fd, void *buff, size_t nbyte) noexcept;

    static ssize_t
    pread(int fd, void *buff, size_t nbyte, off_t offset) noexcept;

    static off_t
    lseek(int fd, off_t offset, int whence) noexcept;

    static int
    stat(const char *file) noexcept;

    static int
    stat(const char *file, struct stat *st) noexcept;

    static int
    fstat(int file, struct stat *st) noexcept;

    static off_t
    size(const char* name) noexcept;

    static off_t
    fsize(int file) noexcept;

public:
    /// @brief Default constructor
    FileIO() noexcept = default;

    /// @brief Construct an object where the fd_ is not closed on destruction
    explicit FileIO(int filedes) noexcept;

    /// @brief Construct FileIO
    explicit FileIO(int filedes, bool closeflag) noexcept;

    /// @brief Construct FileIO object
    explicit FileIO(const std::string& file);

    /// @brief Construct FileIO object and open the file
    /// @note flags are as per open()
    explicit FileIO(const std::string& file, int flags);

    /// @brief Construct FileIO object end open the file
    /// @note flags and mode are as per open()
    explicit FileIO(const std::string& file, int flags, mode_t mode);

    FileIO(FileIO     &&) noexcept;
    FileIO(FileIO const&);

    FileIO& operator=(FileIO     &&);
    FileIO& operator=(FileIO const&);

    virtual ~FileIO();

    auto syserror() const noexcept;

    const auto& fd() const noexcept;

    const auto& oserror() const noexcept;

    const auto& filename() const noexcept;

    virtual void fd_close() noexcept;

    __attribute__((warn_unused_result))
    virtual int fd_fsync() noexcept;

    __attribute__((warn_unused_result))
    virtual int fd_open(int flags) noexcept;

    __attribute__((warn_unused_result))
    virtual int fd_open(int flags, mode_t mode) noexcept;

    __attribute__((warn_unused_result))
    virtual off_t fd_seek(off_t offset, int whence) noexcept;

    __attribute__((warn_unused_result))
    virtual off_t fd_size() noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t fd_write(const void *buff, size_t count) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t fd_pwrite(
            const void *buff, size_t count, off_t offset) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t fd_read(void *buff, size_t nbyte) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t fd_pread(void *buff, size_t nbyte, off_t offset) noexcept;

    __attribute__((warn_unused_result))
    virtual int fd_truncate(off_t length) noexcept;

    __attribute__((warn_unused_result))
    virtual bool fd_lseek(off_t offset, int whence) noexcept;


protected:
    int fd_{-1};
    int oserror_{0};
    bool do_close_{true};
    std::string filename_{};
};

inline auto FileIO::syserror() const noexcept
{
    return SysError(oserror_);
}

inline const auto& FileIO::fd() const noexcept
{
    return fd_;
}

inline const auto& FileIO::oserror() const noexcept
{
    return oserror_;
}

inline const auto& FileIO::filename() const noexcept
{
    return filename_;
}

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UTL_FILE_IO_H_
