#ifndef S2S_UTILS_HPP
#define S2S_UTILS_HPP

#include "s2s/logger/s2s_log.hpp"
#include "s2s/s2s_types.hpp"

#include <string>

namespace com
{
namespace s2s
{
/**
 * @brief Function that returns the byte order of the machine
 * @return TRUE if the byte order of the machine is BigEndian
 */
bool isBig();

/**
 * @brief Function that returns the position of a event config. It will return
 * a PduPosition based on the input
 * @param position Value used to create the PDU Position
 * @return PduPosition
 */
PduPosition getPosition(const uint32_t position);

/**
 * @brief Function to return a new position based on byte order
 * @param startPosition Current start position
 * @param length Value that will be added to the startPosition
 * @param order Byte order that will be used to create the new position
 * @return The new position
 */
PduPosition getNewPosition(const uint32_t startPosition, const uint32_t length, const ByteOrderEnum order);

/**
 * @brief Function that prints S2S information
 * @param buffer Content to be printed
 * @param size Size of the buffer
 * @param desc Short description that is placed before the buffer content
 */
void printS2SBuffer(const uint8_t* buffer, size_t size, const std::string& desc);

/**
 * @brief Overload operator to log a object of type ISignalConfig
 * @param stream Logging object
 * @param cfg ISignalConfig object
 * @return Logging object reference
 */
ara::log::LogStream& operator<<(ara::log::LogStream& stream, const ISignalConfig& cfg);

/**
 * @brief Overload operator to log a object of type PduPosition
 * @param stream Logging object
 * @param pos PduPosition object
 * @return Logging object reference
 */
ara::log::LogStream& operator<<(ara::log::LogStream& stream, const PduPosition& pos);

} // namespace s2s
} // namespace com

#endif
