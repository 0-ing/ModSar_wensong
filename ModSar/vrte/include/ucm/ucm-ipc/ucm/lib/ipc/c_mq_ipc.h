//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lip/ipc/c_mq_ipc.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_IPC__C_MQ_IPC_H_
#define UCM_AAP_LIBRARY__UCM_LIB_IPC__C_MQ_IPC_H_

#include <errno.h>
#include <stddef.h>
#include <mqueue.h>

#if !defined (UCM_HAVE_ERRNO_T) && \
   (!defined(__STDC_LIB_EXT1__) || (__STDC_LIB_EXT1__ < 200509L))
#define UCM_HAVE_ERRNO_T
#ifdef __cplusplus
using errno_t = int;
#else
typedef int errno_t;
#endif
#endif

#include "ucm/lib/ipc/c_ipc_msg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Maximum size of the file mqueue base name
 */
#define UCM_MQIPC_NAMESIZE 64

/**
 * Maximum size of the file mqueue unique name
 */
#define UCM_MQIPC_URISIZE (32 + UCM_MQIPC_NAMESIZE)

/**
 * Server mqueue file system UUID
 */
#define UCM_MQIPC_SERVER_UUID 0

/**
 * IPC callback function type.
 * The function receives a message from the underlying layer, does whatever
 * processing is required, modifies the message in-place and on return
 * the reply is sent to the remote site accordingly. The callback is implemented
 * at the server side.
 * @param buff pointer to the message buffer.
 */
typedef errno_t (*mqipc_callback_t)(struct ucm_ipcmsg *msg);

/**
 * IPC printer function type.
 */
typedef void (*mqipc_printer_t)(
        errno_t err, const char *text, const struct ucm_ipcmsg *msg);

/**
 * IPC mqueue peer options block.
 */
struct mqipc_mqopts
{
    mode_t         mode;    /**< mqueue creation mode        */
    uint64_t       uuid;    /**< UUID of the node            */
    struct mq_attr attr;    /**< POSIX mqueue attributes     */
    char name[UCM_MQIPC_URISIZE];   /** file name of the mqueue     */
};

/**
 * Return the exact size for the IPC mqueue peer options block.
 */
__attribute__((const))
inline static size_t mqipc_mqopts_size(void)
{
    return sizeof(struct mqipc_mqopts);
}

/**
 * @brief Initialize IPC mqueue peer options block.
 * @param opts Pointer to the structure to be initialized
 * @param name File system base name of the mqueue
 * @param uuid Unitue ID of the node
 * @return 0 on success
 * @return -EINVAL if the name is not a valid mqueue
 * @return -ENAMETOOLONG if the name longer than UCM_MQIPC_NAMESIZE
 * @return Errors returned by mq_open() with O_CREAT flag
 */
errno_t mqipc_mqopts_init(struct mqipc_mqopts* opts,
                          const char *name, uint64_t uuid);

/**
 * mqueue connection descriptor (local or remote peer)
 */
struct mqipc_peer
{
    mqd_t    fd;        /**< File descriptor for the mqueue                  */
    uint8_t  type;      /**< Type of the last message as per ucm_ipc_type    */
    uint8_t  stat;      /**< Status of the last message as per ucm_ipc_stat  */
    uint64_t node;      /**< ucm_ipcmsg::node                                */
    uint64_t uuid;      /**< ucm_ipcmsg::uuid                                */
    uint64_t init;      /**< Initialization constant                         */
};

/**
 * Return the exact size for the IPC connection descriptor
 */
__attribute__((const))
inline static size_t mqipc_peer_size(void)
{
    return sizeof(struct mqipc_peer);
}

/**
 * IPC server options block.
 */
struct mqipc_srvopts
{
    size_t cnumber;                 /**< Number of the elements in *clients */
    struct mqipc_peer *clients;     /**< Client nodes                       */
    mqipc_printer_t    printer;     /**< Printer callback                   */
    mqipc_callback_t   callback;    /**< Message callback                   */
    const char *client_name;        /**< Name of the clients mqueue         */
};

/**
 * mqueue IPC server node descriptor
 */
struct mqipc_server
{
    size_t cnumber;                 /**< Number of the elements in *clients */
    struct ucm_ipcmsg  buffer;      /**< The message buffer used for I/O    */
    struct mqipc_peer  server;      /**< Server MQ node                     */
    struct mqipc_peer *clients;     /**< Client nodes                       */
    const char *client_name;        /**< Name of the clients mqueue         */
    mqipc_printer_t    printer;     /**< Printer callback                   */
    mqipc_callback_t   callback;    /**< Message callback                   */
};

/**
 * Return the exact size for the IPC server descriptor.
 */
__attribute__((const))
inline static size_t mqipc_server_size(void)
{
    return sizeof(struct mqipc_server);
}

/**
 * Initialize the IPC control block in the ctx buff for an IPC server
 * @param ctx Buffer that holds the server IPC block.
 * @param opts MQ IPC options block
 * @return 0 if initialization is successful
 * @return -ENAMETOOLONG if uri string length exceeds the required limit.
 * @return -EINVAL if the uri does not start with '/'
 */
errno_t mqipc_server_init(struct mqipc_server *ctx,
                          const struct mqipc_mqopts *opts,
                          const struct mqipc_srvopts *srvopts);

/**
 * De-initialize IPC the server control block
 * @param ctc Previously initialized server IPC control block.
 * @return 0 if de-initialization is successful
 */
errno_t mqipc_server_fini(struct mqipc_server *ctx);

/**
 * @brief Receive a message and return as part of context
 * @param ctc Previously initialized server IPC control block.
 * @return 0 if de-initialization is successful
 */
errno_t mqipc_server_recv(struct mqipc_server *ctx);

/**
 * @brief Send a message stored as a part of context
 * @param ctc Previously initialized server IPC control block.
 * @return 0 if de-initialization is successful
 */
errno_t mqipc_server_send(struct mqipc_server *ctx);

/**
 * Listen (server) on initialized IPC control block
 * @param ctc Previously initialized server IPC control block.
 * @return 0 if de-initialization is successful
 */
errno_t mqipc_server_listen(struct mqipc_server *ctx);

/**
 * mqueue IPC client node descriptor
 */
struct mqipc_client
{
    struct ucm_ipcmsg buffer;
    struct mqipc_peer client;
    struct mqipc_peer server;
    mqipc_printer_t  printer;           /** Printer callback            */
};

/**
 * Return the exact size for the IPC client descriptor
 */
__attribute__((const))
inline static size_t mqipc_client_size(void)
{
    return sizeof(struct mqipc_client);
}

/**
 * Initialize the client control block in the ctx buff.
 * @param ctx Buffer that holds the client IPC block.
 * @param opts MQ IPC control block
 * @return 0 if initialization is successful
 * @return -ENAMETOOLONG if uri string length exceeds the required limit.
 * @return -EINVAL if the curi or suri do not start with '/'
 */
errno_t mqipc_client_init(struct mqipc_client *ctx, uint64_t uuid,
                          mqipc_printer_t printer,
                          const struct mqipc_mqopts *rxopts,
                          const struct mqipc_mqopts *txopts);

/**
 * De-initialize IPC the client control block
 * @param ctc Previously initialized client IPC block.
 * @return 0 if de-initialization is successful
 */
errno_t mqipc_client_fini(struct mqipc_client *ctx);

/**
 * Send a message to the server and receive its reply.
 * @param ctc Previously initialized client IPC block.
 * @return 0 if de-initialization is successful
 * @note The message should be loaded first in ctc->buffer
 */
errno_t mqipc_client_send(struct mqipc_client *ctx);

#ifdef UCM_BUILD_UT_HELPERS

void msdelay(struct timespec *tp, long sec);

void uuid_gettime(uint64_t* uuid);

errno_t _mqipc_create(const struct mqipc_mqopts *opts);

__attribute__((nonnull(1, 2)))
errno_t _mqipc_name_init(struct mqipc_mqopts *opts,
                                const char *name, uint64_t uuid);

__attribute__((nonnull(1)))
errno_t _peer_close(struct mqipc_peer *peer);

__attribute__((nonnull(1)))
errno_t _peer_open(struct mqipc_peer *peer, const char *name, int flags);

__attribute__((nonnull(1)))
errno_t _peer_init(struct mqipc_peer *peer);

__attribute__((nonnull(1)))
errno_t _peer_fini(struct mqipc_peer *peer);

__attribute__((nonnull(1, 2)))
errno_t _peer_recv(struct mqipc_peer *peer, struct ucm_ipcmsg *msg);

__attribute__((nonnull(1, 2)))
errno_t _peer_timedrecv(struct mqipc_peer *peer, struct ucm_ipcmsg *msg);

__attribute__((nonnull(1, 2)))
errno_t _peer_timedsend(struct mqipc_peer *peer, const struct ucm_ipcmsg *msg);

__attribute__((nonnull(1)))
struct mqipc_peer *_server_empty_slot(struct mqipc_server *ctx);

__attribute__((nonnull(1)))
errno_t _server_new_client(struct mqipc_server *ctx);

__attribute__((nonnull(1)))
int _server_helo(struct mqipc_server *ctx);

__attribute__((nonnull(1)))
errno_t _server_ping(struct mqipc_server *ctx);

__attribute__((nonnull(1)))
errno_t _server_exec(struct mqipc_server *ctx);

__attribute__((nonnull(1)))
errno_t _server_kill(struct mqipc_server *ctx);

__attribute__((nonnull(1)))
errno_t _server_zero(struct mqipc_server *ctx);

__attribute__((nonnull(1)))
errno_t _server_recv(struct mqipc_server *ctx);

#endif  /* UCM_BUILD_UT_HELPERS */

#ifdef __cplusplus
}
#endif

#endif    // UCM_AAP_LIBRARY__UCM_LIB_IPC__C_MQ_IPC_H_
