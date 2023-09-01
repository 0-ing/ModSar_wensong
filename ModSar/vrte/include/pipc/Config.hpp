#ifndef PROTOTYPES_DEFINES_HPP
#define PROTOTYPES_DEFINES_HPP

#include <cstddef>
#include <stdint.h>

namespace pipc
{
/**
 * @brief Central location for defines and typedefs
 *
 * @todo
 * Needs to be revisited & cleaned up later.
 *
 * @todo
 * Discuss about 3 possibilities for memory allocation:
 * - dynamic memory allocation vs.
 * - one allocator for the lib vs.
 * - one allocator per variable
 *
 * Dynamic memory allocation is not possible for safety-critical software,
 * while using one allocator per variable (as it is done currently)
 * quickly leads to memory bloat and makes it difficult to change settings.
 * Instead we can think about option 2:
 * Reserve a chunk of memory statically and allocate memory chunks from that
 * place. Such an allocator would be reasonably fast due to missing kernel calls,
 * while the configuration to increase or reduce memory consumption would be a lot
 * more straightforward.
 */

/** @brief The max. no. of processed managed by PIPC. */
#define PIPC_MAX_PROCESSES 64U

/** @brief The max. no. of processes connections per process */
#define PIPC_MAX_PROC_CONNECTIONS 64U

/** @brief The max. no. of proc sockets managed by PIPC. */
#define PIPC_MAX_PROC_SOCKETS 128U

/** @brief The max. length of a process identifier string. */
#define PIPC_MAX_PROCID_STRING_LENGTH 128U

/** @brief The max. no. of concurrent messages of a publisher. */
#define PIPC_MAX_CONCURRENT_PUBLISHER_MSGS 20U

/** @brief The max. no. of concurrent messages of a subscriber. */
#define PIPC_MAX_CONCURRENT_SUBSCRIBER_MSGS 10U

/** @brief The max. no. of users that can connect to a provider. */
#define PIPC_MAX_USERS_PER_PROVIDER 64U

/** @brief The max. no. of RPC server users. */
#define PIPC_MAX_SRVR_USERS 16U

/** @brief The max. no. of RPC request, which can be in flight. */
#define PIPC_MAX_CONCURRENT_CLIENT_REQUESTS 20U

/** @brief The max. pending rpc requests. */
#define PIPC_MAX_PENDING_RPC_REQUESTS 64U

/** @brief The max. no. of ports that can be assigned statically. */
#define PIPC_MAX_STATIC_PORTS 16U

/** @brief The max. no. of ports that can be assigned dynamically. */
#define PIPC_MAX_DYNAMIC_PORTS 512U

/** @brief The max. no. of service components, which can be handled by the daemon. */
#define PIPC_DAEMON_MAX_SERVICE_COMPONENTS 512U

/** @brief The max. no. of pending find requests a SD client can handle. */
#define PIPC_SD_CLIENT_MAX_PENDING_FIND_REQUESTS 64U

/**
 * @brief Max payload size.
 *
 * @remark
 * Ideally would be a message size spanning at max. one cache line, which is 64 Byte.
 * The slot's sequence counter and size info is 8 Byte (with E2E protection),
 * which leaves 56 Byte for the payload.
 * Due to inverse storage protection this would currently leave
 * max. 56/2 = 28 Byte for the max payload size.
 *
 * This is currently not sufficient due to the ProviderId format workaround.
 * For future reductions we have the following options:
 * - Try to decrease once ProviderId can become 8 Byte in total
 * - Use a CRC check instead of inverse storage for the payload
 * - Deactivate E2E protection (only payload or fully)
 */
static constexpr size_t PIPC_PIMP_APP_MAX_PAYLOAD_SIZE = 48U;
/**
 * @brief Max no. of messages, that can be buffered in a channel's queue.
 *
 * @remark
 * Must be a power of 2.
 */
static constexpr size_t PIPC_PIMP_APP_QUEUE_SIZE = 128U;

/** @brief PIPC Daemon path. */
#if defined(__QNX__)
static const char PIPC_DAEMON_PATH[] = "pipc_sd_daemon";
#else
static const char PIPC_DAEMON_PATH[] = "/tmp/pipc_sd_daemon";
#endif

/**
 * @brief Base directory for PIPC files.
 *
 * @todo
 * Separate read-only folder or not?
 */
#ifdef __QNX__
#    define PIPC_BASE_DIR "/dev/shmem/"
#else
#    define PIPC_BASE_DIR "/dev/shm/"
#endif

/** @brief Prefix for daemon sockets. */
static const char PIPC_PREFIX_SD_SOCKETS[] = "pipc_sd_";

/** @brief Prefix for proc sockets. */
static const char PIPC_PREFIX_PROC_SOCKETS[] = "pipc_proc_";

/** @brief Prefix for shared memory segments. */
static const char PIPC_PREFIX_SEGMENTS[] = "pipc_seg_";

/** @brief Max. no. of shm segments managed by PIPC. */
static constexpr size_t PIPC_MAX_SEGMENTS = 256U;

} // namespace pipc

#endif // PROTOTYPES_DEFINES_HPP
