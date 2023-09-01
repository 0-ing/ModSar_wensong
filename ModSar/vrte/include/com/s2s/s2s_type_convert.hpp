#ifndef S2S_TYPE_CONVERT_HPP
#define S2S_TYPE_CONVERT_HPP

#include "s2s/s2s_types.hpp"
#include "s2s/s2s_utils.hpp"

namespace com
{
namespace s2s
{
/**
 * @brief Function that converts a vector of uint8 to a primitive signed type. This function will
 * be generated for types which are signed and integrals. If the bit at iSignalLength is 1, then
 * the number will be interpreted as negative
 * @param iSignalData Vector to be converted
 * @param iSignalLength Lenght of the signal. If te value of this bit is 1, then the number will be
 * interpreted as negative
 * @return Primitive signed type
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, T>::type convert(
    const std::vector<uint8_t>& iSignalData,
    const uint32_t iSignalLength)
{
    T convertValue = 0;
    if (sizeof(T) > iSignalData.size())
    {
        std::vector<uint8_t> fullData(sizeof(T), 0);
        if (isBig())
        {
            std::copy(iSignalData.begin(), iSignalData.end(), fullData.begin() + sizeof(T) - iSignalData.size());
        }
        else
        {
            std::copy(iSignalData.begin(), iSignalData.end(), fullData.begin());
        }

        convertValue = *reinterpret_cast<const T*>(fullData.data());
    }
    else
    {
        convertValue = *reinterpret_cast<const T*>(iSignalData.data());
    }

    bool isNegative = (convertValue >> (iSignalLength - 1u)) & 0x01u;

    if (isNegative)
    {
        T mask = static_cast<T>((~0u) << (iSignalLength - 1u));
        convertValue |= mask;
    }

    return convertValue;
}

/**
 * @brief Function that converts a vector of uint8 to a primitive type. This function will
 * be generated for all other types which are not signed and integrals
 * @param iSignalData Vector to be converted
 * @param iSignalLength Unused
 * @return Primitive type
 */
template<typename T>
typename std::enable_if<!(std::is_integral<T>::value && std::is_signed<T>::value), T>::type convert(
    const std::vector<uint8_t>& iSignalData,
    const uint32_t iSignalLength)
{
    (void)iSignalLength;
    if (sizeof(T) > iSignalData.size())
    {
        std::vector<uint8_t> fullData(sizeof(T), 0);
        if (isBig())
        {
            std::copy(iSignalData.begin(), iSignalData.end(), fullData.begin() + sizeof(T) - iSignalData.size());
        }
        else
        {
            std::copy(iSignalData.begin(), iSignalData.end(), fullData.begin());
        }

        return *reinterpret_cast<const T*>(fullData.data());
    }
    else
    {
        return *reinterpret_cast<const T*>(iSignalData.data());
    }
}
} // namespace s2s
} // namespace com

#endif
