#ifndef S2S_TRANSLATION_HPP
#define S2S_TRANSLATION_HPP

#include "s2s/s2s_types.hpp"

namespace com
{
namespace s2s
{
/**
 * @brief Function that retrieves signal content from PDU. The content will be placed in ISignalData param based on the
 * endianness of the machine.
 * @param chunkPayload PDU content
 * @param ISignalData Buffer where the signal content will be placed
 * @param signalConfig Signal Information that should be used on the PDU content
 * @return TRUE if signal content retieved with success
 */
bool getISignalDataFromPdu(const uint8_t* chunkPayload,
                           std::vector<uint8_t>& ISignalData,
                           const ISignalConfig& signalConfig);

/**
 * @brief Function that inserts signal content into PDU. The content will be inserted into PDU based on the endianness
 * of the machine.
 * @param chunkPayload PDU content
 * @param iSignalData Signal data that will be inserted
 * @param signalConfig Signal Information used to insert to signal content
 * @return TRUE if signal content was inserted with success
 */
bool putISignalDataToPdu(uint8_t* chunkPayload, std::vector<uint8_t>& iSignalData, const ISignalConfig& signalConfig);

} // namespace s2s
} // namespace com

#endif
