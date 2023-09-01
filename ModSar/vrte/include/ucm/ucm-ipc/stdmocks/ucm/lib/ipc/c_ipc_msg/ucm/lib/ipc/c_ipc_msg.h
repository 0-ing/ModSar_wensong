//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lip/ipc/c_ipc_msg.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_IPC__C_IPC_MSG_H_
#define UCM_AAP_LIBRARY__UCM_LIB_IPC__C_IPC_MSG_H_

#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <arpa/inet.h>

#if !defined (UCM_HAVE_ERRNO_T) && \
   (!defined(__STDC_LIB_EXT1__) || (__STDC_LIB_EXT1__ < 200509L))
#define UCM_HAVE_ERRNO_T
#ifdef __cplusplus
using errno_t = int;
#else
typedef int errno_t;
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifndef array_size
#define array_size(array) (sizeof(array) / sizeof((array)[0]))
#endif

#ifndef member_size
#define member_size(type, member) sizeof(((type *)0)->member)
#endif

__attribute__((pure))
inline static uint64_t hton64(uint64_t value)
{
    uint32_t hi = (uint32_t)(value >> 32);
    uint32_t lo = (uint32_t)(value & 0xFFFFFFFF);

    return ((((uint64_t)htonl(lo)) << 32) | (uint64_t)htonl(hi));
}

inline static uint64_t ntoh64(uint64_t value)
{
    uint32_t hi = (uint32_t)(value >> 32);
    uint32_t lo = (uint32_t)(value & 0xFFFFFFFF);

    return ((((uint64_t)ntohl(lo)) << 32) | (uint64_t)ntohl(hi));
}

#define UCM_IPCMSG_DATA_SIZE 256

/**
 * UCM IPC Message type
 */
enum ucm_ipc_type
{
    ucm_ipc_type_zero = 1,  /**< No reply is expected                    */
    ucm_ipc_type_helo,      /**< Initial message to assign node_id       */
    ucm_ipc_type_ping,      /**< Ping request/response type              */
    ucm_ipc_type_exec,      /**< Pass the message payload to upper layer */
    ucm_ipc_type_kill       /**< Server or client is going down          */
};

/**
 * @brief Return string name for a type
 */
const char *ucm_ipcmsg_type_str(enum ucm_ipc_type type);

/**
 * UCM IPC Message status type
 */
enum ucm_ipc_stat
{
    ucm_ipc_stat_success = 1,   /**< Request success                         */
    ucm_ipc_stat_failure,       /**< Request failure due to implementation   */
    ucm_ipc_stat_oserror,       /**< Request failure due to OS/system error  */
};

/**
 * @brief Return string name for a stat
 */
const char *ucm_ipcmsg_stat_str(enum ucm_ipc_stat stat);

/**
 * UCM IPC Message format.
 */
struct ucm_ipcmsg
{
    uint8_t  type;      /**< Type of the message as per ucm_ipc_type     */
    uint8_t  stat;      /**< Status of the message as per ucm_ipc_stat   */
    uint16_t size;      /**< Size of the valid data in the data buffer   */
#if (UINT_MAX - 0) == (UINT64_MAX - 0)
    uint32_t pad32;
#endif
    uint64_t node;      /**< id of the node initiating the message.      */
    uint64_t uuid;      /**< Unique id of the IPC node                   */
    uint8_t  data[UCM_IPCMSG_DATA_SIZE];    /** Message data            */
} __attribute__ ((packed));

__attribute__((const))
inline static size_t ucm_ipcmsg_msize(void)
{
    return sizeof(struct ucm_ipcmsg);
}

__attribute__((const))
inline static size_t ucm_ipcmsg_dsize(void)
{
    return member_size(struct ucm_ipcmsg, data);
}

__attribute__((pure))
inline static size_t ucm_ipcmsg_dfree(const struct ucm_ipcmsg *msg)
{
    return ucm_ipcmsg_dsize() - msg->size;
}

__attribute__((pure))
inline static size_t ucm_ipcmsg_dused(const struct ucm_ipcmsg *msg)
{
    return msg->size;
}

/**
 * @brief Convert to host byte order the values in the message header.
 * The message fields are check for validity and if there is an error,
 * ENINVAL is return.
 * @return 0 on success
 * @return EINVAL when the message contains invalid data
 */
errno_t ucm_ipcmsg_hton(struct ucm_ipcmsg *msg);

/**
 * @brief Convert to network byte order the values in the message header.
 * The message fields are check for validity and if there is an error,
 * ENINVAL is return.
 * @return 0 on success
 * @return EINVAL when the message contains invalid data
 */
errno_t ucm_ipcmsg_ntoh(struct ucm_ipcmsg *msg);

/**
 * @brief Read data from IPC message data buffer.
 * @param msg IPC message
 * @param dbuff Destination buffer -i.e. data to write form the IPC message
 * @param dlen Size of the destination buffer.
 * @return 0, if successful
 * @return ENOSPC if not enough space (len > dlen)
 * @return EINVAL if msg == NULL
 * @return EINVAL if dbuff == NULL
 * @return EINVAL if dlen == 0
 * @note msg and dbuff memory must not overlap
 * @note the cursor is only udated if there is no error
 */
errno_t ucm_ipcmsg_read(const struct ucm_ipcmsg *msg, size_t* cursor,
                        void *dbuff, size_t* dlen);

/**
 * @brief Append data to IPC message data buffer.
 * @param msg IPC message
 * @param sbuff Source buffer -i.e. data to append in to the IPC message
 * @param slen Size of the source buffer.
 * @return 0, if successful
 * @return ENOSPC if not enough space (slen > ucm_ipcmsg_dfree(msg))
 * @return EINVAL if msg == NULL
 * @return EINVAL if sbuff == NULL
 * @return EINVAL if slen == 0
 * @note msg and sbuff memory must not overlap
 */
errno_t ucm_ipcmsg_write(struct ucm_ipcmsg *msg,
                         const void *sbuff, size_t slen);

/**
 * @brief Create a HELO message
 * @param msg Message buffer
 * @param uuid Unique ID of the node
 * @param node Node number
 */
void ucm_ipcmsg_helo(struct ucm_ipcmsg *msg, uint64_t uuid, uint64_t node);

/**
 * @brief Create a PING message
 * @param msg Message buffer
 * @param uuid Unique ID of the node
 * @param node Node number
 */
void ucm_ipcmsg_ping(struct ucm_ipcmsg *msg, uint64_t uuid, uint64_t node);


/**
 * @brief Create a EXEC message
 * @param msg Message buffer
 * @param uuid Unique ID of the node
 * @param node Node number
 */
void ucm_ipcmsg_exec(struct ucm_ipcmsg *msg, uint64_t uuid, uint64_t node);

/**
 * @brief Create a KILL message
 * @param msg Message buffer
 * @param uuid Unique ID of the node
 * @param node Node number
 */
void ucm_ipcmsg_kill(struct ucm_ipcmsg *msg, uint64_t uuid, uint64_t node);

#ifdef __cplusplus
}
#endif

#endif    // UCM_AAP_LIBRARY__UCM_LIB_IPC__C_IPC_MSG_H_
