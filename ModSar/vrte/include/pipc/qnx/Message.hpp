#ifndef PIPC_QNX_MESSAGE_HPP
#define PIPC_QNX_MESSAGE_HPP

#include <sys/dispatch.h>
#include <utility>

namespace pipc
{
namespace qnx
{
/**
 * @brief Definition of a message for QNX message passing.
 *
 * @remark
 * A message sent via QNX always incorporates the pulse
 * information at the beginning, even if it's not used.
 */
template<typename T>
struct Message
{
    /** @brief Constructor with forwarding arguments to the payload. */
    template<typename... Args>
    inline Message(Args&&... args) : pulse(), payload(std::forward<Args>(args)...)
    {
    }

    /** @brief QNX pulse information. */
    struct _pulse pulse;
    /** @brief The typed payload. */
    T payload;
};

/** @brief Template specialization for a pulse. */
template<>
struct Message<void>
{
    /** @brief QNX pulse information. */
    struct _pulse pulse;
};

using Pulse = Message<void>;

} // namespace qnx
} // namespace pipc

#endif // PIPC_QNX_MESSAGE_HPP
