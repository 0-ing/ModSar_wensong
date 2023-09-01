//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      SerializableExternalString.hpp
/// @brief     Utility to read and write string arguments from and to a byte stream
/// @copyright Robert Bosch GmbH  2018
/// @author    baetz

#ifndef QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_SERIALIZABLEEXTERNALSTRING_HPP_
#define QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_SERIALIZABLEEXTERNALSTRING_HPP_

#include "ISerialize.hpp"
#include "SerializeAdapter.hpp"

#include "utils/c/string.hpp"     //wrapper to prevent direct inclusion of libc headers

namespace exm
{

namespace utils
{

/// @brief  Utility to read and write string arguments from and to a byte stream.
///  The string is encoded with a preceding length field (field width set
///  by template argument) and a trailing null field.
///  The string itself is not copied into the class.
///  Instead, it is copied directly from an external buffer into the stream (on write),
///  or the pointer is set to a position in the stream (on read).
///  Thus, the buffer or stream must still exist when the string is read.
template<typename count_t>
class SerializableExternalString: public ISerialize
{
public:

    static_assert((static_cast<count_t>(-1) > 0),"SerializableExternalString: count_t is signed");

    static count_t StringLength(const char* buffer, const count_t max_capacity)
    {
        if(nullptr == buffer)
        {
            return 0U;
        }

        return strnlen(buffer, max_capacity);    //PRQA S 3010 # max_capacity has the same type as the return value of this function.
    }                                            //              Therefore, this implicit conversion cannot lead to data loss.

    /// @brief  Default constructor.
    ///  Initializes to zero. Used for reading a string from a stream.
    SerializableExternalString():
        ISerialize(), length(0U), content(nullptr)
    {
    }

    /// @brief  Initializing constructor.
    /// buffer must persist as long as this element is used.
    /// @param buffer    Buffer to the string to be serialized
    /// @param length_   Length of the string, excluding trailing null.
    SerializableExternalString(const char* buffer, count_t length_) :
        ISerialize(), length(length_), content(buffer)
    {
    }

    //Defaut destructor
    ~SerializableExternalString(){}     //Not covered: Only the deleting destructor is not covered. We don't use the heap.

    //Default copy constructor
    SerializableExternalString (const SerializableExternalString &other):
        ISerialize(), length(other.length), content(other.content){}

    //Default copy assignment operator
    SerializableExternalString &operator=(const SerializableExternalString &other)
    {
        if(this != &other)
        {
            length=other.length;
            content=other.content;
        }

        return *this;
    }

    /// @brief  Serializes the string to buffer.
    /// First, the length field is serialized, then the string is copied.
    /// The actual content is copied using memcpy.
    /// buffer must be large enough to hold length field + buffer + null.
    /// @param[in] buffer     Buffer to serialize to.
    /// @param[inout] offset     Offset within the buffer to serialize to.
    /// @param[in] maxSize    Maximum available size for serialization.
    /// @return StdReturnType
    /// @retval  OK on success
    /// @retval  GENERAL_ERROR on error, eg. buffer too short or nullptr input.
    StdReturnType Serialize(uint8_t buffer[], uint32_t* offset, uint32_t maxSize) const
    {
        if((nullptr == buffer) || (nullptr == offset))
        {
            return StdReturnType::GENERAL_ERROR;
        }

        if (nullptr == content)
        {
            // Can't serialize nullptr.
            return StdReturnType::GENERAL_ERROR;
        }

        StdReturnType result = SerializeAdapter::Serialize(length, buffer, offset, maxSize);
        if (result != StdReturnType::OK)
        {
            // Serialization failure.
            return result;
        }

        if ((*offset + length + 1U) > maxSize)
        {
            // Can't fit the string data.
            return StdReturnType::GENERAL_ERROR;
        }

        // Finally copy content to stream
        (void)memcpy(&buffer[*offset], content, length);
        *offset += length;
        // Add trailing null.
        buffer[*offset] = '\0';
        *offset += 1U;

        return StdReturnType::OK;
    }

    /// @brief  Read a string from a stream.
    /// The string must be encoded using this class, as it expects a preceding
    /// length fields.
    /// @param[in] buffer    The stream buffer to read from.
    /// @param[inout] offset Offset within the stream to read.
    /// @param[in] maxSize   Maximum size of readable content.
    /// @return StdReturnType
    /// @retval  OK on success
    /// @retval  GENERAL_ERROR on error, eg. buffer too short or nullptr input.
    StdReturnType DeSerialize(const uint8_t buffer[], uint32_t* offset, uint32_t maxSize)
    {

        if((nullptr == buffer) || (nullptr == offset))
        {
            return StdReturnType::GENERAL_ERROR;
        }

        StdReturnType result = SerializeAdapter::DeSerialize(&length, buffer, offset, maxSize);
        if (result != StdReturnType::OK)
        {
            // DeSerialize issue.
            return result;
        }

        if ((*offset + length + 1U) > maxSize)
        {
            // Not enough data in buffer
            return StdReturnType::GENERAL_ERROR;
        }

        content = reinterpret_cast<const char*>(&buffer[*offset]);

        if (buffer[*offset + length] != '\0')
        {
            // The string is not properly null terminated.
            return StdReturnType::GENERAL_ERROR;
        }

        *offset += (length + 1U);

        return StdReturnType::OK;
    }

    /// @brief  Serialized size is the size of the length field, content of the length field and the trailing null.
    /// @return
    uint32_t GetSerializedSize() const
    {
        return SerializeAdapter::GetSerializedSize(length) + length + 1U;
    }

    /// @brief  Getter for string length.
    /// @return Length of the string without trailing null.
    count_t getLength() const
    {
        return length;
    }

    /// @brief  Getter for the String itself.
    /// @return  Pointer to the stored string.
    const char* getString() const
    {
        return content;
    }

private:
    count_t length;         ///< Field identifying the length of the string.
    const char* content;    ///< Pointer to string content.
};

}  // namespace utils

}  // namespace exm

#endif // QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_SERIALIZABLEEXTERNALSTRING_HPP_
