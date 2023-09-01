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
/// @file         tests/VRTE_UT/mocks/syscall_sys_stat.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_SYSCALL_SYS_STAT_H
#define TESTS_VRTE_UT_MOCKS_SYSCALL_SYS_STAT_H

#include "sys/stat.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C"
{ 

int    __wrap_chmod (const char *, mode_t        ) UCM_MOCK_DECL(chmod )
int    __wrap_fchmod(int, mode_t                 ) UCM_MOCK_DECL(fchmod)
int    __wrap_fstat (int, struct stat *          ) UCM_MOCK_DECL(fstat )
int    __wrap_lstat (const char *, struct stat * ) UCM_MOCK_DECL(lstat )
int    __wrap_mkdir (const char *, mode_t        ) UCM_MOCK_DECL(mkdir )
int    __wrap_mkfifo(const char *, mode_t        ) UCM_MOCK_DECL(mkfifo)
int    __wrap_mknod (const char *, mode_t, dev_t ) UCM_MOCK_DECL(mknod )
int    __wrap_stat  (const char *, struct stat * ) UCM_MOCK_DECL(stat  )
mode_t __wrap_umask (mode_t                      ) UCM_MOCK_DECL(umask )

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_SYSCALL_SYS_STAT_H
