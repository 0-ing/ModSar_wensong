/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef SESSION_USER_LAYER_HPP
#define SESSION_USER_LAYER_HPP

#include "ProviderId.hpp"
#include "ProviderMsg.hpp"
#include "SessionId.hpp"
#include "UserMsg.hpp"
#include "pipc/Logger.hpp"
#include "pipc/ReturnCode.hpp"
#include "pipc/protocol/DefaultLayer.hpp"
#include "pipc/protocol/Protocol.hpp"

namespace pipc
{
namespace session
{
/**
 * @brief A Service User on the session layer.
 *
 * Encapsulates session handling.
 */
class UserPtpLayer : public protocol::DefaultLayer
{
public:
    using PayloadRx = ProviderMsg;
    using PayloadTx = UserMsg;

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

    /** @brief Default constructor. */
    UserPtpLayer() : providerId_(), sessionId_(INVALID_SESSION_ID), state_(State::kInvalid)
    {
    }

    /**
     * @brief Destructor callback.
     *
     * Sends a disconnect message, if a session is currently active.
     * In contrast to a requestDeactivation callback, this function does not
     * forward any state change notification to the upper layers, as the
     * owning object is about to be destroyed.
     *
     * @remark
     * This is explicitly not handled in the destructor due to 2 reasons:
     * In the destructor the additional endpoint information would be missing.
     * Also a proper destruction order of the layers
     * within the endpoint is not ensured, so the endpoint has to use this callback in its
     * own destructor.
     */
    template<size_t NLayer, typename... TLayers>
    void destroy(PtpEndpoint<TLayers...>& endpoint)
    {
        if (state_ == State::kValid || state_ == State::kBusy)
        {
            Message<UserMsg, NLayer, TLayers...> pdu;
            pdu.header().sessionId = INVALID_SESSION_ID;
            pdu.payload().template emplace<UserMsgs::DisconnectNotification>();
            state_ = State::kIdle;
            endpoint.send(pdu);
        }
    }

    /** @brief Initialize this layer. */
    void init(ProviderId providerId, State state = State::kInvalid)
    {
        providerId_ = providerId;
        state_      = state;
    }

    /** @brief Initialize this layer. */
    void init()
    {
        state_ = State::kIdle;
    }

    /** @brief Put this layer's header into place. */
    void prepare(Header& header)
    {
        // std::cout << "Session: Inserting header (Session Id " << (int)sessionId_ << ")" << std::endl;
        header.sessionId = sessionId_;
    }

    /** @brief Check that the endpoint is valid on this layer. */
    bool valid() const
    {
        return state_ == State::kValid;
    }

    /** @brief Get the ProviderId we want to connect to. */
    ProviderId& getProviderId()
    {
        return providerId_;
    }

    /** @brief Get the connection state. */
    State getState()
    {
        return state_;
    };

    /** @brief Get the session Id. */
    SessionId getSessionId()
    {
        return sessionId_;
    }

    /** @brief Process a state change in the transport layer. */
    template<size_t N, typename... TLayers>
    inline void processNotification(PtpEndpoint<TLayers...>& endpoint, StateChange change)
    {
        PIPC_LOG_VERBOSE() << "UserPtpLayer: Received notification " << protocol::ToString(change) << ": "
                           << providerId_.toString() << std::endl;
        bool notificationUnderstood = false;
        switch (state_)
        {
        // We are connected or can connect
        case State::kValid:
        case State::kIdle:
        case State::kBusy:
            if (change == StateChange::kInvalid)
            {
                state_ = State::kInvalid;
                protocol::ForwardNotification<N>(endpoint, StateChange::kInvalid);
                notificationUnderstood = true;
            }
            // A state change from valid to valid could happen in case
            // we have multiple users for the same ProviderId
            // TODO: Filter this in the transport layer instead of here
            else if (state_ == State::kValid && change == StateChange::kValid)
            {
                notificationUnderstood = true;
            }
            break;
        // The endpoint isn't valid
        case State::kInvalid:
            if (change == StateChange::kValid)
            {
                state_ = State::kIdle;
                protocol::ForwardNotification<N>(endpoint, StateChange::kIdle);
                notificationUnderstood = true;
            }
            break;
        default:
            break;
        }
        // Received a StateChange::kIdle, this should never happen
        if (!notificationUnderstood)
        {
            PIPC_LOG_ERROR() << "UserPtpLayer: Couldn't map unexpected state change from lower layer: "
                             << providerId_.toString() << std::endl;
        }
    }

    /**
     * @brief Try to establish a connection.
     */
    template<size_t NLayer, typename... TLayers>
    ReturnCode requestActivation(PtpEndpoint<TLayers...>& endpoint)
    {
        switch (state_)
        {
        // We are already connected
        case State::kValid:
            return ReturnCode::kOk;
            break;
        // The endpoint is invalid or the connection has been denied
        // TODO: Be more precise?
        case State::kInvalid:
            return ReturnCode::kPermissionDenied;
            break;
        // We can request a connection
        case State::kIdle:
            Message<UserMsg, NLayer, TLayers...> pdu;
            pdu.header().sessionId = INVALID_SESSION_ID;
            pdu.payload().template emplace<UserMsgs::ConnectionRequest>(providerId_);
            state_ = State::kBusy;
            // std::cout << "UserPtpLayer: Sending connection request..." << std::endl;
            return endpoint.send(pdu);
            break;
        // We have already requested a connection, return silently
        case State::kBusy:
            return ReturnCode::kOk;
            break;
        default:
            break;
        }
        // This should never be reached
        return ReturnCode::kGeneralError;
    }

    /**
     * @brief Disconnect from the provider.
     */
    template<size_t NLayer, typename... TLayers>
    ReturnCode requestDeactivation(PtpEndpoint<TLayers...>& endpoint)
    {
        if (state_ == State::kValid || state_ == State::kBusy)
        {
            Message<UserMsg, NLayer, TLayers...> pdu;
            pdu.header().sessionId = INVALID_SESSION_ID;
            pdu.payload().template emplace<UserMsgs::DisconnectNotification>();
            state_ = State::kIdle;
            protocol::ForwardNotification<NLayer>(endpoint, StateChange::kIdle);
            endpoint.send(pdu);
        }
        return ReturnCode::kOk;
    }

    /** @brief Receive a message. */
    template<size_t NLayer, typename... TLayers>
    inline ReturnCode receive(PtpEndpoint<TLayers...>& endpoint, Message<PayloadRx, NLayer, TLayers...>& pdu)
    {
        SessionId sessionId = pdu.header().sessionId;
        // Fast path: Assume we get a message for the next layer
        if (sessionId != INVALID_SESSION_ID)
        {
            // Fast path: Assume we get the correct Session Id
            if (sessionId == sessionId_)
            {
                // std::cout << "Forwarding message..." << std::endl;
                return protocol::Forward<NLayer>(endpoint, pdu);
            }
            // Incorrect session Id = invalid message
            else
            {
                // std::cout << "Session layer: Received message with incorrect Session Id." << std::endl;
                return ReturnCode::kSessionError;
            }
        }
        // We actually got a connection message
        else
        {
            ProviderMsg& providerMsg = pdu.payload();
            bool msgUnderstood       = false;
            switch (state_)
            {
            case State::kBusy:
                switch (providerMsg.index())
                {
                case ProviderMsgs::Type::kConnectionAcknowledge:
                    sessionId_ = utils::Get<ProviderMsgs::kConnectionAcknowledge>(providerMsg).sessionId;
                    state_     = State::kValid;
                    protocol::ForwardNotification<NLayer>(endpoint, StateChange::kValid);
                    msgUnderstood = true;
                    PIPC_LOG_DEBUG() << "UserPtpLayer: Connection successful: " << providerId_.toString() << std::endl;
                    break;
                case ProviderMsgs::Type::kConnectionDeny:
                    PIPC_LOG_ERROR() << "UserPtpLayer: Connection was denied: " << providerId_.toString() << std::endl;
                    state_ = State::kInvalid;
                    protocol::ForwardNotification<NLayer>(endpoint, StateChange::kInvalid);
                    msgUnderstood = true;
                    break;
                default:
                    break;
                }
            default:
                break;
            }
            if (!msgUnderstood)
            {
                PIPC_LOG_ERROR() << "UserPtpLayer: Couldn't understand provider msg.: " << providerId_.toString()
                                 << std::endl;
                return ReturnCode::kSessionError;
            }
        }
        return ReturnCode::kOk;
    }

private:
    /** @brief Some Id to identify the provider. */
    ProviderId providerId_;
    /** @brief Id of the session, if a connection has been established. */
    SessionId sessionId_;
    /**
     * @brief Current state of this layer.
     *
     * The state mappings are as as follows:
     *  - kValid   : Working connection
     *  - kInvalid : Connection denied
     *  - kIdle    : Connection can be requested
     *  - kBusy    : Waiting for reply to connection request
     */
    State state_;
};

} // namespace session
} // namespace pipc

#endif // SESSION_USER_LAYER_HPP
