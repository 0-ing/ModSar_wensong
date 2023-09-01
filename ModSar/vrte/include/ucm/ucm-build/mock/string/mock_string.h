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
/// @file         tests/VRTE_UT/mocks/stdlib_string.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_STDLIB_STRING_H
#define TESTS_VRTE_UT_MOCKS_STDLIB_STRING_H

#include "string.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C"
{ 

void    *__wrap_memccpy  (void *, const void *, int, size_t ) UCM_MOCK_DECL (memccpy )
void    *__wrap_memchr   (const void *, int, size_t         ) UCM_MOCK_DECL (memchr  )
int      __wrap_memcmp   (const void *, const void *, size_t) UCM_MOCK_DECL (memcmp  )
void    *__wrap_memcpy   (void *, const void *, size_t      ) UCM_MOCK_DECL (memcpy  )
void    *__wrap_memmove  (void *, const void *, size_t      ) UCM_MOCK_DECL (memmove )
void    *__wrap_memset   (void *, int, size_t               ) UCM_MOCK_DECL (memset  )
char    *__wrap_strcat   (char *, const char *              ) UCM_MOCK_DECL (strcat  )
char    *__wrap_strchr   (const char *, int                 ) UCM_MOCK_DECL (strchr  )
int      __wrap_strcmp   (const char *, const char *        ) UCM_MOCK_DECL (strcmp  )
int      __wrap_strcoll  (const char *, const char *        ) UCM_MOCK_DECL (strcoll )
char    *__wrap_strcpy   (char *, const char *              ) UCM_MOCK_DECL (strcpy  )
size_t   __wrap_strcspn  (const char *, const char *        ) UCM_MOCK_DECL (strcspn )
char    *__wrap_strerror (int                               ) UCM_MOCK_DECL (strerror)
size_t   __wrap_strlen   (const char *                      ) UCM_MOCK_DECL (strlen  )
char    *__wrap_strncat  (char *, const char *, size_t      ) UCM_MOCK_DECL (strncat )
int      __wrap_strncmp  (const char *, const char *, size_t) UCM_MOCK_DECL (strncmp )
char    *__wrap_strncpy  (char *, const char *, size_t      ) UCM_MOCK_DECL (strncpy )
char    *__wrap_strpbrk  (const char *, const char *        ) UCM_MOCK_DECL (strpbrk )
char    *__wrap_strrchr  (const char *, int                 ) UCM_MOCK_DECL (strrchr )
size_t   __wrap_strspn   (const char *, const char *        ) UCM_MOCK_DECL (strspn  )
char    *__wrap_strstr   (const char *, const char *        ) UCM_MOCK_DECL (strstr  )
char    *__wrap_strtok   (char *, const char *              ) UCM_MOCK_DECL (strtok  )
size_t   __wrap_strxfrm  (char *, const char *, size_t      ) UCM_MOCK_DECL (strxfrm )

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_STDLIB_STRING_H
