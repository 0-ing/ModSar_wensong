//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lip/dev/posix.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_DEV_POSIX_H_
#define UCM_AAP_LIBRARY_LIB_DEV_POSIX_H_

#include "ucm/lib/dev/device.h"
#include "ucm/lib/utl/file_io.h"

#include <cstring> // added for mock


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace dev   {

class Posix
        : public utl::FileIO
        , virtual protected ucm::mock::Sequence
{

public:

    explicit Posix(const Device::Specs& specs) noexcept : specs_{specs} {}

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
    const auto& specs() const noexcept
    {
        return specs_;
    }

    const auto& sofar() const noexcept
    {
        return sofar_;
    }

    const auto& maxsize() const noexcept
    {
        return maxsize_;
    }

    const auto& address() const noexcept
    {
        return address_;
    }

    const auto& ioexpect() const noexcept
    {
        return ioexpect_;
    }

    void sofar(const usize_type& bytes) noexcept
    {
        sofar_ = bytes;
    }

    void maxsize(const usize_type& bytes) noexcept
    {
        maxsize_ = bytes;
    }

    void address(const usize_type& bytes) noexcept
    {
        address_ = bytes;
    }

    void ioexpect(const usize_type& bytes) noexcept
    {
        ioexpect_ = bytes;
    }

    bool erase_image() noexcept
    {
        return pop<bool>();
    }

    // =========================================================================
    // Methods from lib::utl::FileIO
    // =========================================================================
    __attribute__((warn_unused_result))
    virtual int fd_open(int) noexcept override
    {
        return pop<int>();
    }

    __attribute__((warn_unused_result))
    virtual int fd_truncate(off_t) noexcept override
    {
        return pop<int>();
    }

    __attribute__((warn_unused_result))
    virtual int fd_open(int, mode_t) noexcept override
    {
        return pop<int>();
    }

    // =========================================================================
    // Own virtual methods
    // =========================================================================
    __attribute__((warn_unused_result))
    virtual bool io_erase(size_t, off_t) noexcept
    {
        return pop<bool>();
    }

    __attribute__((warn_unused_result))
    virtual bool io_copy(off_t, off_t, size_t) noexcept
    {
        return pop<bool>();
    }

    __attribute__((warn_unused_result))
    virtual ssize_t io_pread(void *, size_t) noexcept
    {
        return pop<ssize_t>();
    }

    __attribute__((warn_unused_result))
    virtual ssize_t io_pread(void * dst, size_t dlen, off_t) noexcept
    {
        auto vec  = pop<std::vector<std::uint8_t>>();
        auto slen = vec.size();
        if (dlen and slen) {
            auto len = dlen < slen ? dlen : slen;
            memcpy(dst, static_cast<void*>(&vec[0]), len);
        }
        return pop<ssize_t>();
    }

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite(const void *, size_t) noexcept
    {
        return pop<ssize_t>();
    }

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite(const void *, size_t, off_t) noexcept
    {
        return pop<ssize_t>();
    }

protected:
    usize_type sofar_{0};
    usize_type maxsize_{0};
    usize_type address_{0};
    usize_type ioexpect_{0};
    Device::Specs specs_;


    __attribute__((warn_unused_result))
    virtual ssize_t io_pread_seek(void *, size_t) noexcept
    {
        return pop<ssize_t>();
    }

    __attribute__((warn_unused_result))
    virtual ssize_t io_pread_seek(void *, size_t, off_t) noexcept
    {
        return pop<ssize_t>();
    }

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite_seek(const void *, size_t) noexcept
    {
        return pop<ssize_t>();
    }

    __attribute__((warn_unused_result))
    virtual ssize_t io_pwrite_seek(const void *, size_t, off_t) noexcept
    {
        return pop<ssize_t>();
    }
};

}    // namespace dev
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_DEV_POSIX_H_
