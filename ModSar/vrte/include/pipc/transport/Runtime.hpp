/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef PIPC_TRANSPORT_RUNTIME_HPP
#define PIPC_TRANSPORT_RUNTIME_HPP

#include "MsgDispatcher.hpp"

namespace pipc
{
namespace transport
{
/**
 * @brief Runtime of PIPC.
 *
 * The runtime contains singleton instances of all classes, which we (usually)
 * need only once.
 */
class Runtime
{
private:
    /** @brief No instances of Runtime. */
    Runtime()
    {
    }

public:
    /** @brief No copy operations. */
    Runtime(Runtime const&) = delete;
    void operator=(Runtime const&) = delete;

    /** @brief Get the message dispatcher. */
    static MsgDispatcher& GetDispatcher()
    {
        static MsgDispatcher instance;
        return instance;
    }
};

} // namespace transport
} // namespace pipc

#endif // PIPC_TRANSPORT_RUNTIME_HPP
