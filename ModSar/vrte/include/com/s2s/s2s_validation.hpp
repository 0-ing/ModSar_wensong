#ifndef S2S_VALIDATION_HPP
#define S2S_VALIDATION_HPP

#include "s2s/s2s_types.hpp"

namespace com
{
namespace s2s
{
/**
 * @brief Function that returns an S2S configuration associated to an event
 * This function will also validate the configuration and will store the result
 * in S2SEventConfig.isConfigurationValid.
 * The following validation will be performed:
 *  - Check that serviceId, instanceId and eventId are found in serviceInstanceToSignalMapping
 *  - Check that the event has at least 1 signal mapped
 *  - Check that the signals mapped to the event are not duplicated
 *  - Check that the signals mapped to the event are in the same PDU
 *  - Check that the PDU length is greater than 0
 *  - Check that the signals mapped to the event are present in the iSignals list
 *  - Check that the signals have a length greater than 0
 *  - Check that the signals do not overlap in the PDU
 *  - Check that the signals do not pass the PDU size
 * @param serviceId Service identifier of the event
 * @param instanceId Instance identifier of the event
 * @param eventId Event identifier of the event
 * @param serviceInstanceToSignalMapping S2S Mapping
 * @param iSignals Signal List information
 * @param iSignalGroups SignalGroup List information
 * @param iSignalIPdus PDU to Signal Mapping
 * @return S2SEventConfig
 */
S2SEventConfig getAndValidateEventConfig(
    const uint32_t serviceId,
    const uint32_t instanceId,
    const uint32_t eventId,
    const std::map<std::tuple<uint32_t, uint32_t, uint32_t>, std::vector<std::string>>& serviceInstanceToSignalMapping,
    const std::map<std::string, ISignal>& iSignals,
    const std::map<std::string, ISignalGroup>& iSignalGroups,
    const std::vector<IPdu>& iSignalIPdus);

/**
 * @brief Function performs searches inside the list of PDU configurations, and returns a PDU configuration
 * pointer if a configuration was found that contains all the signals
 * @param signalList Signal list used to search inside the list of PDU configurations
 * @param iSignalIPdus List of PDU configurations
 * @return PDU configuration pointer if a PDU was found that contains all the signals, otherwise will return nullptr
 */
const IPdu* getPdu(const std::vector<std::string>& signalList, const std::vector<IPdu>& iSignalIPdus);

} // namespace s2s
} // namespace com

#endif
