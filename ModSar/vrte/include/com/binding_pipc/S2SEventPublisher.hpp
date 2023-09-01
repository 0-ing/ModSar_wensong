/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_PIPC_S2SEVENT_PUBLISHER_HPP
#define COM_BINDING_PIPC_S2SEVENT_PUBLISHER_HPP

#include "binding_pipc/EventPublisherSerializedBase.hpp"
#include "s2s/s2s_translation.hpp"
#include "s2s/s2s_types.hpp"
#include "s2s/s2s_utils.hpp"
#include "serializer/IS2SSerializer.hpp"

namespace com
{
namespace binding_pipc
{
/** @brief Class for publishing and sending S2S events on Pipc.
 *  Allows configuration of E2E protection
 *  Allows configuration of s2s Serialization
 *  Allows configuration of s2s Config
 */
template<size_t N, typename SampleType>
class S2SEventPublisher : public EventPublisherSerializedBase<N, SampleType>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using ComErrc               = ara::com::ComErrc;
    using EventCfgSomeIp        = com::config::EventCfgSomeIp;
    using S2SEventConfig        = com::s2s::S2SEventConfig;
    using S2SE2EProtectorConfig = s2s::S2SE2EProtectorConfig;
    using S2SSerializer         = com::serializer::IS2SSerializer<SampleType>;
    using Logger                = com::utils::Logger;
    template<typename T>
    using UniquePtr = ara::com::UniquePtr<T>;
    using BaseClass = EventPublisherSerializedBase<N, SampleType>;

    /** \brief Constructor for a "SOME/IP" deployment */
    S2SEventPublisher(const config::DeploymentContextSomeIp& context,
                      const EventCfgSomeIp& eventCfg,
                      const S2SEventConfig& s2sCfg,
                      UniquePtr<S2SSerializer>&& s2sSerializer,
                      std::vector<com::s2s::S2SE2EProtectorConfig>&& e2eProtectors)
        : BaseClass(context, eventCfg),
          s2sCfg_(s2sCfg),
          s2sSerializer_(std::move(s2sSerializer)),
          e2eProtectorsCfg_(std::move(e2eProtectors))
    {
    }

    ~S2SEventPublisher() = default;

    S2SEventPublisher& operator=(const S2SEventPublisher& other) = delete;
    S2SEventPublisher(const S2SEventPublisher& other)            = delete;

    S2SEventPublisher(S2SEventPublisher&& other) = delete;
    S2SEventPublisher& operator=(S2SEventPublisher&&) = delete;

    /**
     * @brief Sends Event's data.
     * Calculate the sample's size with the needed headers and allocate storage for the sample.
     * Serialize the signals and put pack them in the PDU and call protect() of the configured protectors on the
     * configured parts to be protected
     * Send the sample if no error occurred in any of the previous steps
     *
     * @param data the data to be sent by the publisher
     * @return relevant ComErrc or returns void Result to represent successful Send
     */
    ara::core::Result<void> Send(const SampleType& data) override
    {
        if (!s2sCfg_.isConfigurationValid)
        {
            Logger::GetInstance().LogWarn()
                << this->readableComponentId_ << " S2S configuration is invalid, do not send the message\n";
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }

        // size of the sample (+8 [header length])
        if ((s2sCfg_.pduLength + binding::SerializedSample::GetHeaderSize()) > this->maxSampleSize_)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_ << " Serialized sample of size "
                << s2sCfg_.pduLength + binding::SerializedSample::GetHeaderSize()
                << " is bigger than configured maxSampleSize of " << this->maxSampleSize_ << "\n";
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }

        auto sample = this->publisher_.allocate();
        // check if allocate() successfully reserved memory
        if (!sample)
        {
            Logger::GetInstance().LogError()
                << this->readableComponentId_ << " Shared Memory full, cannot send message\n";
            return ara::core::Result<void>::FromError(ComErrc::kSampleAllocationFailure);
        }

        binding::SerializedSample* samplePtr = sample.get();
        samplePtr->resize(s2sCfg_.pduLength, this->maxSampleSize_ - binding::SerializedSample::GetHeaderSize());

        // initialize pdu with bit pattern before adding signals
        memset(samplePtr->data(), s2sCfg_.unusedBitPattern, samplePtr->size());

        for (auto iSignalConfig = s2sCfg_.iSignalConfigs.begin(); iSignalConfig != s2sCfg_.iSignalConfigs.end();
             ++iSignalConfig)
        {
            std::vector<uint8_t> iSignalOutBuffer;
            bool success = s2sSerializer_->GetISignalData(iSignalOutBuffer,
                                                          &data,
                                                          iSignalConfig->iSignalName,
                                                          iSignalConfig->length);

            if (!success)
            {
                Logger::GetInstance().LogWarn() << this->readableComponentId_ << " Error while getting signal data for "
                                                << iSignalConfig->iSignalName << ", do not send message\n";
                return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
            }

            com::s2s::printS2SBuffer(iSignalOutBuffer.data(), iSignalOutBuffer.size(), "Before packing ");

            success = com::s2s::putISignalDataToPdu(samplePtr->data(), iSignalOutBuffer, *iSignalConfig);

            if (!success)
            {
                Logger::GetInstance().LogWarn() << this->readableComponentId_ << " Error while assembling PDU for "
                                                << iSignalConfig->iSignalName << ", do not send message\n";
                return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
            }
        }

        // E2E protector for SignalGroup
        // The PDU will be sent only if protect function worked ok or if there is no profile configuration
        for (auto protectorCfg = e2eProtectorsCfg_.begin(); protectorCfg != e2eProtectorsCfg_.end(); protectorCfg++)
        {
            e2e::ProtectStatus protectStatus = (protectorCfg->protector->protect)(samplePtr->data()
                                                                                      + protectorCfg->startPosition,
                                                                                  protectorCfg->length,
                                                                                  nullptr,
                                                                                  0);
            if (protectStatus != e2e::ProtectStatus::kOk && protectStatus != e2e::ProtectStatus::kProtectDisabled)
            {
                Logger::GetInstance().LogError()
                    << this->readableComponentId_ << " Protector function failed. position is "
                    << protectorCfg->startPosition << " byte\n";
                return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
            }
        }

        com::s2s::printS2SBuffer(samplePtr->data(), samplePtr->size(), "Sending S2S event data ");
        //  send to shared memory
        this->publisher_.send(std::move(sample));
        return ara::core::Result<void>{};
    }

    /**
     * @brief sends Event's data.
     * checks the passed SamplePtr, if not null then call the Send() on the sample's data.
     *
     * @param data the SamplePtr of the data to be sent by the publisher
     * @return void Result (no error) if 'data' is a nullptr, otherwise call Send() and return its result
     */
    ara::core::Result<void> Send(ara::com::SampleAllocateePtr<SampleType> data) override
    {
        // Check if the pointer really contains a sample
        if (data)
        {
            return Send(*(data.get()));
        }
        // There is no ErrorCode defined for empty samples, so return OK
        return ara::core::Result<void>{};
    }

    /** @brief Offering the sevice if the s2s Configuration is valid.*/
    ara::core::Result<void> Offer()
    {
        if (!s2sCfg_.isConfigurationValid)
        {
            Logger::GetInstance().LogWarn()
                << this->readableComponentId_ << " The Event's S2S configuration is invalid, do not offer\n";
            return ara::core::Result<void>::FromError(ComErrc::kCommunicationStackError);
        }
        return BaseClass::Offer();
    }

private:
    /** @brief S2S event configuration. */
    S2SEventConfig s2sCfg_;
    /** @brief Sample serializer. */
    UniquePtr<S2SSerializer> s2sSerializer_;
    /** @brief array of the signals' e2e e2eProtectors. */
    std::vector<com::s2s::S2SE2EProtectorConfig> e2eProtectorsCfg_;
};
} // namespace binding_pipc
} // namespace com

#endif // COM_BINDING_PIPC_S2SEVENT_PUBLISHER_HPP
