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
/// @file         tests/VRTE_UT/mocks/stdlib_stdlib.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCK_STDLIB_STDLIB_H
#define TESTS_VRTE_UT_MOCK_STDLIB_STDLIB_H

#include "stdlib.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" {

/* void            __wrap__Exit         (int                                                                            ) UCM_MOCK_DECLV(_Exit         ) */
/* long            __wrap_a64l          (const char *                                                                   ) UCM_MOCK_DECL (a64l          ) */
/* void            __wrap_abort         (void                                                                           ) UCM_MOCK_DECLV(abort         ) */
/* int             __wrap_abs           (int                                                                            ) UCM_MOCK_DECL (abs           ) */
int                __wrap_atexit        (void (*)(void)                                                                 ) UCM_MOCK_DECL (atexit        )
double             __wrap_atof          (const char *                                                                   ) UCM_MOCK_DECL (atof          )
int                __wrap_atoi          (const char *                                                                   ) UCM_MOCK_DECL (atoi          )
long               __wrap_atol          (const char *                                                                   ) UCM_MOCK_DECL (atol          )
long long          __wrap_atoll         (const char *                                                                   ) UCM_MOCK_DECL (atoll         )
void         *     __wrap_bsearch       (const void *, const void *, size_t, size_t, int (*)(const void *, const void *)) UCM_MOCK_DECL (bsearch       )
/* void      *     __wrap_calloc        (size_t, size_t                                                                 ) UCM_MOCK_DECL (calloc        ) */
/* div_t           __wrap_div           (int, int                                                                       ) UCM_MOCK_DECL (div           ) */
double             __wrap_drand48       (void                                                                           ) UCM_MOCK_DECL (drand48       )
double             __wrap_erand48       (unsigned short [3]                                                             ) UCM_MOCK_DECL (erand48       )
void               __wrap_exit          (int                                                                            ) UCM_MOCK_DECLV(exit          )
/* void            __wrap_free          (void *                                                                         ) UCM_MOCK_DECLV(free          ) */
char         *     __wrap_getenv        (const char *                                                                   ) UCM_MOCK_DECL (getenv        )
int                __wrap_getsubopt     (char **, char *const *, char **                                                ) UCM_MOCK_DECL (getsubopt     )
int                __wrap_grantpt       (int                                                                            ) UCM_MOCK_DECL (grantpt       )
char         *     __wrap_initstate     (unsigned, char *, size_t                                                       ) UCM_MOCK_DECL (initstate     )
long               __wrap_jrand48       (unsigned short [3]                                                             ) UCM_MOCK_DECL (jrand48       )
/* char      *     __wrap_l64a          (long                                                                           ) UCM_MOCK_DECL (l64a          ) */
long               __wrap_labs          (long                                                                           ) UCM_MOCK_DECL (labs          )
void               __wrap_lcong48       (unsigned short [7]                                                             ) UCM_MOCK_DECLV(lcong48       )
/* ldiv_t          __wrap_ldiv          (long, long                                                                     ) UCM_MOCK_DECL (ldiv          ) */
long long          __wrap_llabs         (long long                                                                      ) UCM_MOCK_DECL (llabs         )
/* lldiv_t         __wrap_lldiv         (long long, long long                                                           ) UCM_MOCK_DECL (lldiv         ) */
long               __wrap_lrand48       (void                                                                           ) UCM_MOCK_DECL (lrand48       )
/* void      *     __wrap_malloc        (size_t                                                                         ) UCM_MOCK_DECL (malloc        ) */
int                __wrap_mblen         (const char *, size_t                                                           ) UCM_MOCK_DECL (mblen         )
size_t             __wrap_mbstowcs      (wchar_t *, const char *, size_t                                                ) UCM_MOCK_DECL (mbstowcs      )
int                __wrap_mbtowc        (wchar_t *, const char *, size_t                                                ) UCM_MOCK_DECL (mbtowc        )
char         *     __wrap_mkdtemp       (char *                                                                         ) UCM_MOCK_DECL (mkdtemp       )
int                __wrap_mkstemp       (char *                                                                         ) UCM_MOCK_DECL (mkstemp       )
long               __wrap_mrand48       (void                                                                           ) UCM_MOCK_DECL (mrand48       )
long               __wrap_nrand48       (unsigned short [3]                                                             ) UCM_MOCK_DECL (nrand48       )
int                __wrap_posix_memalign(void **, size_t, size_t                                                        ) UCM_MOCK_DECL (posix_memalign)
int                __wrap_posix_openpt  (int                                                                            ) UCM_MOCK_DECL (posix_openpt  )
char         *     __wrap_ptsname       (int                                                                            ) UCM_MOCK_DECL (ptsname       )
int                __wrap_putenv        (char *                                                                         ) UCM_MOCK_DECL (putenv        )
void               __wrap_qsort         (void *, size_t, size_t, int (*)(const void *, const void *)                    ) UCM_MOCK_DECLV(qsort         )
int                __wrap_rand          (void                                                                           ) UCM_MOCK_DECL (rand          )
int                __wrap_rand_r        (unsigned *                                                                     ) UCM_MOCK_DECL (rand_r        )
long               __wrap_random        (void                                                                           ) UCM_MOCK_DECL (random        )
/* void      *     __wrap_realloc       (void *, size_t                                                                 ) UCM_MOCK_DECL (realloc       ) */
char         *     __wrap_realpath      (const char *, char *                                                           ) UCM_MOCK_DECL (realpath      )
/* unsigned short  __wrap_seed48        (unsigned short [3]                                                             ) UCM_MOCK_DECL (seed48        ) */
int                __wrap_setenv        (const char *, const char *, int                                                ) UCM_MOCK_DECL (setenv        )
/* void            __wrap_setkey        (const char *                                                                   ) UCM_MOCK_DECLV(setkey        ) */
char         *     __wrap_setstate      (char *                                                                         ) UCM_MOCK_DECL (setstate      )
void               __wrap_srand         (unsigned                                                                       ) UCM_MOCK_DECLV(srand         )
void               __wrap_srand48       (long                                                                           ) UCM_MOCK_DECLV(srand48       )
void               __wrap_srandom       (unsigned                                                                       ) UCM_MOCK_DECLV(srandom       )
double             __wrap_strtod        (const char *, char **                                                          ) UCM_MOCK_DECL (strtod        )
float              __wrap_strtof        (const char *, char **                                                          ) UCM_MOCK_DECL (strtof        )
long               __wrap_strtol        (const char *, char **, int                                                     ) UCM_MOCK_DECL (strtol        )
long double        __wrap_strtold       (const char *, char **                                                          ) UCM_MOCK_DECL (strtold       )
long long          __wrap_strtoll       (const char *, char **, int                                                     ) UCM_MOCK_DECL (strtoll       )
unsigned long      __wrap_strtoul       (const char *, char **, int                                                     ) UCM_MOCK_DECL (strtoul       )
unsigned long long __wrap_strtoull      (const char *, char **, int                                                     ) UCM_MOCK_DECL (strtoull      )
int                __wrap_system        (const char *                                                                   ) UCM_MOCK_DECL (system        )
int                __wrap_unlockpt      (int                                                                            ) UCM_MOCK_DECL (unlockpt      )
int                __wrap_unsetenv      (const char *                                                                   ) UCM_MOCK_DECL (unsetenv      )
size_t             __wrap_wcstombs      (char *, const wchar_t *, size_t                                                ) UCM_MOCK_DECL (wcstombs      )
int                __wrap_wctomb        (char *, wchar_t                                                                ) UCM_MOCK_DECL (wctomb        )

#if 0 // not defined(__EXT_POSIX1_200112) // kept for reference
#endif

#if defined(__EXT_POSIX1_200112)
#endif

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCK_STDLIB_STDLIB_H
