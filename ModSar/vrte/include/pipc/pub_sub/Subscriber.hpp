/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PUB_SUB_SUBSCRIBER_HPP
#define PUB_SUB_SUBSCRIBER_HPP

#include "SubscriberBase.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/session/ProviderId.hpp"
#include "pipc/transport/Mailbox.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief Subscriber for type T.
 */
template<typename T, size_t MaxMsgs = PIPC_MAX_CONCURRENT_SUBSCRIBER_MSGS>
class Subscriber : public SubscriberBase<>
{
public:
    /** @brief Constructor for registering the Subscriber for dispatch. */
    Subscriber(const session::ProviderId& providerId, rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : SubscriberBase(providerId, runtime), values_()
    {
        auto& dispatcher = runtime.getDispatcher();
        auto port        = dispatcher.registerCbk(&Receive, &ReceiveValue, *this);
        endpoint_.getLayer<protocol::kTransport>().setSrcPort(port);
        if (port != transport::INVALID_PORT)
        {
            // TODO: Can we get an invalid ReturnCode?
            runtime_.registerUser(*this);
        }
        else
        {
            PIPC_LOG_ERROR() << "Couldn't register Subscriber with ProviderId " << providerId.toString() << std::endl;
        }
    }

    /** @brief Try to receive a value from the mailbox. */
    inline bool tryReceive(T& value)
    {
        auto ret = values_.msgs_.try_pop(value);
        if (ret == ReturnVal::kOk)
        {
            return true;
        }
        return false;
    }

private:
    /**
     * @brief Wrapper to receive a value.
     */
    static void ReceiveValue(Subscriber& obj, pimp::Socket& socket, transport::Datagram<T>* msg)
    {
        obj.receiveValue(socket, *msg);
    }

    /** @brief Function for receiving a value. */
    inline void receiveValue(pimp::Socket& socket, const transport::Datagram<T>& msg)
    {
        // Assert for the correct identity of the publisher
        if (this->endpoint_.template getLayer<protocol::kNetwork>().getSocket() == &socket)
        {
            // Assert that we expect a message at all
            if (getSubscriptionState() == SubscriberPublicState::kSubscribed)
            {
                // TODO: Handle mailbox full case
                values_.msgs_.try_push(msg.payload());
                auto& handler = this->getAppLayer().getEventReceiveHandler().read();
                if (handler)
                {
                    handler();
                }
            }
            else
            {
                PIPC_LOG_INFO() << "Subscriber: Unexpected data msg received." << std::endl;
            }
        }
        else
        {
            PIPC_LOG_INFO() << "Subscriber: Got data message with invalid identity." << std::endl;
        }
    }

    /** @brief Mailbox with received values. */
    transport::Mailbox<T, MaxMsgs> values_;
};

} // namespace pub_sub
} // namespace pipc

#endif // PUB_SUB_SUBSCRIBER_HPP
