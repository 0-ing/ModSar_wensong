//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file         tests/VRTE_UT/mocks/syscall_fcntl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_SYSCALL_FCNTL_H
#define TESTS_VRTE_UT_MOCKS_SYSCALL_FCNTL_H

#include "fcntl.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" { 

int __wrap_creat           (const char *, mode_t  ) UCM_MOCK_DECL (creat          )
int __wrap_fcntl           (int, int, ...         ) UCM_MOCK_DECL (fcntl          )
int __wrap_open            (const char *, int, ...) UCM_MOCK_DECL (open           )
/* int __wrap_posix_fadvise   (int, off_t, off_t, int) UCM_MOCK_DECL (posix_fadvice  ) */
/* int __wrap_posix_fallocate (int, off_t, off_t     ) UCM_MOCK_DECL (posix_fallocate) */

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_SYSCALL_FCNTL_H
