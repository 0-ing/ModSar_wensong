/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_TRANSPORT_MSG_DISPATCHER_HPP
#define PIPC_TRANSPORT_MSG_DISPATCHER_HPP

#include "DispatchEntry.hpp"
#include "Message.hpp"
#include "Port.hpp"
#include "pipc/Config.hpp"
#include "pipc/utils/ErrorHandler.hpp"
#include "pipc/utils/Expect.hpp"

#include <array>

namespace pipc
{
namespace transport
{
namespace internal
{
/**
 * @brief Class for dispatching messages.
 *
 * The MsgDispatcher has a table with one entry per Port, which is used upon dispatch.
 * It provides APIs to register and unregister callbacks for dispatching.
 *
 * @todo
 * Clean handling of registering and unregistering to prevent race conditions:
 * - Unregister & concurrent register
 */
template<size_t NDynamic, size_t NStatic>
class MsgDispatcher
{
    /** @brief A Message up to the transport layer (to get the destination port). */
    using TransportMsg = transport::Message<protocol::Placeholder>;

public:
    /** @brief Default constructor. */
    constexpr MsgDispatcher() noexcept : dispatchTable_(), lastUsedPort_(NStatic + NDynamic - 1U)
    {
    }

    /**
     * @brief Get no. of static ports.
     *
     * @return size_t The no. of available
     */
    static constexpr size_t GetStaticPorts()
    {
        return NStatic;
    }

    /**
     * @brief Register a callback and return the mapped port no.
     */
    template<typename... Args>
    Port registerCbk(Args&&... args)
    {
        Port port;
        if (reservePort(port))
        {
            dispatchTable_[port].set(std::forward<Args>(args)...);
            return port;
        }
        else
        {
            // TODO: Critical error handler shall be invoked by the API caller,
            // not by the transport layer itself
            utils::ErrorHandler::CriticalError(utils::ErrorType::kGeneral, "Could not find a free port!");
            return INVALID_PORT;
        }
    }

    /**
     * @brief Register a callback for a static port.
     *
     * Registration for static port works only once.
     * If the port has already been assigned or out of range, an error will be returned.
     *
     * @return
     *   - kOk if registration was successful
     *   - kPortInUse if the port is already occupied
     *   - kPortOutOfBounds if the port is higher than the max. allowed value
     */
    template<typename... Args>
    ReturnCode registerCbk(Port port, Args&&... args)
    {
        if (port >= NStatic)
        {
            return ReturnCode::kPortOutOfBounds;
        }
        if (dispatchTable_[port])
        {
            return ReturnCode::kPortInUse;
        }
        dispatchTable_[port].set(std::forward<Args>(args)...);
        return ReturnCode::kOk;
    }

    /** @brief Unregister a callback, resetting the function to nullptr. */
    void unregisterCbk(Port port)
    {
        dispatchTable_[port].reset();
    }

    /** @brief Receive a given message and dispatch it. */
    template<typename TSocket>
    ReturnCode receive(TSocket& socket, utils::Placeholder& msg)
    {
        auto& transportMsg = *reinterpret_cast<TransportMsg*>(&msg);
        auto tmp           = transportMsg.header().dstPort;
        auto port          = GetPort(tmp);
        size_t callbackIdx = (tmp & 1U);
        if (EXPECT_UNLIKELY(port >= dispatchTable_.size()))
        {
            PIPC_LOG_ERROR() << "MsgDispatcher: Couldn't dispatch msg, port OOB: " << port << std::endl;
            return ReturnCode::kTransportError;
        }
        auto& entry = dispatchTable_[port];
        if (EXPECT_UNLIKELY(!entry(callbackIdx, socket, &msg)))
        {
            // HINT:
            // Erroneous dispatches are expected, as there are unavoidable race conditions if service components
            // shut down at about the same time.
            if (!callbackIdx)
            {
                PIPC_LOG_WARN() << "MsgDispatcher: Couldn't dispatch ctrl msg to dst port: " << port << std::endl;
            }
            else
            {
                PIPC_LOG_WARN() << "MsgDispatcher: Couldn't dispatch datagram to dst port: " << port << std::endl;
            }
            return ReturnCode::kTransportError;
        }
        return ReturnCode::kOk;
    }

private:
    /**
     * @brief Get the next dynamic port no.
     *
     * Utility function which takes care of a proper wrap-around.
     *
     * @param port The previous port.
     * @return Port The next port.
     */
    Port getNextDynamicPort(Port port)
    {
        port++;
        if (port >= (NDynamic + NStatic))
        {
            port = NStatic;
        }
        return port;
    }

    /**
     * @brief Try to reserve a port for a new dispatch entry.
     *
     * We can re-use old ports here later. The entries' context could act as
     * a reservation mechanism with a CAS. We will also have to revisit
     * the mechanisms between set and reset to distinguish between first-time
     * usage of an entry (direct set) and re-usage (reset and then set).
     */
    bool reservePort(Port& port)
    {
        auto lastPort    = lastUsedPort_.load(std::memory_order_relaxed);
        Port currentPort = lastPort;
        // Start with the next port that is most likely free:
        // We increment first and then check whether we can reserve
        do
        {
            currentPort = getNextDynamicPort(currentPort);
            if (dispatchTable_[currentPort].tryReserve())
            {
                port = currentPort;
                lastUsedPort_.store(currentPort, std::memory_order_relaxed);
                return true;
            }
        } while (currentPort != lastPort);

        return false;
    }

    /** @brief Table for message callbacks. */
    std::array<DispatchEntry, NDynamic + NStatic> dispatchTable_;
    /** @brief The last assigned dynamic port. */
    std::atomic<Port> lastUsedPort_;
};

} // namespace internal

/** @brief The MsgDispatcher used in PIPC with default configuration. */
using MsgDispatcher = internal::MsgDispatcher<PIPC_MAX_DYNAMIC_PORTS, PIPC_MAX_STATIC_PORTS>;

} // namespace transport
} // namespace pipc

#endif // PIPC_TRANSPORT_MSG_DISPATCHER_HPP
