/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.
#ifndef PIPC_PUB_SUB_LOAN_PUBLISHER_HPP
#define PIPC_PUB_SUB_LOAN_PUBLISHER_HPP

#include "LoanPublisherBase.hpp"
#include "pipc/loan/AdjustStride.hpp"
#include "pipc/loan/SamplePool.hpp"
#include "pipc/protocol/Layer.hpp"

namespace pipc
{
namespace pub_sub
{
/**
 * @brief Publisher for data of type T.
 *
 * @todo
 * Error handling for send functions.
 *
 * @todo
 * Best way to handle registration at MsgDispatcher vs. ProviderId registration?
 */
template<typename T, size_t NSubscribers = PIPC_MAX_USERS_PER_PROVIDER, size_t MaxLoans = PIPC_MAX_CONCURRENT_PUBLISHER_MSGS>
class LoanPublisher : public internal::LoanPublisherBase<NSubscribers, MaxLoans>
{
protected:
    using BaseClass  = internal::LoanPublisherBase<NSubscribers, MaxLoans>;
    using SamplePtr  = loan::SamplePtr<T>;
    using SamplePool = loan::SamplePool<T, MaxLoans>;

public:
    /** @brief Constructor without explicit stride. */
    LoanPublisher(session::ProviderId providerId, rte::IRuntime& runtime = rte::StandaloneRuntime::GetInstance())
        : LoanPublisher(providerId, runtime, loan::calcStride<T>())
    {
    }

    /** @brief Constructor with explicit stride. */
    LoanPublisher(session::ProviderId providerId, rte::IRuntime& runtime, size_t stride)
        : BaseClass(providerId, runtime), samplePool_(providerId.toString(), stride)
    {
        auto& dispatcher = runtime.getDispatcher();
        auto port        = dispatcher.registerCbk(&BaseClass::Receive, &BaseClass::ReceiveRestitution, *this);
        this->getTransportLayer().setSrcPort(port);
        if (port != transport::INVALID_PORT)
        {
            runtime.registerProvider(*this);
        }
        else
        {
            PIPC_LOG_ERROR() << "Couldn't register Publisher with ProviderId " << providerId.toString() << std::endl;
        }
    }

    /**
     * @brief Initialize the publisher.
     *
     * For standalone Publishers, we create the Sample Pool.
     * For other cases (e.g. Publishers with SD), we need a post-construction initialization step to
     * open the SamplePool after it has been created by the SD server.
     *
     * @todo
     * As always, error reporting...
     */
    void init(bool standalone) override
    {
        if (standalone)
        {
            samplePool_.create();
        }
        else
        {
            samplePool_.open();
        }
        BaseClass::init(standalone);
    }

    /**
     * @brief Send data to all subscribers.
     *
     * Variant with sample data owned by the user.
     */
    inline void send(const T& value)
    {
        auto samplePtr = allocate();
        *samplePtr     = value;
        return send(std::move(samplePtr));
    }

    /**
     * @brief Send data to all subscribers.
     *
     * Variant with sample data owned by the middleware.
     */
    inline void send(SamplePtr&& samplePtr)
    {
        if (EXPECT_UNLIKELY(this->getSessionLayer().getState() != protocol::LayerState::kValid))
        {
            PIPC_LOG_ERROR() << "Publisher: Cannot send while not offering." << std::endl;
            return;
        }

        this->getAppLayer().sendData(this->endpoint_, samplePtr);
    }

    /** @brief Allocate a sample for the user. */
    constexpr SamplePtr allocate()
    {
        return (samplePool_.allocate());
    }

    /** @brief Get the Segment Size. */
    uint32_t getSegmentSize() const override
    {
        return static_cast<uint32_t>(samplePool_.capacity());
    }

    /** @brief Check if sample pool still has free samples. */
    inline bool hasFreeSamples() const
    {
        return samplePool_.size() != 0UL;
    }

private:
    /** @brief The samples in shared memory. */
    SamplePool samplePool_;
};

} // namespace pub_sub
} // namespace pipc

#endif // PIPC_PUB_SUB_LOAN_PUBLISHER_HPP
