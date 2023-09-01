/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef SESSION_PROVIDER_UNICAST_LAYER
#define SESSION_PROVIDER_UNICAST_LAYER

#include "SessionId.hpp"
#include "pipc/protocol/DefaultLayer.hpp"

namespace pipc
{
namespace session
{
/**
 * @brief A Service Provider for a 1-to-1 connection to a User.
 *
 * Encapsulates session handling. This layer merely contains the
 * sessionId set by the Provider, so it can be inserted when sending
 * messages.
 */
class ProviderPtpLayer : public protocol::DefaultLayer
{
public:
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
    ProviderPtpLayer() : sessionId_(INVALID_SESSION_ID)
    {
    }

    /** @brief Initialize this layer. */
    void init(SessionId sessionId)
    {
        sessionId_ = sessionId;
    }

    // Put this layer's header into place
    void prepare(Header& header)
    {
        header.sessionId = sessionId_;
    }

private:
    /**
     * @brief Id of the session, if a connection has been established.
     *
     * @todo
     * Do we need sessionId here? Probably not, as it's the same as EndpointId.
     */
    SessionId sessionId_;
};

} // namespace session
} // namespace pipc

#endif // SESSION_PROVIDER_UNICAST_LAYER
