#ifndef PIPC_PIMP_MSG_RECEIVER_HPP
#define PIPC_PIMP_MSG_RECEIVER_HPP

#include "pipc/utils/Command.hpp"
#include "pipc/utils/Placeholder.hpp"

namespace pipc
{
namespace pimp
{
/**
 * @brief A generic message receiver for network layer messages.
 *
 * This class stores a Command and provides a receive function,
 * which calls the Command with the receive parameters.
 * It can be used together with a PIMP listener to build a generic
 * message receiver.
 *
 * @todo
 * Not sure if we should add some assertions, e.g. TSocket deriving from pimp::Socket.
 */
class MsgReceiver
{
    /** @brief A command with any Socket and message type. */
    using Command = utils::Command_1<void*, void, utils::Placeholder&, utils::Placeholder&>;

public:
    /** @brief Constructor with a given command. */
    MsgReceiver(const Command& command) : command_(command)
    {
    }

    /** @brief Constructor with forwarding arguments. */
    template<typename... TArgs>
    MsgReceiver(TArgs&&... args) : command_(std::forward<TArgs>(args)...)
    {
    }

    /** @brief Receive a message and forward it to the Command. */
    template<typename TSocket>
    inline void receive(TSocket& socket, utils::Placeholder& msg)
    {
        auto& tmpSocket = *reinterpret_cast<utils::Placeholder*>(&socket);
        command_(tmpSocket, msg);
    }

    /** @brief Set the receive command. */
    template<typename TClass, typename TSocket, typename TMsg>
    inline void set(void (*fnc)(TClass*, TSocket&, TMsg&), TClass* obj)
    {
        auto tmpFnc = reinterpret_cast<void (*)(void*, utils::Placeholder&, utils::Placeholder&)>(
            reinterpret_cast<void*>(fnc));
        command_.set(tmpFnc, obj);
    }

private:
    /** @brief The command called upon message reception. */
    Command command_;
};

} // namespace pimp
} // namespace pipc

#endif // PIPC_PIMP_MSG_RECEIVER_HPP
