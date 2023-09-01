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
/// @file         tests/VRTE_UT/mocks/stdlib_libgen.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_STDLIB_LIBGEN_H
#define TESTS_VRTE_UT_MOCKS_STDLIB_LIBGEN_H

#include "libgen.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" {

char  *__wrap_basename(char *) UCM_MOCK_DECL(basename)
char  *__wrap_dirname (char *) UCM_MOCK_DECL(dirname )

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_STDLIB_LIBGEN_H
