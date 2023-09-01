/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_EVENT_SUBSCRIBER_SERIALIZED_HPP
#define COM_BINDING_PIPC_EVENT_SUBSCRIBER_SERIALIZED_HPP

#include "binding/SerializedSample.hpp"
#include "binding/SomeipHeaderGen.hpp"
#include "binding_pipc/EventSubscriberBase.hpp"
#include "config/IServiceIntfCfg.hpp"
#include "e2e/IE2EChecker.hpp"
#include "e2e/SamplePtrE2E.hpp"
#include "pipc/pub_sub/LoanSubscriber.hpp"
#include "serializer/IDeserializer.hpp"
#include "utils/ObjectStorage.hpp"

#include <functional>
#include <memory>
#include <utility>

namespace com
{
namespace binding_pipc
{
/**
 * @brief Class for serialized P-IPC event subscription and reception.
 *
 * Makes use of the underlying transport (pipc) to receive and subscribe to events.
 * Allows configuration of E2E protection.
 * Allows configuration of serialization.
 */
template<size_t N, typename SampleType>
class EventSubscriberSerialized
    : public EventSubscriberBase<SampleType, pipc::pub_sub::LoanSubscriber<const binding::SerializedSample>>
{
public:
    using BaseClass   = EventSubscriberBase<SampleType, pipc::pub_sub::LoanSubscriber<const binding::SerializedSample>>;
    using EventCfgIpc = com::config::EventCfgIpc;
    using EventCfgSomeIp        = com::config::EventCfgSomeIp;
    using e2eResult             = ara::com::e2e::Result;
    using E2ESMState            = ara::com::e2e::SMState;
    using E2EProfileCheckStatus = ara::com::e2e::ProfileCheckStatus;
    using IDeserializer         = com::serializer::IDeserializer<SampleType>;
    using IE2EChecker           = com::e2e::IE2EChecker;
    using SamplePointer         = ara::com::SamplePtr<const SampleType>;
    using SamplePointerE2E      = com::e2e::SamplePtrE2E<const SampleType>;

    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;

    /** \brief Constructor for an IPC deployment */
    EventSubscriberSerialized(const config::DeploymentContextIpc& context,
                              const EventCfgIpc& eventCfg,
                              UniquePtr<IDeserializer>&& deserializer,
                              UniquePtr<IE2EChecker>&& checker)
        : BaseClass(context, eventCfg, eventCfg.maxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          bindingType_(ara::com::NetworkBindingEnum::IPC),
          cfgSomeIp_(),
          deserializer_(std::move(deserializer)),
          checker_(std::move(checker)),
          objectStorage_()
    {
        this->smState_ = E2ESMState::kNoData;
    }

    /** \brief Constructor for a "SOME/IP" deployment */
    EventSubscriberSerialized(const config::DeploymentContextSomeIp& context,
                              const EventCfgSomeIp& eventCfg,
                              UniquePtr<IDeserializer>&& deserializer,
                              UniquePtr<IE2EChecker>&& checker)
        : BaseClass(context, eventCfg, eventCfg.maxSerializationSize + binding::SerializedSample::GetHeaderSize()),
          bindingType_(ara::com::NetworkBindingEnum::SOME_IP),
          cfgSomeIp_(eventCfg),
          deserializer_(std::move(deserializer)),
          checker_(std::move(checker)),
          objectStorage_()
    {
        this->smState_ = E2ESMState::kNoData;
        checker_->setOffset(binding::SomeipHeaderGen::HEADER_SIZE);
    }

    ara::core::Result<void> Subscribe(size_t maxSampleCount) override
    {
        if (maxSampleCount > N)
        {
            utils::Logger::GetInstance().LogError()
                << this->readableComponentId_ << " maxSampleCout exceeds maximum. Limit is: " << N << "\n";
            return ara::core::Result<void>::FromError(BaseClass::ComErrc::kMaxSampleCountNotRealizable);
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
                e2eResult checkResult = checker_->check(nullptr, 0, nullptr, 0);
                this->smState_        = checkResult.smStatus;
            }
            return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(GetSampleReturnCode::kNoSample);
        }

        auto sample     = loanedPtr.get();
        uint64_t length = sample->size();
        auto data       = sample->data();

        size_t sampleSerializeStart = checker_->getE2EHeaderLength();
        e2eResult checkResult       = checker_->check(data, length, nullptr, 0);
        this->smState_              = checkResult.smStatus;

        if (bindingType_ == ara::com::NetworkBindingEnum::SOME_IP)
        {
            sampleSerializeStart += binding::SomeipHeaderGen::HEADER_SIZE;
            if (binding::SomeipHeaderGen::checkHeader(data, static_cast<uint32_t>(length), cfgSomeIp_) != true)
            {
                // Invalid SOME/IP header
                utils::Logger::GetInstance().LogError()
                    << this->readableComponentId_ << " Received SOME/IP header is broken.\n";
                return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(
                    GetSampleReturnCode::kSomeIpHeaderBroken);
            }
        }

        SamplePointerE2E samplePtr;

        if (CheckE2eValid(checkResult.checkStatus))
        {
            auto storagePtr                = objectStorage_.getLoanedPtr();
            uint32_t readBytes             = 0U;
            bool deserializationSuccessful = deserializer_->deserialize(&data[sampleSerializeStart],
                                                                        static_cast<uint32_t>(length
                                                                                              - sampleSerializeStart),
                                                                        storagePtr.get(),
                                                                        &readBytes);
            if (!deserializationSuccessful)
            {
                utils::Logger::GetInstance().LogError()
                    << this->readableComponentId_ << " Deserialization of sample failed.\n";
                return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromError(
                    GetSampleReturnCode::kSerializerError);
            }
            samplePtr = std::move(*reinterpret_cast<pipc::loan::LoanedSamplePtr<const SampleType>*>(&storagePtr));
        }

        samplePtr.SetProfileCheckStatus(checkResult.checkStatus);
        return ara::core::Result<SamplePointer, GetSampleReturnCode>::FromValue(std::move(samplePtr));
    }

private:
    /** \brief Check E2E status for valid result.
     *  Even though we return a sample to the user in any case, we do not try to deserialize a broken sample.
     */
    static inline bool CheckE2eValid(E2EProfileCheckStatus status)
    {
        bool valid = false;

        if ((status == E2EProfileCheckStatus::kOk) || (status == E2EProfileCheckStatus::kRepeated)
            || (status == E2EProfileCheckStatus::kWrongSequence) || (status == E2EProfileCheckStatus::kCheckDisabled))
        {
            valid = true;
        }

        return valid;
    }

    /** @brief Network binding type. */
    ara::com::NetworkBindingEnum bindingType_;
    /** @brief Someip event configuration. */
    EventCfgSomeIp cfgSomeIp_;
    /** @brief Sample deserializer. */
    UniquePtr<IDeserializer> deserializer_;
    /** @brief Sample e2e checker. */
    UniquePtr<e2e::IE2EChecker> checker_;
    /** @brief Object storage used to store deserialized samples.*/
    com::utils::ObjectStorage<N, SampleType> objectStorage_;
};

} // namespace binding_pipc
} // namespace com
#endif // COM_BINDING_PIPC_EVENT_SUBSCRIBER_SERIALIZED_HPP
