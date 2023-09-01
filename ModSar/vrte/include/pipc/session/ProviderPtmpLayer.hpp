/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_SESSION_PROVIDER_LAYER_HPP
#define PIPC_SESSION_PROVIDER_LAYER_HPP

#include "ProviderId.hpp"
#include "ProviderMsg.hpp"
#include "SessionId.hpp"
#include "UserMsg.hpp"
#include "pipc/Logger.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/protocol/Protocol.hpp"
#include "pipc/protocol/PtmpEndpoint.hpp"
#include "pipc/transport/Port.hpp"

namespace pipc
{
namespace session
{
/**
 * @brief Ptmp Layer for a Service Provider.
 *
 * The Provider PtmpLayer provides means to use the single endpoint
 * of a Provider for multiple client connections.
 * Incoming messages to the provider's endpoint are checked by this layer
 * first and then either routed to an existing endpoint or a new one is allocated.
 *
 * @param NUsers The max no. of users that can be connected to the provider.
 * @param TUser  The datatype to be used for a user slot.
 */
class ProviderPtmpLayer : public protocol::DefaultLayer
{
public:
    using PayloadRx = UserMsg;
    using Socket    = pimp::Socket;

    struct Header
    {
        /** @brief Equal operator (used mainly for testing). */
        inline bool operator==(const Header& other) const
        {
            return (sessionId == other.sessionId);
        }

        /** @brief Session ID (255 is reserved for session layer messages). */
        SessionId sessionId;
    };

    /**
     * @brief Default constructor.
     *
     * @remark
     * By convention, the provider always starts with asking for registration.
     */
    ProviderPtmpLayer() : state_(State::kBusy)
    {
    }

    /** @brief Destructor. */
    // ~ProviderPtmpLayer()
    // {
    //     // We leave out shut down notifications for now and let the daemon handle it
    //     ProviderMsg msg{ProviderMsg::Id::kShutdownNotification};
    //     for (SessionId id = 0; id < NUsers; id++)
    //     {
    //         auto user = getUser(id);
    //         if (user)
    //         {
    //             user->endpoint.sendCtrl(msg);
    //         }
    //     }
    // }

    /** @brief Initalization with a ProviderId. */
    constexpr void init(ProviderId providerId)
    {
        providerId_ = providerId;
    }

    /**
     * @brief Get the underlying ProviderId.
     *
     * @todo
     * Not sure where to put this best yet.
     */
    const ProviderId& getProviderId()
    {
        return providerId_;
    }

    State getState()
    {
        return state_;
    }

    /** @brief Process a state change notification (usually initiated from the runtime, NOT from transport). */
    template<size_t N, typename TEndpoint, typename... TArgs>
    inline void processNotification(TEndpoint& endpoint, StateChange change, TArgs&&... args)
    {
        bool notificationUnderstood = false;
        switch (state_)
        {
        // We are waiting for a registration reply
        case State::kBusy:
            // Permission granted :-)
            if (change == StateChange::kValid)
            {
                state_                 = State::kIdle;
                notificationUnderstood = true;
            }
            // Permission denied :-(
            else if (change == StateChange::kInvalid)
            {
                state_                 = State::kInvalid;
                notificationUnderstood = true;
            }
            break;
        // Any other state/change combination would be unexpected
        default:
            break;
        }
        // This should never happen
        if (!notificationUnderstood)
        {
            PIPC_LOG_ERROR() << "ProviderPtmpLayer: Couldn't map unexpected state change from lower layer."
                             << std::endl;
            return;
        }
        protocol::ForwardNotification<N>(endpoint, change, std::forward<TArgs>(args)...);
    }

    /** @brief Receive a message. */
    template<size_t NLayer,
             typename TMsg,
             size_t NEndpoints,
             typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7>
    inline ReturnCode receive(protocol::PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
                              TMsg& pdu,
                              Socket& socket)
    {
        // TODO: Send error reply back?
        if (state_ != State::kValid)
        {
            PIPC_LOG_ERROR() << "ProviderPtmpLayer: Got message while not offering." << std::endl;
            return ReturnCode::kSessionError;
        }

        SessionId msgSessionId = pdu.header().sessionId;
        // Fast path: Assume we get a message for the next layer
        if (msgSessionId != INVALID_SESSION_ID)
        {
            auto userEndpoint = endpoint.get(msgSessionId);
            // Fast path: Assume we get a correct Session Id
            if (userEndpoint)
            {
                // std::cout << "ProviderPtmpLayer: Forwarding message..." << std::endl;
                // Fast path: Assume the received session Id is valid
                auto ret = userEndpoint->receive(pdu, socket);
                if (ret == ReturnCode::kOk)
                {
                    return protocol::Forward<NLayer>(endpoint, pdu, *userEndpoint);
                }
                else
                {
                    // If network or transport report an error it is due to a session id
                    // mismatch, so return a kSessionError.
                    // std::cout << "Session layer: Received message with incorrect Session Id." << std::endl;
                    return ReturnCode::kSessionError;
                }
            }
            else
            {
                // std::cout << "Session layer: Received message with incorrect Session Id." << std::endl;
                return ReturnCode::kSessionError;
            }
        }
        // We actually got a connection message
        else
        {
            PtpEndpoint<T0, T1, T2, T3>* userEndpoint;
            // SessionId == EndpointId == index into user array
            SessionId sessionId;
            // TODO: We create the endpoint manually currently
            // Implement createEndpoint function from Layer N, which
            // fills the layer info backwards?
            protocol::PtpEndpoint<T0, T1, T2, T3> tmpEndpoint;
            auto dstPort = transport::GetPort(pdu.template getHeader<protocol::kTransport>().srcPort);
            auto srcPort = transport::GetPort(pdu.template getHeader<protocol::kTransport>().dstPort);
            tmpEndpoint.init(socket, dstPort, srcPort);
            UserMsg& userMsg = pdu.payload();

            switch (userMsg.index())
            {
            case UserMsgs::Type::kConnectionRequest:
            {
                PIPC_LOG_VERBOSE() << "Provider " << providerId_.toString() << ": Received connection request from node "
                                 << socket.getNodeId() << ", port " << dstPort << std::endl;

                auto providerMsg               = protocol::CreateMessage<ProviderMsg, NLayer>(tmpEndpoint);
                providerMsg.header().sessionId = INVALID_SESSION_ID;
                // Check for the right ProviderId before proceeding
                bool valid = (providerId_ == utils::Get<UserMsgs::kConnectionRequest>(userMsg).providerId);
                if (valid)
                {
                    // Only add a new entry if the endpoint isn't already there
                    userEndpoint = endpoint.template find<protocol::kTransport>(tmpEndpoint, sessionId);
                    if (!userEndpoint)
                    {
                        PIPC_LOG_DEBUG() << "Provider " << providerId_.toString()
                                         << ": Creating new endpoint entry for node " << socket.getNodeId() << ", port "
                                         << dstPort << std::endl;

                        // TODO: IAM callback can be put here
                        userEndpoint = endpoint.allocate(sessionId);
                        valid        = (userEndpoint != nullptr);
                        if (valid)
                        {
                            // After this assignment tmpEndpoint is moved into the user list,
                            // do not change it anymore!
                            *userEndpoint = std::move(tmpEndpoint);
                            userEndpoint->template getLayer<protocol::kSession>().init(sessionId);
                            protocol::ForwardNotification<NLayer>(endpoint, StateChange::kValid, *userEndpoint);
                        }
                    }
                }
                // User has been added or already exists
                if (valid)
                {
                    providerMsg.payload().template emplace<ProviderMsgs::ConnectionAcknowledge>(sessionId);
                }
                // No user slots available or wrong ProviderId
                else
                {
                    PIPC_LOG_WARN() << "Provider " << providerId_.toString()
                                    << ": Endpoint entry could not be added for " << socket.getNodeId() << ", port "
                                    << dstPort << std::endl;
                    providerMsg.payload().template emplace<ProviderMsgs::ConnectionDeny>();
                }
                tmpEndpoint.send(providerMsg);
                break;
            }
            case UserMsgs::Type::kDisconnectNotification:
            {
                PIPC_LOG_VERBOSE() << "Provider " << providerId_.toString() << ": Received disconnect notification from node "
                                 << socket.getNodeId() << ", port " << dstPort << std::endl;
                userEndpoint = endpoint.template find<protocol::kTransport>(tmpEndpoint, sessionId);
                if (userEndpoint)
                {
                    // Inform the upper layer first, after that it is safe to deallocate
                    protocol::ForwardNotification<NLayer>(endpoint, StateChange::kInvalid, *userEndpoint);
                    endpoint.deallocate(sessionId);
                }
                break;
            }
            default:
                std::cout << "ProviderPtmpLayer: Couldn't understand user msg." << std::endl;
                return ReturnCode::kSessionError;
            }
        }
        return ReturnCode::kOk;
    }

    /** @brief Start offering. */
    ReturnCode startOffer()
    {
        switch (state_)
        {
        // Already offering
        case State::kValid:
            return ReturnCode::kOk;
        // Ready to offer
        case State::kIdle:
            state_ = State::kValid;
            return ReturnCode::kOk;
        // Offer request in progress or not allowed to offer
        case State::kInvalid:
        case State::kBusy:
        default:
            return ReturnCode::kPermissionDenied;
        }
    }

    /** @brief Stop offering. */
    void stopOffer()
    {
        switch (state_)
        {
        // Already offering
        case State::kValid:
            state_ = State::kIdle;
            break;
        // For all other cases we are already not offering
        case State::kIdle:
        case State::kInvalid:
        case State::kBusy:
        default:
            break;
        }
    }

private:
    /** @brief The ProviderId used by the service. */
    ProviderId providerId_;
    /**
     * @brief Current state of this layer.
     *
     * The state mappings are as as follows:
     *  - kValid   : Provider is active (= offering)
     *  - kInvalid : Providing has been denied
     *  - kIdle    : Provider is inactive, but can be activated (= not offering)
     *  - kBusy    : Waiting for reply to registration request
     *
     * @todo
     * Implement the possiblity that we have been denied the provision
     * (due to IAM denial or duplicate ProviderId)
     */
    State state_{State::kBusy};
};

} // namespace session
} // namespace pipc

#endif // PIPC_SESSION_PROVIDER_LAYER_HPP
