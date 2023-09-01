/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_BINDING_SERIALIZEDSAMPLE_HPP
#define COM_BINDING_SERIALIZEDSAMPLE_HPP

#include "utils/Placeholder.hpp"

#include <cstddef>
#include <cstdint>
#include <limits.h>

namespace com
{
namespace binding
{
/**
 * @brief A serialized sample.
 *
 * This class acts as overlay for not further defined storage.
 * The storage must be at least as big as the size info (uint64_t),
 * keeping the size information in bound of the storage lies in
 * responsibility of the user.
 */
class SerializedSample
{
public:
    /** @brief Constructor with given size. */
    SerializedSample(size_t size = 0U) : size_(size)
    {
    }

    /**
     * @brief Return the size of the sample.
     *
     * @return size_t The total size.
     */
    size_t size() const
    {
        return size_;
    }

    /**
     * @brief Resize the sample to the given size.
     *
     * The user has to provide a maxSize parameter, which the resizing is checked against.
     * if newSize is too big, no changes are done.
     *
     * @param newSize The new size to be set.
     * @param maxSize The max size to compare against.
     * @return bool Whether resizing was successful.
     */
    bool resize(size_t newSize, size_t maxSize = std::numeric_limits<size_t>::max())
    {
        if (newSize <= maxSize)
        {
            size_ = newSize;
        }
        return (newSize <= maxSize);
    }

    /**
     * @brief Return a pointer to the data section of the sample.
     *
     * @return uint8_t* The data.
     */
    uint8_t* data()
    {
        size_t startAddress = reinterpret_cast<size_t>(this) + GetHeaderSize();
        return reinterpret_cast<uint8_t*>(startAddress);
    }

    /**
     * @brief Return a pointer to the data section of the sample.
     *
     * @return const uint8_t* The data.
     */
    const uint8_t* data() const
    {
        size_t startAddress = reinterpret_cast<size_t>(this) + GetHeaderSize();
        return reinterpret_cast<const uint8_t*>(startAddress);
    }

    /**
     * @brief Return the size of the header.
     *
     * @return size_t The size of the header.
     */
    static size_t GetHeaderSize()
    {
        return sizeof(uint64_t);
    }

private:
    /** @brief Size info. */
    uint64_t size_;
};

} // namespace binding
} // namespace com

#endif // COM_BINDING_SERIALIZEDSAMPLE_HPP
