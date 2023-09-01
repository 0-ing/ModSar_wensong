#ifndef PIPC_PROC_REG_CLIENT_MSG_HPP
#define PIPC_PROC_REG_CLIENT_MSG_HPP

#include "pipc/Config.hpp"
#include "pipc/utils/FixedString.hpp"

#include <stdint.h>
#include <unistd.h>

namespace pipc
{
namespace proc_reg
{
struct ClientMsg
{
    /** @brief List of all possible messages a client process can send. */
    enum class Id : uint8_t
    {
        /** @brief Register request. */
        kRegisterReq = 0,
        /** @brief Unregister request. */
        kUnregisterReq
    };

    /** @brief ID of the request. */
    Id id;
    /** @brief Process Identifier String. */
    char procIdentifier[PIPC_MAX_PROCID_STRING_LENGTH];
    /** @brief The process' uid. */
    uid_t uid;
};

} // namespace proc_reg
} // namespace pipc

#endif // PIPC_PROC_REG_CLIENT_MSG_HPP
