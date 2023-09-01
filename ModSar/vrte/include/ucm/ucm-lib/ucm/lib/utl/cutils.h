//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/cutils.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_CUTILS_H_
#define UCM_AAP_LIBRARY_LIB_UTL_CUTILS_H_

#include <sys/types.h>

#include <errno.h>
#include <assert.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifndef member_size
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#define member_size(type, member) sizeof(((type *)0)->member)
#pragma GCC diagnostic pop
#endif

#ifdef __GNUC__
#define UNUSED_RETURN(_expr_)  \
    (__extension__({           \
        auto __res = (_expr_); \
        (void)__res;           \
        __res;                 \
    }))
#else
#define UNUSED_RETURN(_expr_)  \
    ({                         \
        auto __res = (_expr_); \
        (void)__res;           \
        __res;                 \
    })
#endif    // __GNUC__

#define UNUSED_ARG(_expr_) ((void)_expr_)

// POSIX specifies one approach: make the primitive fail right away.
// The error code for this kind of failure is EINTR.
// To handle this nicely - violate MISRA and use GCC extension
#ifndef TEMP_FAILURE_RETRY
#if defined(__GNUC__) || defined(__GNUG__)
#define TEMP_FAILURE_RETRY(_syscall_)             \
    (__extension__({                              \
        decltype(_syscall_) __res;                \
        do {                                      \
            __res = (_syscall_);                  \
        } while (__res == -1L && errno == EINTR); \
        __res;                                    \
    }))
#else    // __GNUC__ || __GNUG__
#define TEMP_FAILURE_RETRY(_syscall_) _syscall_
#endif    // __GNUC__ || __GNUG__
#endif    // TEMP_FAILURE_RETRY

const char* progname(const char* argv0);

#ifdef __cplusplus
}
#endif

#endif /* UCM_AAP_LIBRARY_LIB_UTL_CUTILS_H_ */
