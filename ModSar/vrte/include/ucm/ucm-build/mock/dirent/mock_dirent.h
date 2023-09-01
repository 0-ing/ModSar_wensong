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
/// @file         tests/VRTE_UT/mocks/stdlib_dirent.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_STDLIB_DIRENT_H
#define TESTS_VRTE_UT_MOCKS_STDLIB_DIRENT_H

#include "dirent.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" {

int            __wrap_closedir (DIR *                                   ) UCM_MOCK_DECL (closedir )
DIR           *__wrap_opendir  (const char *                            ) UCM_MOCK_DECL (opendir  )
struct dirent *__wrap_readdir  (DIR *                                   ) UCM_MOCK_DECL (readdir  )
/* int         __wrap_readdir_r(DIR *, struct dirent *, struct dirent **) UCM_MOCK_DECL (readdir_r) */
void           __wrap_rewinddir(DIR *                                   ) UCM_MOCK_DECLV(rewinddir)
void           __wrap_seekdir  (DIR *, long int                         ) UCM_MOCK_DECLV(seekdir  )
long int       __wrap_telldir  (DIR *                                   ) UCM_MOCK_DECL (telldir  )

#if 0 // not defined(__EXT_POSIX1_200112) // kept for reference
#endif

#if defined(__EXT_POSIX1_200112)
#endif

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_STDLIB_DIRENT_H
