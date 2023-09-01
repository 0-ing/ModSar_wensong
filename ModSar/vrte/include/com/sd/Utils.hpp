#ifndef COM_SD_UTILS_HPP
#define COM_SD_UTILS_HPP

#include "pipc/pimp/Socket.hpp"
#include "sd/ClientMsg.hpp"

namespace com
{
namespace sd
{
/**
 * @brief Send the remaining instance ids to the socket & port.
 *
 * If there is more than one element in instanceIds,
 * starts with the second element and keeps sending InstanceIdList messages,
 * until all InstanceIdentifiers are transmitted.
 *
 * @tparam TMsgContainer The type of the message container (either ClientMsg or ServerMsg).
 * @tparam TMsg The type of the message (either ClientMsgs::InstanceIdList or ServerMsg::InstanceIdList).
 * @tparam TMsg The type of the instance container (either InstanceIdentifierContainer or InstanceIdContainer).
 * @return bool Whether send was successful.
 */
template<typename TMsgContainer, typename TMsg, typename TInstanceContainer>
bool SendRemainingInstanceIds(pipc::pimp::Socket& socket,
                              pipc::transport::Port port,
                              const TInstanceContainer& container)
{
    size_t remainingInstanceIds = container.size() - 1U;
    if (remainingInstanceIds)
    {
        size_t i = 1U;
        pipc::transport::Datagram<TMsgContainer> idListMsg;
        idListMsg.header().dstPort = port;
        auto& idListContent        = idListMsg.payload().template emplace<TMsg>();
        while (remainingInstanceIds >= 4U)
        {
            idListContent.instanceIds[0] = container[i++];
            idListContent.instanceIds[1] = container[i++];
            idListContent.instanceIds[2] = container[i++];
            idListContent.instanceIds[3] = container[i++];
            if (socket.send(idListMsg) != pipc::ReturnVal::kOk)
            {
                return false;
            }
            remainingInstanceIds -= 4U;
        }

        if (remainingInstanceIds)
        {
            size_t j = 0U;
            do
            {
                idListContent.instanceIds[j++] = container[i++];
                remainingInstanceIds--;
            } while (remainingInstanceIds > 0);
            if (socket.send(idListMsg) != pipc::ReturnVal::kOk)
            {
                return false;
            }
        }
    }
    return true;
}

} // namespace sd
} // namespace com

#endif // COM_SD_UTILS_HPP
