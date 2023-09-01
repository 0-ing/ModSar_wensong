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

#include "ucm/lib/utl/file_io.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class FileOP
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
    copy(FileIO&, FileIO&);

    static void
    clone(const std::string&, const std::string&);

    static void
    rename(const std::string&, const std::string&);

    /// @brief Read at most size bytes into buff at file offset.
    ///
    /// The method tries to read at most size bytes from the file at location
    /// offset. The read calls are performed in a loop so that no more than
    /// chunk bytes are read from the file at a time.
    /// If the read operation is successful the underlying file descriptor
    /// is changed and the bytes read returned.
    /// On failure the position of the underlying file descriptor remains
    /// unchanged.
    ///
    /// @param[in] fio UCM File descriptor.
    /// @param[in] chunk I/O block size.
    /// @param[in] buff The destination memory buffer for operation.
    /// @param[in] size Size of the data to read from the file.
    /// @param[in] offset Offset within the file for the operation.
    /// @returns size of the data successfully read.
    /// @note On error errno is set as follows:
    /// - EINVAL if size > SSIZE_MAX or offset < 0.
    /// - any error number returned by read or lseek libc calls.
    static ssize_t
    readat(FileIO& fio, size_t chunk,
           void *buff, size_t size, off_t offset) noexcept;

    /// @brief Read at most size bytes into buff at file offset.
    ///
    /// The method tries to read at most size bytes from the file at location
    /// offset. The read calls are performed in a loop so that no more than
    /// chunk bytes are read from the file at a time.
    /// The file descriptor remains unchanged after the call.
    ///
    /// @param[in] fio UCM File descriptor.
    /// @param[in] chunk I/O block size.
    /// @param[in] buff The destination memory buffer for operation.
    /// @param[in] size Size of the data to read from the file.
    /// @param[in] offset Offset within the file for the operation.
    /// @returns size of the data successfully read.
    /// @note On error errno is set as follows:
    /// - EINVAL if size > SSIZE_MAX or offset < 0.
    /// - any error number returned by read or lseek libc calls.
    static ssize_t
    pread(FileIO& fio, size_t chunk,
          void *buff, size_t size, off_t offset) noexcept;

    /// @brief Read at most size bytes into buff at file's current offset.
    ///
    /// The method tries to read at most size bytes from the file's current
    /// offset. The read calls are performed in a loop so that no more than
    /// chunk bytes are read from the file at a time.
    /// If the read operation is successful the underlying file descriptor
    /// is changed and the bytes read returned.
    /// On failure the position of the underlying file descriptor remains
    /// unchanged.
    ///
    /// @param[in] fio UCM File descriptor.
    /// @param[in] chunk I/O block size.
    /// @param[in] buff The destination memory buffer for operation.
    /// @param[in] size Size of the data to read from the file.
    /// @returns size of the data successfully read.
    /// @note On error errno is set as follows:
    /// - EINVAL if size > SSIZE_MAX
    /// - any error number returned by read or lseek libc calls.
    static ssize_t
    read(FileIO& fio, size_t chunk, void *buff, size_t size) noexcept;

    /// @brief Write a buffer to a file at offset.
    ///
    /// The method tries to write at most size bytes to the file at location
    /// offset. The write calls are performed in a loop so that no more than
    /// chunk bytes are written to the file at a time.
    /// If the write operation is successful the underlying file descriptor
    /// is changed and the bytes written returned.
    /// On failure the position of the underlying file descriptor remains
    /// unchanged.
    ///
    /// @param[in] fio UCM File descriptor.
    /// @param[in] chunk I/O block size.
    /// @param[in] buff The source memory buffer for operation.
    /// @param[in] size Size of the data to write to the file.
    /// @param[in] offset Offset within the file for the operation.
    /// @returns size of the data successfully written.
    /// @note On error errno is set as follows:
    /// - EINVAL if size > SSIZE_MAX or offset < 0.
    /// - any error number returned by write or lseek libc calls.
    static ssize_t
    writeat(FileIO& fio, size_t chunk,
            const void *buff, size_t size, off_t offset) noexcept;

    /// @brief Write a buffer to a file at offset.
    ///
    /// The method tries to write at most size bytes to the file at location
    /// offset. The write calls are performed in a loop so that no more than
    /// chunk bytes are written to the file at a time.
    /// The file descriptor remains unchanged after the call.
    ///
    /// @param[in] fio UCM File descriptor.
    /// @param[in] chunk I/O block size.
    /// @param[in] buff The source memory buffer for operation.
    /// @param[in] size Size of the data to write to the file.
    /// @param[in] offset Offset within the file for the operation.
    /// @returns size of the data successfully written.
    /// @returns -1 on error.
    /// @note On error errno is set as follows:
    /// - EINVAL if size > SSIZE_MAX or offset < 0.
    /// - any error number returned by write or lseek libc calls.
    static ssize_t
    pwrite(FileIO& fio, size_t chunk,
           const void *buff, size_t size, off_t offset) noexcept;

    /// @brief Write a buffer to a file at current location.
    ///
    /// The method tries to write at most size bytes to the file at location
    /// offset. The write calls are performed in a loop so that no more than
    /// chunk bytes are written to the file at a time.
    /// If the write operation is successful the underlying file descriptor
    /// is changed and the bytes written returned.
    /// On failure the position of the underlying file descriptor remains
    /// unchanged.
    ///
    /// @param[in] fio UCM File descriptor.
    /// @param[in] chunk I/O block size.
    /// @param[in] buff The source memory buffer for operation.
    /// @param[in] size Size of the data to write to the file.
    /// @returns size of the data successfully written.
    /// @note On error errno is set as follows:
    /// - EINVAL if size > SSIZE_MAX
    /// - any error number returned by write or lseek libc calls.
    static ssize_t
    write(FileIO& fio, size_t chunk, const void *buff, size_t size) noexcept;

public:
    FileOP() noexcept = default;

    FileOP(FileOP     &&) = default;
    FileOP(FileOP const&) = default;

    FileOP& operator=(FileOP     &&);
    FileOP& operator=(FileOP const&);

    ~FileOP() = default;

protected:
    static void open_src(FileIO&);
    static void open_dst(FileIO&, const FileIO&);

private:
    static ssize_t
    read_loop(FileIO& fio, size_t chunk,
              void *buff, size_t size, off_t offset) noexcept;

    static ssize_t
    write_loop(FileIO& fio, size_t chunk,
               const void *buff, size_t size, off_t offset) noexcept;
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UTL_FILE_OP_H_
