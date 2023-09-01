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
/// @file         tests/VRTE_UT/mocks/syscall_socket.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_SYSCALL_SOCKET_H
#define TESTS_VRTE_UT_MOCKS_SYSCALL_SOCKET_H

#include "sys/socket.h"

#include "ucm/mock/enable.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

extern "C" { 

int     __wrap_accept     (int, struct sockaddr *, socklen_t *                               ) UCM_MOCK_DECL (accept     )
int     __wrap_bind       (int, const struct sockaddr *, socklen_t                           ) UCM_MOCK_DECL (bind       )
int     __wrap_connect    (int, const struct sockaddr *, socklen_t                           ) UCM_MOCK_DECL (connect    )
int     __wrap_getpeername(int, struct sockaddr *, socklen_t *                               ) UCM_MOCK_DECL (getpeername)
int     __wrap_getsockname(int, struct sockaddr *, socklen_t *                               ) UCM_MOCK_DECL (getsockname)
int     __wrap_getsockopt (int, int, int, void *, socklen_t *                                ) UCM_MOCK_DECL (getsockopt )
int     __wrap_listen     (int, int                                                          ) UCM_MOCK_DECL (listen     )
ssize_t __wrap_recv       (int, void *, size_t, int                                          ) UCM_MOCK_DECL (recv       )
ssize_t __wrap_recvfrom   (int, void *, size_t, int, struct sockaddr *, socklen_t *          ) UCM_MOCK_DECL (recvfrom   )
ssize_t __wrap_recvmsg    (int, struct msghdr *, int                                         ) UCM_MOCK_DECL (recvmsg    )
ssize_t __wrap_send       (int, const void *, size_t, int                                    ) UCM_MOCK_DECL (send       )
ssize_t __wrap_sendmsg    (int, const struct msghdr *, int                                   ) UCM_MOCK_DECL (sendmsg    )
ssize_t __wrap_sendto     (int, const void *, size_t, int, const struct sockaddr *, socklen_t) UCM_MOCK_DECL (sendto     )
int     __wrap_setsockopt (int, int, int, const void *, socklen_t                            ) UCM_MOCK_DECL (setsockopt )
int     __wrap_shutdown   (int, int                                                          ) UCM_MOCK_DECL (shutdown   )
int     __wrap_socket     (int, int, int                                                     ) UCM_MOCK_DECL (socket     )
int     __wrap_sockatmark (int                                                               ) UCM_MOCK_DECL (sockatmark )
int     __wrap_socketpair (int, int, int, int[2]                                             ) UCM_MOCK_DECL (socketpair )

extern struct sockaddr __mock_accept_address;
extern socklen_t       __mock_accept_address_len;

} // extern "C"

#if defined(__GNUC__ )
#pragma GCC diagnostic pop
#endif

#endif // TESTS_VRTE_UT_MOCKS_SYSCALL_SOCKET_H
