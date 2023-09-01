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
/// @file         tests/VRTE_UT/mocks/stdlib_stdio.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_STDLIB_STDIO_H
#define TESTS_VRTE_UT_MOCKS_STDLIB_STDIO_H

#include "stdio.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" {

void     __wrap_clearerr        (FILE *                               ) UCM_MOCK_DECLV(clearerr        )
char    *__wrap_ctermid         (char *                               ) UCM_MOCK_DECL (ctermid         )
int      __wrap_fclose          (FILE *                               ) UCM_MOCK_DECL (fclose          )
FILE    *__wrap_fdopen          (int, const char *                    ) UCM_MOCK_DECL (fdopen          )
int      __wrap_feof            (FILE *                               ) UCM_MOCK_DECL (feof            )
int      __wrap_ferror          (FILE *                               ) UCM_MOCK_DECL (ferror          )
int      __wrap_fflush          (FILE *                               ) UCM_MOCK_DECL (fflush          )
int      __wrap_fgetc           (FILE *                               ) UCM_MOCK_DECL (fgetc           )
int      __wrap_fgetpos         (FILE *, fpos_t *                     ) UCM_MOCK_DECL (fgetpos         )
char    *__wrap_fgets           (char *, int, FILE *                  ) UCM_MOCK_DECL (fgets           )
int      __wrap_fileno          (FILE *                               ) UCM_MOCK_DECL (fileno          )
void     __wrap_flockfile       (FILE *                               ) UCM_MOCK_DECLV(flockfile       )
FILE    *__wrap_fopen           (const char *, const char *           ) UCM_MOCK_DECL (fopen           )
int      __wrap_fprintf         (FILE *, const char *, ...            ) UCM_MOCK_DECL (fprintf         )
int      __wrap_fputc           (int, FILE *                          ) UCM_MOCK_DECL (fputc           )
int      __wrap_fputs           (const char *, FILE *                 ) UCM_MOCK_DECL (fputs           )
size_t   __wrap_fread           (void *, size_t, size_t, FILE *       ) UCM_MOCK_DECL (fread           )
FILE    *__wrap_freopen         (const char *, const char *, FILE *   ) UCM_MOCK_DECL (freopen         )
/* int   __wrap_fscanf          (FILE *, const char *, ...            ) UCM_MOCK_DECL (fscanf          ) */
int      __wrap_fseek           (FILE *, long int, int                ) UCM_MOCK_DECL (fseek           )
int      __wrap_fseeko          (FILE *, off_t, int                   ) UCM_MOCK_DECL (fseeko          )
int      __wrap_fsetpos         (FILE *, const fpos_t *               ) UCM_MOCK_DECL (fsetpos         )
long int __wrap_ftell           (FILE *                               ) UCM_MOCK_DECL (ftell           )
off_t    __wrap_ftello          (FILE *                               ) UCM_MOCK_DECL (ftello          )
int      __wrap_ftrylockfile    (FILE *                               ) UCM_MOCK_DECL (ftrylockfile    )
void     __wrap_funlockfile     (FILE *                               ) UCM_MOCK_DECLV(funlockfile     )
size_t   __wrap_fwrite          (const void *, size_t, size_t, FILE * ) UCM_MOCK_DECL (fwrite          )
int      __wrap_getc            (FILE *                               ) UCM_MOCK_DECL (getc            )
int      __wrap_getc_unlocked   (FILE *                               ) UCM_MOCK_DECL (getc_unlocked   )
int      __wrap_getchar         (void                                 ) UCM_MOCK_DECL (getchar         )
int      __wrap_getchar_unlocked(void                                 ) UCM_MOCK_DECL (getchar_unlocked)
int      __wrap_pclose          (FILE *                               ) UCM_MOCK_DECL (pclose          )
void     __wrap_perror          (const char *                         ) UCM_MOCK_DECLV(perror          )
FILE    *__wrap_popen           (const char *, const char *           ) UCM_MOCK_DECL (popen           )
int      __wrap_printf          (const char *, ...                    ) UCM_MOCK_DECL (printf          )
int      __wrap_putc            (int, FILE *                          ) UCM_MOCK_DECL (putc            )
int      __wrap_putc_unlocked   (int, FILE *                          ) UCM_MOCK_DECL (putc_unlocked   )
int      __wrap_putchar         (int                                  ) UCM_MOCK_DECL (putchar         )
int      __wrap_putchar_unlocked(int                                  ) UCM_MOCK_DECL (putchar_unlocked)
int      __wrap_puts            (const char *                         ) UCM_MOCK_DECL (puts            )
int      __wrap_remove          (const char *                         ) UCM_MOCK_DECL (remove          )
int      __wrap_rename          (const char *, const char *           ) UCM_MOCK_DECL (rename          )
void     __wrap_rewind          (FILE *                               ) UCM_MOCK_DECLV(rewind          )
/* int   __wrap_scanf           (const char *, ...                    ) UCM_MOCK_DECL (scanf           ) */
void     __wrap_setbuf          (FILE *, char *                       ) UCM_MOCK_DECLV(setbuf          )
int      __wrap_setvbuf         (FILE *, char *, int, size_t          ) UCM_MOCK_DECL (setvbuf         )
int      __wrap_snprintf        (char *, size_t, const char *, ...    ) UCM_MOCK_DECL (snprintf        )
int      __wrap_sprintf         (char *, const char *, ...            ) UCM_MOCK_DECL (sprintf         )
/* int   __wrap_sscanf          (const char *, const char *, ...      ) UCM_MOCK_DECL (sscanf          ) */
//char    *__wrap_tempnam       (const char *, const char *           ) UCM_MOCK_DECL (tempnam         )
FILE    *__wrap_tmpfile         (void                                 ) UCM_MOCK_DECL (tmpfile         )
//char  *__wrap_tmpnam          (char *                               ) UCM_MOCK_DECL (tmpnam          )
int      __wrap_ungetc          (int, FILE *                          ) UCM_MOCK_DECL (ungetc          )
int      __wrap_vfprintf        (FILE *, const char *, va_list        ) UCM_MOCK_DECL (vfprintf        )
int      __wrap_vprintf         (const char *, va_list                ) UCM_MOCK_DECL (vprintf         )
int      __wrap_vsnprintf       (char *, size_t, const char *, va_list) UCM_MOCK_DECL (vsnprintf       )
int      __wrap_vsprintf        (char *, const char *, va_list        ) UCM_MOCK_DECL (vsprintf        )

#if 0 // not defined(__EXT_POSIX1_200112) // kept for reference
char    *__wrap_cuserid         (char *                               ) UCM_MOCK_DECL (cuserid         )
int      __wrap_getopt          (int, char * const[], const char      ) UCM_MOCK_DECL (getopt          )
char    *__wrap_gets            (char *                               ) UCM_MOCK_DECL (gets            )
int      __wrap_getw            (FILE *                               ) UCM_MOCK_DECL (getw            )
int      __wrap_putw            (int, FILE *                          ) UCM_MOCK_DECL (putw            )
#endif

#if defined(__EXT_POSIX1_200112)
/* int      __wrap_vfscanf      (FILE *, const char *, va_list        ) UCM_MOCK_DECL (vfscanf         ) */
/* int      __wrap_vscanf       (const char *, va_list                ) UCM_MOCK_DECL (vscanf          ) */
/* int      __wrap_vsscanf      (const char *, const char *, va_list  ) UCM_MOCK_DECL (vsscanf         ) */
#endif

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_STDLIB_STDIO_H
