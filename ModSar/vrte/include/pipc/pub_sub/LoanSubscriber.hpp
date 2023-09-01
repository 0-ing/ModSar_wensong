/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PUB_SUB_LOAN_SUBSCRIBER_HPP
#define PIPC_PUB_SUB_LOAN_SUBSCRIBER_HPP

#include "LoanSubscriberBase.hpp"
#include "pipc/loan/AdjustStride.hpp"
#include "pipc/loan/LoanedSamplePtr.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief LoanSubscriberBase for all subscribers with loan-restitute messaging.
 */
template<typename T>
class LoanSubscriber : public LoanSubscriberBase
{
    using BaseClass         = LoanSubscriberBase;
    using InternalSamplePtr = loan::LoanedSamplePtr<utils::Placeholder>;

public:
    using SamplePtr = loan::LoanedSamplePtr<T>;
    using BaseClass::BaseClass;

    /** @brief Constructor without explicit stride. */
    LoanSubscriber(session::ProviderId providerId, rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : BaseClass(providerId, runtime, loan::calcStride<T>())
    {
    }

    /** @brief Constructor with explicit stride. */
    LoanSubscriber(session::ProviderId providerId, rte::IRuntime& runtime, size_t stride)
        : BaseClass(providerId, runtime, loan::adjustStride<T>(stride, "LoanSubscriber"))
    {
    }

    /**
     * @brief Receive a sample from the mailbox.
     *
     * TODO: "switch to ReturnCode when the mailbox queues are also using ReturnCode
     */
    bool tryReceive(SamplePtr& ptr)
    {
        InternalSamplePtr* tmp = reinterpret_cast<InternalSamplePtr*>(&ptr);
        auto ret               = this->getAppLayer().getMailbox().msgs_.try_pop(*tmp);
        if (ret == ReturnVal::kOk)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Get the Mailbox Max Size
     *
     */
    constexpr size_t getMailboxMaxSize() const
    {
        return this->getAppLayer().getMailbox().Size();
    }
};

} // namespace pub_sub
} // namespace pipc

#endif // PIPC_PUB_SUB_LOAN_SUBSCRIBER_HPP
