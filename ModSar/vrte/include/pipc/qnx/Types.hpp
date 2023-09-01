#ifndef PIPC_QNX_TYPES_HPP
#define PIPC_QNX_TYPES_HPP

#include <sys/iomsg.h>

namespace pipc
{
namespace qnx
{
/** @brief Type-alias for the _msg_info struct from QNX. */
using MsgInfo = struct _msg_info;
/** @brief Type-alias for the _client_info struct from QNX. */
using ClientInfo = struct _client_info;
/** @brief Type-alias for the OS-specific channel ID. */
using ChannelId = _Int32t;
/** @brief Type-alias for the OS-specific connection ID. */
using ConnectionId = int;
/** @brief Type-alias for the OS-specific receive ID. */
using ReceiveId = int;

} // namespace qnx
} // namespace pipc

#endif // PIPC_QNX_TYPES_HPP
