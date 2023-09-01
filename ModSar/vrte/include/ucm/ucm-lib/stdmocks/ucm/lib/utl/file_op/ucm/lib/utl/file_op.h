//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/file_op.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_FILE_OP_H_
#define UCM_AAP_LIBRARY_LIB_UTL_FILE_OP_H_

#include <sys/types.h>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/file_io.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class FileOP
        : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_FileIO, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_FileOP, CTor);
    FRIEND_TEST(Test_ucm_lib_utl_FileIO, Copy);
    FRIEND_TEST(Test_ucm_lib_utl_FileIO, Clone);
    FRIEND_TEST(Test_ucm_lib_utl_FileOP, Clone);
    FRIEND_TEST(Test_ucm_lib_utl_FileIO, OpenSrc);
    FRIEND_TEST(Test_ucm_lib_utl_FileOP, OpenSrc);
    FRIEND_TEST(Test_ucm_lib_utl_FileIO, OpenDst);
    FRIEND_TEST(Test_ucm_lib_utl_FileOP, OpenDst);
#endif

    constexpr static size_t iosize = 512;

public:
    static void
    copy(FileIO&, FileIO&) {pop<void>();}

    static void
    clone(const std::string&, const std::string&) {pop<void>();}

    static void
    rename(const std::string&, const std::string&) {pop<void>();}

    static ssize_t
    read(FileIO&, size_t, void *, size_t)
    {
        ssize_t retv = pop<ssize_t>();
        errno = pop<int>();
        return retv;
    }

    static ssize_t
    pread(FileIO& fio, size_t chunk, void* buff, size_t size, off_t)
    {
        return read(fio, chunk, buff, size);
    }

    static ssize_t
    readat(FileIO& fio, size_t chunk, void* buff, size_t size, off_t)
    {
        return read(fio, chunk, buff, size);
    }

    static ssize_t
    write(FileIO&, size_t, const void *, size_t)
    {
        ssize_t retv = pop<ssize_t>();
        errno = pop<int>();
        return retv;
    }

    static ssize_t
    writeat(FileIO& fio, size_t chunk, const void * buff, size_t size, off_t)
    {
        return write(fio, chunk, buff, size);
    }

    static ssize_t
    pwrite(FileIO& fio, size_t chunk, const void * buff, size_t size, off_t)
    {
        return write(fio, chunk, buff, size);
    }

public:
    FileOP() noexcept = default;

    FileOP(FileOP     &&) = default;
    FileOP(FileOP const&) = default;

    FileOP& operator=(FileOP     &&);
    FileOP& operator=(FileOP const&);

    ~FileOP() = default;

protected:
    static void open_src(FileIO&) {pop<void>();}
    static void open_dst(FileIO&, const FileIO&) {pop<void>();}
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UTL_FILE_OP_H_
