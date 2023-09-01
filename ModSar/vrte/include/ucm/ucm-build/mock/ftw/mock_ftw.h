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
/// @file         tests/VRTE_UT/mocks/stdlib_ftw.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_STDLIB_FTW_H
#define TESTS_VRTE_UT_MOCKS_STDLIB_FTW_H

#include "ftw.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" {

int __wrap_ftw (const char *, int (*)(const char *, const struct stat *, int), int)                    UCM_MOCK_DECL(ftw )
int __wrap_nftw(const char *, int (*)(const char *, const struct stat *, int, struct FTW *), int, int) UCM_MOCK_DECL(nftw)

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_STDLIB_FTW_H
