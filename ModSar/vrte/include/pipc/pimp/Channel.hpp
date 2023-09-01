#ifndef TRANSPORT_CHANNEL_HPP
#define TRANSPORT_CHANNEL_HPP

#include "pipc/utils/FastSemaphore.hpp"
#include "pipc/utils/Semaphore.hpp"

namespace pipc
{
namespace pimp
{
/**
 * @brief Channel State.
 *
 * @remark
 * Not in use currently.
 *
 */
enum class ChannelState : uint8_t
{
    /** @brief Closed (=Inactive). */
    kClosed = 0,
    /** @brief Active channel means it is in use. */
    kActive
};

/**
 * @brief Definition of a channel
 *
 * A channel is a one-way communication medium for sending messages.
 * It contains a queue and an optional notification signal.
 *
 * @remark
 * The prototype concentrates only on channels with notification signal.
 *
 * @todo
 * We need to find a way to NOT put the notification mechanism into shmem
 * for PIMP channels (e.g. use named semaphore / pulse etc.).
 */
template<typename TQueue>
struct Channel
{
    using Queue = TQueue;
    /** @brief The queue used for the channel. */
    TQueue queue;
    /**
     * @brief The signal for send notifications
     *
     * @todo
     * Create notifier template param with:
     * - kNone      : Notifier stubbed
     * - kSemaphore : FastSemaphore, cnt with IntegralWrapper
     * - kPulse     : Use a QNX pulse if available
     */
    utils::FastSemaphore signal{0, true};
};

} // namespace pimp
} // namespace pipc

#endif // TRANSPORT_CHANNEL_HPP
