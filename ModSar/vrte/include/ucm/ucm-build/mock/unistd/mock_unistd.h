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
/// @file         tests/VRTE_UT/mocks/syscall_unistd.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_SYSCALL_UNISTD_H
#define TESTS_VRTE_UT_MOCKS_SYSCALL_UNISTD_H

#include "unistd.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" { 

int      __wrap_access     (const char *, int                           ) UCM_MOCK_DECL (access     )
unsigned __wrap_alarm      (unsigned                                    ) UCM_MOCK_DECL (alarm      )
int      __wrap_chdir      (const char *                                ) UCM_MOCK_DECL (chdir      )
int      __wrap_chown      (const char *, uid_t, gid_t                  ) UCM_MOCK_DECL (chown      )
int      __wrap_close      (int                                         ) UCM_MOCK_DECL (close      )
size_t   __wrap_confstr    (int, char *, size_t                         ) UCM_MOCK_DECL (confstr    )
/* char    *__wrap_crypt      (const char *, const char *                  ) UCM_MOCK_DECL (crypt      ) */
int      __wrap_dup        (int                                         ) UCM_MOCK_DECL (dup        )
int      __wrap_dup2       (int, int                                    ) UCM_MOCK_DECL (dup2       )
/* void  __wrap__exit      (int                                         ) UCM_MOCK_DECLV(_exit      ) */
/* void  __wrap_encrypt    (char [64], int                              ) UCM_MOCK_DECLV(encrypt    ) */
/* int   __wrap_execl      (const char *, const char *, ...             ) UCM_MOCK_DECL (execl      ) */
/* int   __wrap_execle     (const char *, const char *, ...             ) UCM_MOCK_DECL (execle     ) */
/* int   __wrap_execlp     (const char *, const char *, ...             ) UCM_MOCK_DECL (execlp     ) */
int      __wrap_execv      (const char *, char *const []                ) UCM_MOCK_DECL (execv      )
int      __wrap_execve     (const char *, char *const [], char *const []) UCM_MOCK_DECL (execve     )
int      __wrap_execvp     (const char *, char *const []                ) UCM_MOCK_DECL (execvp     )
/* int   __wrap_faccessat  (int, const char *, int, int                 ) UCM_MOCK_DECL (faccessat  ) */
int      __wrap_fchdir     (int                                         ) UCM_MOCK_DECL (fchdir     )
int      __wrap_fchown     (int, uid_t, gid_t                           ) UCM_MOCK_DECL (fchown     )
/* int   __wrap_fchownat   (int, const char *, uid_t, gid_t, int        ) UCM_MOCK_DECL (fchownat   ) */
int      __wrap_fdatasync  (int                                         ) UCM_MOCK_DECL (fdatasync  )
/* int   __wrap_fexecve    (int, char *const [], char *const []         ) UCM_MOCK_DECL (fexecve    ) */
pid_t    __wrap_fork       (void                                        ) UCM_MOCK_DECL (fork       )
long     __wrap_fpathconf  (int, int                                    ) UCM_MOCK_DECL (fpathconf  )
int      __wrap_fsync      (int                                         ) UCM_MOCK_DECL (fsync      )
int      __wrap_ftruncate  (int, off_t                                  ) UCM_MOCK_DECL (ftruncate  )
char    *__wrap_getcwd     (char *, size_t                              ) UCM_MOCK_DECL (getcwd     )
gid_t    __wrap_getegid    (void                                        ) UCM_MOCK_DECL (getegid    )
uid_t    __wrap_geteuid    (void                                        ) UCM_MOCK_DECL (geteuid    )
gid_t    __wrap_getgid     (void                                        ) UCM_MOCK_DECL (getgid     )
int      __wrap_getgroups  (int, gid_t []                               ) UCM_MOCK_DECL (getgroups  )
/* long  __wrap_gethostid  (void                                        ) UCM_MOCK_DECL (gethostid  ) */
int      __wrap_gethostname(char *, size_t                              ) UCM_MOCK_DECL (gethostname)
char    *__wrap_getlogin   (void                                        ) UCM_MOCK_DECL (getlogin   )
int      __wrap_getlogin_r (char *, size_t                              ) UCM_MOCK_DECL (getlogin_r )
int      __wrap_getopt     (int, char * const [], const char *          ) UCM_MOCK_DECL (getopt     )
pid_t    __wrap_getpgid    (pid_t                                       ) UCM_MOCK_DECL (getpgid    )
pid_t    __wrap_getpgrp    (void                                        ) UCM_MOCK_DECL (getpgrp    )
pid_t    __wrap_getpid     (void                                        ) UCM_MOCK_DECL (getpid     )
pid_t    __wrap_getppid    (void                                        ) UCM_MOCK_DECL (getppid    )
pid_t    __wrap_getsid     (pid_t                                       ) UCM_MOCK_DECL (getsid     )
uid_t    __wrap_getuid     (void                                        ) UCM_MOCK_DECL (getuid     )
int      __wrap_isatty     (int                                         ) UCM_MOCK_DECL (isatty     )
int      __wrap_lchown     (const char *, uid_t, gid_t                  ) UCM_MOCK_DECL (lchown     )
int      __wrap_link       (const char *, const char *                  ) UCM_MOCK_DECL (link       )
/* int   __wrap_linkat     (int, const char *, int, const char *, int   ) UCM_MOCK_DECL (linkat     ) */
int      __wrap_lockf      (int, int, off_t                             ) UCM_MOCK_DECL (lockf      )
off_t    __wrap_lseek      (int, off_t, int                             ) UCM_MOCK_DECL (lseek      )
int      __wrap_nice       (int                                         ) UCM_MOCK_DECL (nice       )
long     __wrap_pathconf   (const char *, int                           ) UCM_MOCK_DECL (pathconf   )
int      __wrap_pause      (void                                        ) UCM_MOCK_DECL (pause      )
int      __wrap_pipe       (int [2]                                     ) UCM_MOCK_DECL (pipe       )
ssize_t  __wrap_pread      (int, void *, size_t, off_t                  ) UCM_MOCK_DECL (pread      )
ssize_t  __wrap_pwrite     (int, const void *, size_t, off_t            ) UCM_MOCK_DECL (pwrite     )
ssize_t  __wrap_read       (int, void *, size_t                         ) UCM_MOCK_DECL (read       )
ssize_t  __wrap_readlink   (const char *, char *, size_t                ) UCM_MOCK_DECL (readlink   )
/* ssize_t  __wrap_readlinkat (int, const char *, char *, size_t           ) UCM_MOCK_DECL (readlinkat ) */
int      __wrap_rmdir      (const char *                                ) UCM_MOCK_DECL (rmdir      )
int      __wrap_setegid    (gid_t                                       ) UCM_MOCK_DECL (setegid    )
int      __wrap_seteuid    (uid_t                                       ) UCM_MOCK_DECL (seteuid    )
int      __wrap_setgid     (gid_t                                       ) UCM_MOCK_DECL (setgid     )
int      __wrap_setpgid    (pid_t, pid_t                                ) UCM_MOCK_DECL (setpgid    )
pid_t    __wrap_setpgrp    (void                                        ) UCM_MOCK_DECL (setpgrp    )
int      __wrap_setregid   (gid_t, gid_t                                ) UCM_MOCK_DECL (setregid   )
int      __wrap_setreuid   (uid_t, uid_t                                ) UCM_MOCK_DECL (setreuid   )
pid_t    __wrap_setsid     (void                                        ) UCM_MOCK_DECL (setsid     )
int      __wrap_setuid     (uid_t                                       ) UCM_MOCK_DECL (setuid     )
unsigned __wrap_sleep      (unsigned                                    ) UCM_MOCK_DECL (sleep      )
void     __wrap_swab       (const void *, void *, ssize_t               ) UCM_MOCK_DECLV(swab       )
int      __wrap_symlink    (const char *, const char *                  ) UCM_MOCK_DECL (symlink    )
/* int   __wrap_symlinkat  (const char *, int, const char *             ) UCM_MOCK_DECL (symlinkat  ) */
void     __wrap_sync       (void                                        ) UCM_MOCK_DECLV(sync       )
long     __wrap_sysconf    (int                                         ) UCM_MOCK_DECL (sysconf    )
pid_t    __wrap_tcgetpgrp  (int                                         ) UCM_MOCK_DECL (tcgetpgrp  )
int      __wrap_tcsetpgrp  (int, pid_t                                  ) UCM_MOCK_DECL (tcsetpgrp  )
int      __wrap_truncate   (const char *, off_t                         ) UCM_MOCK_DECL (truncate   )
char    *__wrap_ttyname    (int                                         ) UCM_MOCK_DECL (ttyname    )
int      __wrap_ttyname_r  (int, char *, size_t                         ) UCM_MOCK_DECL (ttyname_r  )
int      __wrap_unlink     (const char *                                ) UCM_MOCK_DECL (unlink     )
/* int   __wrap_unlinkat   (int, const char *, int                      ) UCM_MOCK_DECL (unlinkat   ) */
ssize_t  __wrap_write      (int, const void *, size_t                   ) UCM_MOCK_DECL (write      )

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_SYSCALL_UNISTD_H
