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
/// @file         tests/VRTE_UT/mocks/syscall_pthread.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_SYSCALL_PTHREAD_H
#define TESTS_VRTE_UT_MOCKS_SYSCALL_PTHREAD_H

#include "pthread.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" {

/* int    __wrap_pthread_atfork                  (void (*)(void), void (*)(void), void(*)(void)                ) UCM_MOCK_DECL (pthread_atfork                  ) */
int       __wrap_pthread_attr_destroy            (pthread_attr_t *                                             ) UCM_MOCK_DECL (pthread_attr_destroy            )
int       __wrap_pthread_attr_getdetachstate     (const pthread_attr_t *, int *                                ) UCM_MOCK_DECL (pthread_attr_getdetachstate     )
int       __wrap_pthread_attr_getguardsize       (const pthread_attr_t *, size_t *                             ) UCM_MOCK_DECL (pthread_attr_getguardsize       )
int       __wrap_pthread_attr_getinheritsched    (const pthread_attr_t *, int *                                ) UCM_MOCK_DECL (pthread_attr_getinheritsched    )
int       __wrap_pthread_attr_getschedparam      (const pthread_attr_t *, struct sched_param *                 ) UCM_MOCK_DECL (pthread_attr_getschedparam      )
int       __wrap_pthread_attr_getschedpolicy     (const pthread_attr_t *, int *                                ) UCM_MOCK_DECL (pthread_attr_getschedpolicy     )
int       __wrap_pthread_attr_getscope           (const pthread_attr_t *, int *                                ) UCM_MOCK_DECL (pthread_attr_getscope           )
int       __wrap_pthread_attr_getstack           (const pthread_attr_t *, void **, size_t *                    ) UCM_MOCK_DECL (pthread_attr_getstack           )
int       __wrap_pthread_attr_getstacksize       (const pthread_attr_t *, size_t *                             ) UCM_MOCK_DECL (pthread_attr_getstacksize       )
int       __wrap_pthread_attr_init               (pthread_attr_t *                                             ) UCM_MOCK_DECL (pthread_attr_init               )
int       __wrap_pthread_attr_setdetachstate     (pthread_attr_t *, int                                        ) UCM_MOCK_DECL (pthread_attr_setdetachstate     )
int       __wrap_pthread_attr_setguardsize       (pthread_attr_t *, size_t                                     ) UCM_MOCK_DECL (pthread_attr_setguardsize       )
int       __wrap_pthread_attr_setinheritsched    (pthread_attr_t *, int                                        ) UCM_MOCK_DECL (pthread_attr_setinheritsched    )
int       __wrap_pthread_attr_setschedparam      (pthread_attr_t *, const struct sched_param *                 ) UCM_MOCK_DECL (pthread_attr_setschedparam      )
int       __wrap_pthread_attr_setschedpolicy     (pthread_attr_t *, int                                        ) UCM_MOCK_DECL (pthread_attr_setschedpolicy     )
int       __wrap_pthread_attr_setscope           (pthread_attr_t *, int                                        ) UCM_MOCK_DECL (pthread_attr_setscope           )
int       __wrap_pthread_attr_setstack           (pthread_attr_t *, void *, size_t                             ) UCM_MOCK_DECL (pthread_attr_setstack           )
int       __wrap_pthread_attr_setstacksize       (pthread_attr_t *, size_t                                     ) UCM_MOCK_DECL (pthread_attr_setstacksize       )
int       __wrap_pthread_barrier_destroy         (pthread_barrier_t *                                          ) UCM_MOCK_DECL (pthread_barrier_destroy         )
int       __wrap_pthread_barrier_init            (pthread_barrier_t *, const pthread_barrierattr_t *, unsigned ) UCM_MOCK_DECL (pthread_barrier_init            )
int       __wrap_pthread_barrier_wait            (pthread_barrier_t *                                          ) UCM_MOCK_DECL (pthread_barrier_wait            )
int       __wrap_pthread_barrierattr_destroy     (pthread_barrierattr_t *                                      ) UCM_MOCK_DECL (pthread_barrierattr_destroy     )
int       __wrap_pthread_barrierattr_getpshared  (const pthread_barrierattr_t *, int *                         ) UCM_MOCK_DECL (pthread_barrierattr_getpshared  )
int       __wrap_pthread_barrierattr_init        (pthread_barrierattr_t *                                      ) UCM_MOCK_DECL (pthread_barrierattr_init        )
int       __wrap_pthread_barrierattr_setpshared  (pthread_barrierattr_t *, int                                 ) UCM_MOCK_DECL (pthread_barrierattr_setpshared  )
int       __wrap_pthread_cancel                  (pthread_t                                                    ) UCM_MOCK_DECL (pthread_cancel                  )
int       __wrap_pthread_cond_broadcast          (pthread_cond_t *                                             ) UCM_MOCK_DECL (pthread_cond_broadcast          )
int       __wrap_pthread_cond_destroy            (pthread_cond_t *                                             ) UCM_MOCK_DECL (pthread_cond_destroy            )
int       __wrap_pthread_cond_init               (pthread_cond_t *, const pthread_condattr_t *                 ) UCM_MOCK_DECL (pthread_cond_init               )
int       __wrap_pthread_cond_signal             (pthread_cond_t *                                             ) UCM_MOCK_DECL (pthread_cond_signal             )
int       __wrap_pthread_cond_timedwait          (pthread_cond_t *, pthread_mutex_t *, const struct timespec * ) UCM_MOCK_DECL (pthread_cond_timedwait          )
int       __wrap_pthread_cond_wait               (pthread_cond_t *, pthread_mutex_t *                          ) UCM_MOCK_DECL (pthread_cond_wait               )
int       __wrap_pthread_condattr_destroy        (pthread_condattr_t *                                         ) UCM_MOCK_DECL (pthread_condattr_destroy        )
int       __wrap_pthread_condattr_getclock       (const pthread_condattr_t *, clockid_t *                      ) UCM_MOCK_DECL (pthread_condattr_getclock       )
int       __wrap_pthread_condattr_getpshared     (const pthread_condattr_t *, int *                            ) UCM_MOCK_DECL (pthread_condattr_getpshared     )
int       __wrap_pthread_condattr_init           (pthread_condattr_t *                                         ) UCM_MOCK_DECL (pthread_condattr_init           )
int       __wrap_pthread_condattr_setclock       (pthread_condattr_t *, clockid_t                              ) UCM_MOCK_DECL (pthread_condattr_setclock       )
int       __wrap_pthread_condattr_setpshared     (pthread_condattr_t *, int                                    ) UCM_MOCK_DECL (pthread_condattr_setpshared     )
int       __wrap_pthread_create                  (pthread_t *, const pthread_attr_t *, void *(*)(void*), void *) UCM_MOCK_DECL (pthread_create                  )
int       __wrap_pthread_detach                  (pthread_t                                                    ) UCM_MOCK_DECL (pthread_detach                  )
int       __wrap_pthread_equal                   (pthread_t, pthread_t                                         ) UCM_MOCK_DECL (pthread_equal                   )
void      __wrap_pthread_exit                    (void *                                                       ) UCM_MOCK_DECLV(pthread_exit                    )
int       __wrap_pthread_getconcurrency          (void                                                         ) UCM_MOCK_DECL (pthread_getconcurrency          )
int       __wrap_pthread_getcpuclockid           (pthread_t, clockid_t *                                       ) UCM_MOCK_DECL (pthread_getcpuclockid           )
int       __wrap_pthread_getschedparam           (pthread_t, int *, struct sched_param *                       ) UCM_MOCK_DECL (pthread_getschedparam           )
void*     __wrap_pthread_getspecific             (pthread_key_t                                                ) UCM_MOCK_DECL (pthread_getspecific             )
int       __wrap_pthread_join                    (pthread_t, void **                                           ) UCM_MOCK_DECL (pthread_join                    )
int       __wrap_pthread_key_create              (pthread_key_t *, void (*)(void*)                             ) UCM_MOCK_DECL (pthread_key_create              )
int       __wrap_pthread_key_delete              (pthread_key_t                                                ) UCM_MOCK_DECL (pthread_key_delete              )
int       __wrap_pthread_mutex_consistent        (pthread_mutex_t *                                            ) UCM_MOCK_DECL (pthread_mutex_consistent        )
int       __wrap_pthread_mutex_destroy           (pthread_mutex_t *                                            ) UCM_MOCK_DECL (pthread_mutex_destroy           )
int       __wrap_pthread_mutex_getprioceiling    (const pthread_mutex_t *, int *                               ) UCM_MOCK_DECL (pthread_mutex_getprioceiling    )
int       __wrap_pthread_mutex_init              (pthread_mutex_t *, const pthread_mutexattr_t *               ) UCM_MOCK_DECL (pthread_mutex_init              )
int       __wrap_pthread_mutex_lock              (pthread_mutex_t *                                            ) UCM_MOCK_DECL (pthread_mutex_lock              )
int       __wrap_pthread_mutex_setprioceiling    (pthread_mutex_t *, int, int *                                ) UCM_MOCK_DECL (pthread_mutex_setprioceiling    )
int       __wrap_pthread_mutex_timedlock         (pthread_mutex_t *, const struct timespec *                   ) UCM_MOCK_DECL (pthread_mutex_timedlock         )
int       __wrap_pthread_mutex_trylock           (pthread_mutex_t *                                            ) UCM_MOCK_DECL (pthread_mutex_trylock           )
int       __wrap_pthread_mutex_unlock            (pthread_mutex_t *                                            ) UCM_MOCK_DECL (pthread_mutex_unlock            )
int       __wrap_pthread_mutexattr_destroy       (pthread_mutexattr_t *                                        ) UCM_MOCK_DECL (pthread_mutexattr_destroy       )
int       __wrap_pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *, int *                           ) UCM_MOCK_DECL (pthread_mutexattr_getprioceiling)
int       __wrap_pthread_mutexattr_getprotocol   (const pthread_mutexattr_t *, int *                           ) UCM_MOCK_DECL (pthread_mutexattr_getprotocol   )
int       __wrap_pthread_mutexattr_getpshared    (const pthread_mutexattr_t *, int *                           ) UCM_MOCK_DECL (pthread_mutexattr_getpshared    )
int       __wrap_pthread_mutexattr_getrobust     (const pthread_mutexattr_t *, int *                           ) UCM_MOCK_DECL (pthread_mutexattr_getrobust     )
int       __wrap_pthread_mutexattr_gettype       (const pthread_mutexattr_t *, int *                           ) UCM_MOCK_DECL (pthread_mutexattr_gettype       )
int       __wrap_pthread_mutexattr_init          (pthread_mutexattr_t *                                        ) UCM_MOCK_DECL (pthread_mutexattr_init          )
int       __wrap_pthread_mutexattr_setprioceiling(pthread_mutexattr_t *, int                                   ) UCM_MOCK_DECL (pthread_mutexattr_setprioceiling)
int       __wrap_pthread_mutexattr_setprotocol   (pthread_mutexattr_t *, int                                   ) UCM_MOCK_DECL (pthread_mutexattr_setprotocol   )
int       __wrap_pthread_mutexattr_setpshared    (pthread_mutexattr_t *, int                                   ) UCM_MOCK_DECL (pthread_mutexattr_setpshared    )
int       __wrap_pthread_mutexattr_setrobust     (pthread_mutexattr_t *, int                                   ) UCM_MOCK_DECL (pthread_mutexattr_setrobust     )
int       __wrap_pthread_mutexattr_settype       (pthread_mutexattr_t *, int                                   ) UCM_MOCK_DECL (pthread_mutexattr_settype       )
int       __wrap_pthread_once                    (pthread_once_t *, void (*)(void)                             ) UCM_MOCK_DECL (pthread_once                    )
int       __wrap_pthread_rwlock_destroy          (pthread_rwlock_t *                                           ) UCM_MOCK_DECL (pthread_rwlock_destroy          )
int       __wrap_pthread_rwlock_init             (pthread_rwlock_t *, const pthread_rwlockattr_t *             ) UCM_MOCK_DECL (pthread_rwlock_init             )
int       __wrap_pthread_rwlock_rdlock           (pthread_rwlock_t *                                           ) UCM_MOCK_DECL (pthread_rwlock_rdlock           )
int       __wrap_pthread_rwlock_timedrdlock      (pthread_rwlock_t *, const struct timespec *                  ) UCM_MOCK_DECL (pthread_rwlock_timedrdlock      )
int       __wrap_pthread_rwlock_timedwrlock      (pthread_rwlock_t *, const struct timespec *                  ) UCM_MOCK_DECL (pthread_rwlock_timedwrlock      )
int       __wrap_pthread_rwlock_tryrdlock        (pthread_rwlock_t *                                           ) UCM_MOCK_DECL (pthread_rwlock_tryrdlock        )
int       __wrap_pthread_rwlock_trywrlock        (pthread_rwlock_t *                                           ) UCM_MOCK_DECL (pthread_rwlock_trywrlock        )
int       __wrap_pthread_rwlock_unlock           (pthread_rwlock_t *                                           ) UCM_MOCK_DECL (pthread_rwlock_unlock           )
int       __wrap_pthread_rwlock_wrlock           (pthread_rwlock_t *                                           ) UCM_MOCK_DECL (pthread_rwlock_wrlock           )
int       __wrap_pthread_rwlockattr_destroy      (pthread_rwlockattr_t *                                       ) UCM_MOCK_DECL (pthread_rwlockattr_destroy      )
int       __wrap_pthread_rwlockattr_getpshared   (const pthread_rwlockattr_t *, int *                          ) UCM_MOCK_DECL (pthread_rwlockattr_getpshared   )
int       __wrap_pthread_rwlockattr_init         (pthread_rwlockattr_t *                                       ) UCM_MOCK_DECL (pthread_rwlockattr_init         )
int       __wrap_pthread_rwlockattr_setpshared   (pthread_rwlockattr_t *, int                                  ) UCM_MOCK_DECL (pthread_rwlockattr_setpshared   )
pthread_t __wrap_pthread_self                    (void                                                         ) UCM_MOCK_DECL (pthread_self                    )
int       __wrap_pthread_setcancelstate          (int, int *                                                   ) UCM_MOCK_DECL (pthread_setcancelstate          )
int       __wrap_pthread_setcanceltype           (int, int *                                                   ) UCM_MOCK_DECL (pthread_setcanceltype           )
int       __wrap_pthread_setconcurrency          (int                                                          ) UCM_MOCK_DECL (pthread_setconcurrency          )
int       __wrap_pthread_setschedparam           (pthread_t, int, const struct sched_param *                   ) UCM_MOCK_DECL (pthread_setschedparam           )
pthread_t __wrap_pthread_setschedprio            (pthread_t, int                                               ) UCM_MOCK_DECL (pthread_setschedprio            )
int       __wrap_pthread_setspecific             (pthread_key_t, const void *                                  ) UCM_MOCK_DECL (pthread_setspecific             )
int       __wrap_pthread_spin_destroy            (pthread_spinlock_t *                                         ) UCM_MOCK_DECL (pthread_spin_destroy            )
int       __wrap_pthread_spin_init               (pthread_spinlock_t *, int                                    ) UCM_MOCK_DECL (pthread_spin_init               )
int       __wrap_pthread_spin_lock               (pthread_spinlock_t *                                         ) UCM_MOCK_DECL (pthread_spin_lock               )
int       __wrap_pthread_spin_trylock            (pthread_spinlock_t *                                         ) UCM_MOCK_DECL (pthread_spin_trylock            )
int       __wrap_pthread_spin_unlock             (pthread_spinlock_t *                                         ) UCM_MOCK_DECL (pthread_spin_unlock             )
void      __wrap_pthread_testcancel              (void                                                         ) UCM_MOCK_DECLV(pthread_testcancel              )
/* void   __wrap_pthread_cleanup_pop             (                                                             ) UCM_MOCK_DECLV(pthread_cleanup_pop             ) */
/* void   __wrap_pthread_cleanup_push            (                                                             ) UCM_MOCK_DECLV(pthread_cleanup_push            ) */

#if defined(__QNX__) || defined(_GNU_SOURCE)
int       __wrap_pthread_setname_np              (pthread_t, const char *                                      ) UCM_MOCK_DECL (pthread_setname_np              )
int       __wrap_pthread_getname_np              (pthread_t, char *, int                                       ) UCM_MOCK_DECL (pthread_getname_np              )
#endif

//=============================================================================

// legacy declarations

// pthread_barrier_destroy
extern int __mock_pthread_barrier_destroy_on;
extern int __mock_pthread_barrier_destroy_ex;
extern int __mock_pthread_barrier_destroy_rv;

// pthread_barrier_init
extern int __mock_pthread_barrier_init_on;
extern int __mock_pthread_barrier_init_ex;
extern int __mock_pthread_barrier_init_rv;

// pthread_barrier_wait
extern int __mock_pthread_barrier_wait_on;
extern int __mock_pthread_barrier_wait_ex;
extern int __mock_pthread_barrier_wait_rv;

// pthred_self
extern int       __mock_pthread_self_on;
extern int       __mock_pthread_self_ex;
extern pthread_t __mock_pthread_self_rv;

// pthread_setsched_prio
extern int __mock_pthread_setschedprio_on;
extern int __mock_pthread_setschedprio_ex;
extern int __mock_pthread_setschedprio_rv;

#if defined(__QNX__) || defined(_GNU_SOURCE)
// pthread_setname_np
extern int __mock_pthread_setname_np_on;
extern int __mock_pthread_setname_np_ex;
extern int __mock_pthread_setname_np_rv;

// pthread_getname_np
extern int __mock_pthread_getname_np_on;
extern int __mock_pthread_getname_np_ex;
extern int __mock_pthread_getname_np_rv;
#endif

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_SYSCALL_PTHREAD_H
