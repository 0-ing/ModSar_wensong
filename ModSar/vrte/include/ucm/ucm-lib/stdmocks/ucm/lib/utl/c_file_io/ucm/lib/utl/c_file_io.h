//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/c_file_io.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_C_FILE_IO_H_
#define UCM_AAP_LIBRARY_LIB_UTL_C_FILE_IO_H_

#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>

#include "ucm/mock/sequence.h"


#ifdef __cplusplus
extern "C" {
#endif

struct ucm_file_io
{
    int fd;
    int syserr;
    char file[PATH_MAX];
};

/**
 * @brief Initialize the IO context and set fd to -1
 * @param ctx Valid pointer to an IO context
 */
__attribute((nonnull(1)))
void ucm_file_io_init(
        struct ucm_file_io *ctx, const char *file);

/**
 * @brief Wrapper around close system call.
 *
 * Close the associated file if open and set fd to -1.
 *
 * @param ctx Valid pointer to an IO context
 */
__attribute((nonnull(1)))
void ucm_file_io_close(struct ucm_file_io *ctx);

/**
 * @brief Wrapper around open system call.
 *
 * Try to open the file and set ctx->fd to the file descriptor.
 * On success the file name is stored in ctx->file
 * On error ctx->syserr is set to errno, but file name not copied
 *
 * @param ctx Valid pointer to an IO context
 * @param name Valid file name
 * @param flags File open flag
 * @param mode File open mode
 * @return return ctx->fd
 */
__attribute((nonnull(1), warn_unused_result))
int ucm_file_io_open(struct ucm_file_io *ctx, int flags, mode_t mode);

/**
 * @brief Wrapper around write system call
 *
 * The function will try to write as much data as possible, working around the
 * EINTR errno iteratively.
 *
 * @param ctx Valid pointer to an IO context
 * @param buff Valid pointer to the data to be written
 * @param count Size of the data to be written
 * @return The actual number of bytes written or -1 on error
 */
__attribute__((nonnull(1,2), warn_unused_result))
ssize_t ucm_file_io_write(struct ucm_file_io *ctx,
                          const void *buff, size_t count);

/**
 * @brief Wrapper around pwrite system call
 *
 * The function will try to write as much data as possible, working around the
 * EINTR errno iteratively.
 *
 * @param ctx Valid pointer to an IO context
 * @param buff Valid pointer to the data to be written
 * @param count Size of the data to be written
 * @param offset Offset from the beginning of file
 * @return The actual number of bytes written or -1 on error
 */
__attribute__((nonnull(1,2), warn_unused_result))
ssize_t ucm_file_io_pwrite(
        struct ucm_file_io *ctx,
        const void *buff, size_t count, off_t offset);

/**
 * @brief Wrapper around read system call
 *
 * The function will try to read as much data as possible, working around the
 * EINTR errno iteratively.
 *
 * @param ctx Valid pointer to an IO context
 * @param buff Valid pointer to the buffer where data is read into
 * @param count Size of the data to be read
 * @return The actual number of bytes read or -1 on error
 */
__attribute__((nonnull(1,2), warn_unused_result))
ssize_t ucm_file_io_read(struct ucm_file_io *ctx,
                         void *buff, size_t nbyte);

/**
 * @brief Wrapper around pread system call
 *
 * The function will try to read as much data as possible, working around the
 * EINTR errno iteratively.
 *
 * @param ctx Valid pointer to an IO context
 * @param buff Valid pointer to the buffer where data is read into
 * @param count Size of the data to be read
 * @param offset Offset from the beginning of file
 * @return The actual number of bytes read or -1 on error
 */
__attribute__((nonnull(1,2), warn_unused_result))
ssize_t ucm_file_io_pread(struct ucm_file_io *ctx,
                         void *buff, size_t nbyte, off_t offset);

/**
 * @brief Wrapper around lseek system call
 *
 * @param ctx Valid pointer to an IO context
 * @param offset Offset in bytes
 * @param whence From where to reposition the file descriptor
 * @return
 */
__attribute__((nonnull(1), warn_unused_result))
off_t ucm_file_io_lseek(struct ucm_file_io *ctx, off_t offset, int whence);


/**
 * @brief wrapper around truncate and ftruncate
 *
 * If ctx->fd > -1 use ftruncate otherwise use truncate with ctx->file
 *
 * @param ctx Valid pointer to an IO context
 * @param length the deisred size of the file
 * @return -1 on error, 0 on success
 */
__attribute__((nonnull(1), warn_unused_result))
int ucm_file_io_truncate(struct ucm_file_io *ctx, off_t length);


/**
 * @brief Get the size of a file
 *
 * @param ctx Valid pointer to an IO context
 * @return (off_t)-1 on error, file size on success
 */
__attribute__((nonnull(1), warn_unused_result))
off_t ucm_file_io_fsize(struct ucm_file_io *ctx);

/**
 * @brief Loads a file in the provided buffer
 *
 * @param file File to load
 * @param buff Buffer where to store the loaded data
 * @param size The size of the buffer on input, size of the data on output
 * @return 0 on success, errno otherwise
 */
__attribute__((nonnull(1,2,3), warn_unused_result))
int ucm_file_io_load(const char *file,
                     void *buff, size_t *size);


#ifdef __cplusplus
}
#endif

#endif // UCM_AAP_LIBRARY_LIB_UTL_C_FILE_IO_H_
