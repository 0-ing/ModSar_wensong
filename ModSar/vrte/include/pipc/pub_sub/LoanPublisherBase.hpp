/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PUB_SUB_LOAN_PUBLISHER_BASE_HPP
#define PIPC_PUB_SUB_LOAN_PUBLISHER_BASE_HPP

#include "LoanPublisherPtmpLayer.hpp"
#include "PublisherBase.hpp"
#include "pipc/Logger.hpp"
#include "pipc/loan/LoanMsg.hpp"
#include "pipc/transport/Message.hpp"
#include "pipc/utils/Expect.hpp"

namespace pipc
{
namespace pub_sub
{
namespace internal
{
/**
 * @brief LoanPublisherBase for type-independent parts of Publisher.
 *
 * @remark
 * The base class is carefully designed to minimize code duplication and
 * optimize branch prediction:
 * The ReceiveRestitution callback with the subscription logic is the same for
 * all publishers, meaning the same function will be registered at the
 * MsgDispatcher.
 */
template<size_t NSubscribers = PIPC_MAX_USERS_PER_PROVIDER, size_t MaxLoans = PIPC_MAX_CONCURRENT_PUBLISHER_MSGS>
class LoanPublisherBase : public internal::PublisherBase<NSubscribers, LoanPublisherPtmpLayer<MaxLoans>>
{
protected:
    using BaseClass    = internal::PublisherBase<NSubscribers, LoanPublisherPtmpLayer<MaxLoans>>;
    using RestituteMsg = loan::RestituteMsg;
    using Socket       = pimp::Socket;

protected:
    using BaseClass::BaseClass;

    /**
     * @brief Wrapper to receive a restitution message.
     */
    static void ReceiveRestitution(LoanPublisherBase& obj, Socket& socket, transport::Datagram<RestituteMsg>* msg)
    {
        obj.receiveRestitution(socket, *msg);
    }

    /**
     * @brief Function for receiving a restitution.
     */
    inline void receiveRestitution(Socket& socket, transport::Datagram<RestituteMsg>& msg)
    {
        auto idx        = msg.payload().getDebitorId();
        auto subscriber = this->endpoint_.get(idx);
        // Assert that the sender exists
        if (EXPECT_UNLIKELY(!subscriber))
        {
            PIPC_LOG_ERROR() << "LoanPublisherBase: Received restitution with invalid session id." << std::endl;
            return;
        }
        // Assert for the correct identity of the sender
        if (EXPECT_UNLIKELY(subscriber->getSocket() != &socket))
        {
            PIPC_LOG_ERROR() << "LoanPublisherBase: Received restitution with invalid identity." << std::endl;
            return;
        }
        // Assert the loan Id is correct
        // HINT:
        // Invalid restitutions could occur in rare cases:
        // - An app crashed and the disconnect is handled faster than remaining
        //   restitute msgs
        // - Some app goes rogue and sends garbage to the publisher
        if (EXPECT_UNLIKELY(this->getAppLayer().restitute(msg.payload()) != ReturnCode::kOk))
        {
            PIPC_LOG_ERROR() << "LoanPublisherBase: Received invalid loan id." << std::endl;
            return;
        }
    }
};

} // namespace internal

} // namespace pub_sub
} // namespace pipc

#endif // PIPC_PUB_SUB_LOAN_PUBLISHER_BASE_HPP
