/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_S2SEVENT_SUBSCRIBER_HPP
#define COM_BINDING_PIPC_S2SEVENT_SUBSCRIBER_HPP

#include "EventSubscriberBase.hpp"
#include "binding/SerializedSample.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "e2e/SamplePtrE2E.hpp"
#include "s2s/s2s_translation.hpp"
#include "s2s/s2s_utils.hpp"
#include "serializer/IS2SDeserializer.hpp"
#include "utils/Logger.hpp"
#include "utils/ObjectStorage.hpp"

namespace com
{
namespace binding_pipc
{
/**
 * @brief Class for serialized P-IPC s2s event subscription and reception.
 *
 * Makes use of the underlying transport (pipc) to receive and subscribe to s2s events.
 * Allows configuration of E2E protection.
 * Allows configuration of serialization.
 */
template<uint32_t N, typename SampleType>
class S2SEventSubscriber
    : public EventSubscriberBase<SampleType, pipc::pub_sub::LoanSubscriber<const binding::SerializedSample>>
{
public:
    using BaseClass  = EventSubscriberBase<SampleType, pipc::pub_sub::LoanSubscriber<const binding::SerializedSample>>;
    using E2ESMState = ara::com::e2e::SMState;
    using E2EResult  = ara::com::e2e::Result;
    using E2EProfileCheckStatus = ara::com::e2e::ProfileCheckStatus;
    using EventCfgSomeIp        = com::config::EventCfgSomeIp;
    using IDeserializer         = com::serializer::IS2SDeserializer<SampleType>;
    using Logger                = com::utils::Logger;
    using S2SConfig             = com::s2s::S2SEventConfig;
    using SamplePointer         = ara::com::SamplePtr<const SampleType>;
    using SamplePointerE2E      = com::e2e::SamplePtrE2E<const SampleType>;
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

    /** \brief Constructor for a "SOME/IP" deployment */
    S2SEventSubscriber(const config::DeploymentContextSomeIp& context,
                       const EventCfgSomeIp& eventCfg,
                       UniquePtr<IDeserializer>&& deserializer,
                       S2SConfig&& s2sConfig,
                       std::vector<com::s2s::S2SE2ECheckerConfig>&& checkers)
        : BaseClass(context, eventCfg, (eventCfg.maxSerializationSize + binding::SerializedSample::GetHeaderSize())),
          deserializer_(std::move(deserializer)),
          s2sConfig_(std::move(s2sConfig)),
          objectStorage_(),
          checkers_(std::move(checkers))
    {
        this->smState_ = E2ESMState::kNoData;
    }

    ara::core::Result<void> Subscribe(size_t maxSampleCount) override
    {
        if (maxSampleCount > N)
        {
            return ara::core::Result<void>::FromError(BaseClass::ComErrc::kMaxSampleCountNotRealizable);
        }

        if (!s2sConfig_.isConfigurationValid)
        {
            return ara::core::Result<void>::FromError(BaseClass::ComErrc::kCommunicationStackError);
        }

        return BaseClass::Subscribe(maxSampleCount);
    }

    size_t GetFreeSampleCount() const override
    {
        return (this->maxSampleCount_ - objectStorage_.getUsed());
    }

protected:
    using typename ara::com::IProxyEvent<SampleType>::GetSampleReturnCode;

    ara::core::Result<SamplePointer, GetSampleReturnCode> GetSample(bool isFirstCall) override
    {
        // First, check if we have local cache available then use subscriber_.tryReceive, so that
        // we do not discard a sample if there is no local space.
        if (objectStorage_.getUsed() >= this->maxSampleCount_)
        {
            // All sample slots are occupied
            return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(
                GetSampleReturnCode::kMaxSamplesReached);
        }

        pipc::loan::LoanedSamplePtr<const binding::SerializedSample> loanedPtr;
        if (!this->subscriber_.tryReceive(loanedPtr))
        {
            // No new samples available
            if (isFirstCall)
            {
                // The user expected a sample, but didn't get one.
                // This is a case for the E2E state machine.
                // For S2S, we may have multiple state machines.
                for (auto e2eChecker = checkers_.begin(); e2eChecker != checkers_.end(); e2eChecker++)
                {
                    auto checkResult = e2eChecker->checker->check(nullptr, 0, nullptr, 0);
                    // TODO: smState_ will never have a reasonable value, it's just the state of the last signal.
                    this->smState_ = checkResult.smStatus;
                }
            }
            return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(GetSampleReturnCode::kNoSample);
        }

        auto sample     = loanedPtr.get();
        uint32_t length = static_cast<uint32_t>(sample->size());
        auto data       = sample->data();

        if (length != s2sConfig_.pduLength)
        {
            Logger::GetInstance().LogWarn() << this->readableComponentId_ << " PDU length received (" << length
                                            << ") is not the same as configured (" << s2sConfig_.pduLength << ")!\n";
            return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(
                GetSampleReturnCode::kIpcTransportError);
        }

        com::s2s::printS2SBuffer(data, length, "Received S2S event data ");

        // E2E check for SignalGroup
        E2EResult checkResult{E2EProfileCheckStatus::kCheckDisabled, E2ESMState::kStateMDisabled};
        E2EProfileCheckStatus failProfileCheckStatus = E2EProfileCheckStatus::kOk;

        for (auto e2eChecker = checkers_.begin(); e2eChecker != checkers_.end(); e2eChecker++)
        {
            checkResult = e2eChecker->checker->check(data + e2eChecker->startPosition, e2eChecker->length, nullptr, 0);
            if (checkResult.checkStatus != E2EProfileCheckStatus::kOk)
            {
                Logger::GetInstance().LogWarn()
                    << this->readableComponentId_ << " Check function failed. Start position is "
                    << e2eChecker->startPosition << " CheckStatus: " << static_cast<uint16_t>(checkResult.checkStatus)
                    << "\n";
                // When multiple E2E errors occur, there is no AUTOSAR specification that which E2E error is
                // returned to application. So, we return first E2E error as implementation specification.
                if (failProfileCheckStatus == E2EProfileCheckStatus::kOk)
                {
                    failProfileCheckStatus = checkResult.checkStatus;
                }
            }
        }

        // TODO: smState_ will never have a reasonable value, it's just the state of the last signal.
        this->smState_ = checkResult.smStatus;

        // [TPS_MANI_03614] No translation of not OK E2E protected data out of several sources
        if (failProfileCheckStatus != E2EProfileCheckStatus::kOk)
        {
            // As intended in the AUTOSAR standard, we return a sample anyway, but with the ProfileCheckStatus set.
            SamplePointerE2E samplePtr;
            samplePtr.SetProfileCheckStatus(failProfileCheckStatus);
            return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromValue(std::move(samplePtr));
        }

        auto storagePtr = objectStorage_.getLoanedPtr();

        for (auto iSignalConfig = s2sConfig_.iSignalConfigs.begin(); iSignalConfig != s2sConfig_.iSignalConfigs.end();
             ++iSignalConfig)
        {
            std::vector<uint8_t> iSignalInBuffer;

            bool correct = getISignalDataFromPdu(data, iSignalInBuffer, *iSignalConfig);

            com::s2s::printS2SBuffer(iSignalInBuffer.data(),
                                     static_cast<uint32_t>(iSignalInBuffer.size()),
                                     "After unpacking ");

            if (correct)
            {
                correct = deserializer_->SetISignalData(iSignalInBuffer,
                                                        storagePtr.get(),
                                                        iSignalConfig->iSignalName,
                                                        iSignalConfig->length);
            }

            if (!correct)
            {
                Logger::GetInstance().LogWarn()
                    << this->readableComponentId_
                    << " Error retrieving signal data from PDU or error deserializing signal data for "
                    << iSignalConfig->iSignalName << "!\n";
                return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(
                    GetSampleReturnCode::kSerializerError);
            }
        }
        SamplePointerE2E samplePtr(
            std::move(*reinterpret_cast<pipc::loan::LoanedSamplePtr<const SampleType>*>(&storagePtr)));

        // When reaching this line, E2E check was either disabled or kOk.
        samplePtr.SetProfileCheckStatus(checkResult.checkStatus);
        return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromValue(std::move(samplePtr));
    }

private:
    /** @brief Sample deserializer. */
    std::unique_ptr<IDeserializer> deserializer_;
    /** @brief S2S configuration. */
    S2SConfig s2sConfig_;
    /** @brief Object storage used to store deserialized samples.*/
    com::utils::ObjectStorage<N, SampleType> objectStorage_;
    /** @brief E2E Checkers. */
    std::vector<com::s2s::S2SE2ECheckerConfig> checkers_;
};

} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_S2SEVENT_SUBSCRIBER_HPP
