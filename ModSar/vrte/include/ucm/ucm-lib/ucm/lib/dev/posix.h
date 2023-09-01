//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/dev/posix.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_DEV_POSIX_H_
#define UCM_AAP_LIBRARY_LIB_DEV_POSIX_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/dev/device.h"
#include "ucm/lib/utl/file_io.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace dev {

class Posix : public utl::FileIO
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_dev_Posix, CTor);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, FD_Open);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, IO_Copy);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, IO_Erase);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, IO_PRead);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, IO_PWrite);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, EraseImage);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, IO_PReadSeek);
    FRIEND_TEST(Test_ucm_lib_dev_Posix, IO_PWriteSeek);
#endif

public:

    explicit Posix(const Device::Specs&) noexcept;

    // copy semantics
    Posix(const Posix&) = delete;
    Posix& operator=(const Posix&) = delete;

    // move semantic
    Posix(Posix&&) noexcept = default;
    Posix& operator=(Posix&&) = default;

    virtual ~Posix() = default;

    // =========================================================================
    // Non-virtual methods
    // =========================================================================
    const auto& specs() const noexcept;

    const auto& sofar() const noexcept;

    const auto& maxsize() const noexcept;

    const auto& address() const noexcept;

    const auto& ioexpect() const noexcept;

    void sofar(const usize_type&) noexcept;

    void maxsize(const usize_type&) noexcept;

    void address(const usize_type&) noexcept;

    void ioexpect(const usize_type&) noexcept;

    bool erase_image() noexcept;

    // =========================================================================
    // Methods from lib::utl::FileIO
    // =========================================================================
    __attribute__((warn_unused_result))
    virtual int fd_open(int flags) noexcept override;

    __attribute__((warn_unused_result))
    virtual int fd_truncate(off_t length) noexcept override;

    __attribute__((warn_unused_result))
    virtual int fd_open(int flags, mode_t mode) noexcept override;

    // =========================================================================
    // Own virtual methods
    // =========================================================================
    __attribute__((warn_unused_result))
    virtual bool io_erase(size_t count, off_t offset) noexcept;

    /// @brief Copy data from one location to another.
    ///
    /// @param src Source offset
    /// @param dst Destination offset
    /// @param count The number of bytes to copy
    ///
    /// @return true on success, false otherwise
    __attribute__((warn_unused_result))
    virtual bool io_copy(off_t src, off_t dst, size_t count) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t io_pread(void *buff, size_t nbyte) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t io_pread(void *buff, size_t nbyte, off_t offset) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite(const void *buff, size_t count) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite(const void *buff, size_t count, off_t offset) noexcept;

protected:
    usize_type sofar_{0};
    usize_type maxsize_{0};
    usize_type address_{0};
    usize_type ioexpect_{0};
    Device::Specs specs_;


    __attribute__((warn_unused_result))
    virtual ssize_t io_pread_seek(void *buff, size_t nbyte) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t io_pread_seek(void *buff, size_t nbyte, off_t offset) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite_seek(const void *buff, size_t count) noexcept;

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite_seek(const void *buff, size_t count, off_t offset) noexcept;
};

inline const auto& Posix::specs() const noexcept
{
    return specs_;
}

inline const auto& Posix::sofar() const noexcept
{
    return sofar_;
}

inline const auto& Posix::maxsize() const noexcept
{
    return maxsize_;
}

inline const auto& Posix::address() const noexcept
{
    return address_;
}

inline const auto& Posix::ioexpect() const noexcept
{
    return ioexpect_;
}

inline void Posix::sofar(const usize_type& bytes) noexcept
{
    sofar_ = bytes;
}

inline void Posix::maxsize(const usize_type& bytes) noexcept
{
    maxsize_ = bytes;
}

inline void Posix::address(const usize_type& bytes) noexcept
{
    address_ = bytes;
}

inline void Posix::ioexpect(const usize_type& bytes) noexcept
{
    ioexpect_ = bytes;
}

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_DEV_POSIX_H_
