//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      IProxyEvent.hpp
/// @brief     Interface class for proxy events
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_IPROXY_EVENT_HPP
#define ARA_COM_IPROXY_EVENT_HPP

#include "ara/com/com_error_domain.h"
#include "ara/com/e2e/e2e_error_domain.h"
#include "ara/com/types.h"
#include "ara/core/result.h"

/**
 * \brief Forward declaration to make FieldSubscriber a friend class of IProxyEvent.
 *
 * \remark FieldSubscriber needs access to GetSample() of this interface,
 * because it needs to redirect the method call to the notifier implementation.
 */
namespace com
{
namespace binding
{
template<typename FieldType_T>
class FieldSubscriber;

} // namespace binding
} // namespace com

namespace ara
{
namespace com
{
/** \brief Forward declaration to make ProxyEvent a friend class of IProxyEvent. */
template<typename SampleType_T>
class ProxyEvent;

/**
 * \brief Template interface for all proxy-side events used in ara::com
 *
 * This class is used as an interface for proxy events used in ara::com.
 * It provides all public interfaces as defined by AR.
 *
 * \remark Although an interface should not contain any implementations, the implementation of
 * \see GetNewSamples() has to be be included in the interface, as a templated method is required per AR spec.
 * This implementation is written in a generic manner, sub-classes must only provide an implementation for
 * the referenced method \see GetSample().
 */
// TODO: Check whether we require the additional method 'const ara::com::e2e::Result GetResult() const;', see SWS_CM_90424
template<typename SampleType_T>
class IProxyEvent
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using SampleType        = SampleType_T;
    using SamplePointer     = SamplePtr<const SampleType>;
    using ComErrc           = ara::com::ComErrc;
    using SubscriptionState = ara::com::SubscriptionState;
    using SMState           = ara::com::e2e::SMState;

    /** \brief ProxyEvent needs to access protected methods */
    friend class ProxyEvent<SampleType>;

    /** \brief FieldSubscriber needs to access protected methods */
    friend class ::com::binding::FieldSubscriber<SampleType>;

    IProxyEvent() = default;

    /** \brief No copy operations allowed */
    IProxyEvent(const IProxyEvent&) = delete;
    IProxyEvent& operator=(const IProxyEvent&) = delete;

    /** \brief No move operations allowed */
    IProxyEvent(const IProxyEvent&&) = delete;
    IProxyEvent& operator=(const IProxyEvent&&) = delete;

    virtual ~IProxyEvent() = default;

    /**
     * \brief Query current subscription state.
     * \return Current state of the subscription.
     *
     * \remark
     * @ID{[SWS_CM_00316]}
     */
    virtual SubscriptionState GetSubscriptionState() const = 0;

    /**
     * \brief Start the subscription to the event.
     *
     * The Communication Management will try to subscribe and
     * re-subscribe until \see Unsubscribe() is called explicitly. The function
     * returns immediately, error handling is dealt internally.
     * An optional notification mechanism can be set up via
     * \see SetSubscriptionStateChangeHandler().
     *
     * \param[in] maxSampleCount The maximum no. of samples that can be allocated
     *   at a point in time
     *
     * \remark
     * @ID{[SWS_CM_00141]}
     * @ID{[SWS_CM_00700]}
     */
    virtual ara::core::Result<void> Subscribe(size_t maxSampleCount) = 0;

    /**
     * \brief Unsubscribe from the event.
     *
     * \remark
     * @ID{[SWS_CM_00151]}
     * */
    virtual void Unsubscribe() = 0;

    /**
     * \brief Registration of a subscription state handler.
     *
     * The handler gets called as soon as the subscription
     * state of this event has changed. If multiple changes of
     * the subscription state take place during the runtime of a previous call
     * to a handler, it will get called with the last/effectice state the next time.
     * Handler may be overwritten during runtime.
     *
     * \remark
     * @ID{[SWS_CM_00333]}
     */
    virtual ara::core::Result<void> SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler)
        = 0;

    /**
     * \brief Remove handler set by \see SetSubscriptionStateChangeHandler().
     *
     * \remark
     * @ID{[SWS_CM_00334]}
     */
    virtual void UnsetSubscriptionStateChangeHandler() = 0;

    /**
     * \brief Register a receive handler for the event.
     *
     * The registered handler gets called asynchronously by the Communication
     * Management as soon as new event data arrives for that event.
     * If the user wants to have strict polling behaviour, where you decide when to
     * check for new data via Update() he should NOT register a handler.
     * Handler may be overwritten anytime during runtime.
     *
     * \remark The provided Handler needs not to be re-entrant since the Communication
     * Management implementation has to serialize calls to the handler: Handler
     * gets called once by the MW, when new events arrived since the last call
     * to Update(). When application calls Update() again in the context of the
     * receive handler, MW must - in case new events arrived in the meantime -
     * defer next call to receive handler until after the previous call to
     * receive handler has been completed.
     *
     * \remark
     * @ID{[SWS_CM_00181]}
     */
    virtual ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler) = 0;

    /**
     * \brief Remove handler set by \see SetReceiveHandler().
     *
     * \remark
     * @ID{[SWS_CM_00183]}
     */
    virtual ara::core::Result<void> UnsetReceiveHandler() = 0;

    /**
     * \brief Get new data from the Communication Management
     * buffers and provide it in callbacks to the given callable f.
     *
     * \param f
     * \parblock
     * Callback, which shall be called with new sample.
     *
     * This callable has to fulfill the signature
     * void(ara::com::SamplePtr<SampleType const>)
     * \endparblock
     *
     * \param maxNumberOfSamples
     * \parblock
     * Upper bound of samples to be fetched from middleware buffers.
     * Default value means "no restriction", i.e. all newly arrived samples
     * are fetched as long as there are free sample slots.
     * \endparblock
     *
     * \return Result, which contains the number of samples,
     * which have been fetched and presented to user via calls to f or an
     * ErrorCode in case of error (e.g. max samples exceeded)
     *
     * \remark
     * @ID{[SWS_CM_00701]}
     * @ID{[SWS_CM_00703]}
     * @ID{[SWS_CM_00704]}
     * @ID{[SWS_CM_00714]}
     */
    template<typename F>
    ara::core::Result<size_t> GetNewSamples(F&& f, size_t maxNumberOfSamples = std::numeric_limits<size_t>::max())
    {
        if (this->GetSubscriptionState() != ara::com::SubscriptionState::kSubscribed)
        {
            // The event is not subscribed. Situation currently not exactly specified in AUTOSAR.
            return ara::core::Result<size_t>::FromError(MakeErrorCode(ComErrc::kServiceNotAvailable));
        }

        size_t samplesRead = 0u;
        while (samplesRead < maxNumberOfSamples)
        {
            ara::core::Result<SamplePointer, GetSampleReturnCode> sample = GetSample((0 == samplesRead));
            // Check if we have received a SamplePtr
            if (sample.HasValue())
            {
                f(std::move(sample).Value());
                samplesRead++;
            }
            // No sample received.
            else
            {
                switch (sample.Error())
                {
                case GetSampleReturnCode::kNoSample:
                    // No new sample available. No need to continue.
                    // If it was first sample, E2E state machine was updated.
                    return ara::core::Result<size_t>::FromValue(samplesRead);
                case GetSampleReturnCode::kMaxSamplesReached:
                    // Distinguish between reading out some samples before reaching MaxSamples,
                    // or having read no sample at all, following SWS_CM_00703 for normal behavior.
                    // The spec is not 100% clear, SWS_CM_00704 could be interpreted such
                    // that an error is returned immediately.
                    if (samplesRead > 0)
                    {
                        // We have read some samples but we reached the Subscribe max samples. Return the amount read so far.
                        return ara::core::Result<size_t>::FromValue(samplesRead);
                    }
                    else
                    {
                        // No samples were read so we can return error
                        return ara::core::Result<size_t>::FromError(MakeErrorCode(ComErrc::kMaxSamplesReached));
                    }
                // All of these cases are severe functional or configuration errors.
                // Thus, it is better to break.
                case GetSampleReturnCode::kIpcTransportError:
                case GetSampleReturnCode::kSomeIpHeaderBroken:
                    return ara::core::Result<size_t>::FromError(MakeErrorCode(ComErrc::kCommunicationStackError));
                case GetSampleReturnCode::kSerializerError:
                default:
                    return ara::core::Result<size_t>::FromError(MakeErrorCode(ComErrc::kNetworkBindingFailure));
                }
            }
        }
        return ara::core::Result<size_t>::FromValue(samplesRead);
    }

    /**
     * \brief Get the number of currently free/available sample slots.
     *
     * \return number from 0 - N (N = count given in call to \see Subscribe())
     * or an ErrorCode in case of number of currently held samples
     * already exceeds the max number given in Subscribe().
     *
     * \remark
     * @ID{[SWS_CM_00705]}
     * @ID{[SWS_CM_00706]}
     * @ID{[SWS_CM_00707]}
     */
    virtual size_t GetFreeSampleCount() const = 0;

    /**
     * \brief Get the current state of the E2E State Machine
     *
     * \return State of the E2E State Machine
     *
     * \remark
     * @ID{[SWS_CM_10475]}
     * @ID{[SWS_CM_90431]}
     */
    virtual SMState GetSMState() const = 0;

protected:
    /**
     * @brief This class holds all possible return codes of the internal GetSample() call.
     *
     * An alternative option is to use ComErrc directly.
     * However, this makes it difficult to differentiate "no sample" situations.
     */
    enum class GetSampleReturnCode : uint8_t
    {
        kNoSample,          ///< No sample available, even though you asked for.
        kMaxSamplesReached, ///< More samples are held than what was requested
        kIpcTransportError, ///< Error of the underlying IPC transport mechanism. Quite unlikely.
        kSerializerError,   ///< (De-)Serialization error. Sever configuration error.
        kSomeIpHeaderBroken ///< Missmatch in received SOME/IP header. Very unlikely.
    };

    /**
     * \brief Fetch one sample
     *
     * \param isFirstCall First call to the function in one GetNewSamples call.
     * \return Either a SamplePointer or GetSampleReturnCode.
     */
    virtual ara::core::Result<SamplePointer, GetSampleReturnCode> GetSample(bool isFirstCall) = 0;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_IPROXY_EVENT_HPP
