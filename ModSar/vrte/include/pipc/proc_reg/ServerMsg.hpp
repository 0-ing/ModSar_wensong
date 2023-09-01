#ifndef PIPC_PROC_REG_SERVER_MSG_HPP
#define PIPC_PROC_REG_SERVER_MSG_HPP

#include "pipc/Config.hpp"
#include "pipc/NodeId.hpp"
#include "pipc/utils/FixedString.hpp"

#include <stdint.h>
#include <unistd.h>

namespace pipc
{
namespace proc_reg
{
struct ServerMsg
{
    /** @brief List of all possible messages a server process can send. */
    enum class Id : uint8_t
    {
        /** @brief Registration acknowledged. */
        kRegisterAck = 0,
        /** @brief Registration denied. */
        kRegisterDeny
    };

    /** @brief ID of the server msg. */
    Id id;
    /** @brief The Node Id, which the daemon has mapped for the proc. */
    NodeId nodeId;
};

} // namespace proc_reg
} // namespace pipc

#endif // PIPC_PROC_REG_SERVER_MSG_HPP
