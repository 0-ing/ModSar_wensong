//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      SerializeAdapter.hpp
/// @brief     Adapter class with static methods only, which supports serialization
/// @copyright Robert Bosch GmbH  2018
/// @author    baetz

#ifndef QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_SERIALIZEADAPTER_HPP_
#define QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_SERIALIZEADAPTER_HPP_

#include "utils/c/stddef.hpp"     //wrapper to prevent direct inclusion of libc headers

#include "utils/type_traits.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/ISerialize.hpp"

namespace exm
{

namespace utils
{

/// @brief     Adapter class with static methods only, which supports serialization.
///
/// Is capable of doing specialized serialization and deserialization of
/// integer types, enum types and types which implement the ISerialize interface.
/// There is NO default implementation e.g. using memcpy.
/// Moreover, serialization of float and double is currently not supported.
/// Increments the offset parameter, so calls can be chained without effort.
class SerializeAdapter
{
private:

    /// @brief    Default template, which is used if no specialized template triggers.
    ///
    /// Does not provide an implementation. Thus, using the class with
    /// unsupported types produces a compile time error with:
    /// "No matching function for call to ..."
    template<class T, typename Enable = void>
    class SerializeAdapter_
    {
    public:
        //No default implementation
    };

    /// @brief    Partial specialization of SerializeAdapter_ for integral types.
    ///
    /// Serializes by putting values byte-by-byte into the buffer (and vice versa).
    template<class T>
    class SerializeAdapter_<T,
            typename utils::EnableIf<utils::IsIntegralNumber<T>::value>::type>
    {
    public:
        /// @brief    Static method to support serialization of types.
        ///
        /// Uses internal SerializeAdapter_ class and partial specialization to determine the
        /// correct operation for serialization.
        /// @param[in] value         The value to serialize.
        /// @param[inout] buffer     Pointer to a buffer to be filled with object content.
        /// @param[inout] offset     Offset within the buffer. Is incremented by the serial representation size of T.
        /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
        /// @return  StdReturnType
        /// @retval  OK              Object was serialized
        /// @retval  GENERAL_ERROR   Not enough space for object or nullptr input.
        StdReturnType Serialize(const T& value, uint8_t buffer[],
                uint32_t* offset, uint32_t maxSize)
        {
            // check for nullptr
            if((nullptr == buffer) ||( nullptr == offset))
            {
                return StdReturnType::GENERAL_ERROR;
            }

            //Always go for Big Endian on the wire.
            if ((*offset + sizeof(T) )> maxSize)
            {
                return StdReturnType::GENERAL_ERROR;
            }
            for (size_t count = 0U; count < sizeof(T); count++)
            {
                const uint32_t shift = static_cast<uint32_t>((sizeof(T) - 1U
                        - count) * 8U);
                const uint8_t byte = static_cast<uint8_t>(value >> shift)          // PRQA S 3003 # Signed integers are two's complement - "There is One True Representation for signed integers, and that representation is two's complement."
                        & 0xFFU; 

                buffer[*offset + count] = byte;
            }
            *offset += sizeof(T);
            return StdReturnType::OK;
        }

        /// @brief    Static method to support deserialization of types from stream.
        ///
        /// Uses internal SerializeAdapter_ class and partial specialization to determine the
        /// correct operation for deserialization.
        /// @param[out] value        The value to read from the buffer.
        /// @param[in] buffer        Pointer to a buffer from which the content is read.
        /// @param[inout] offset     Offset within buffer to read from. Is incremented by the serial representation size of T.
        /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
        /// @return  StdReturnType
        /// @retval  OK              Object was serialized
        /// @retval  GENERAL_ERROR   Not enough data to read value from stream or nullptr input.
        StdReturnType DeSerialize(T* value, const uint8_t buffer[],
                uint32_t* offset, uint32_t maxSize)
        {
            // check for nullptr
            if((nullptr == value) || (nullptr == buffer) ||( nullptr == offset))
            {
                return StdReturnType::GENERAL_ERROR;
            }


            //Always read Big Endian on the wire.
            if ((*offset + sizeof(T)) > maxSize)
            {
                return StdReturnType::GENERAL_ERROR;
            }
            *value = static_cast<T>(0);
            for (size_t count = 0U; count < sizeof(T); count++)
            {
                const uint32_t shift = static_cast<uint32_t>((sizeof(T) - 1U
                        - count) * 8U);
                const T val = static_cast<T>(buffer[*offset + count]);

                *value += static_cast<T>(val << shift); // PRQA S 3003 # Signed integers are two's complement - "There is One True Representation for signed integers, and that representation is two’s complement."
            }
            *offset += sizeof(T);
            return StdReturnType::OK;
        }

        /// @brief    Get the serialization size of the value.
        /// @param    value         Value to retrieve the size for.
        /// @return   Size of the serial representation of T.
        uint32_t GetSerializedSize(const T& value)
        {
            return sizeof(value);
        }
    };

    /// @brief    Partial specialization of SerializeAdapter_ for enum types.
    ///
    /// Admittedly, the code looks quite horrible, but in principle it resorts
    /// to using the integer specialization (from which it inherits).
    /// In order to use it, a type conversion of the input enum value to the
    ///  underlying integer type is necessary.
    template<class T>
    class SerializeAdapter_<T,
            typename utils::EnableIf<utils::IsEnum<T>::value>::type> : public SerializeAdapter_<
            typename utils::UnderlyingType<T>::type>
    {
    public:
        /// @brief    Static method to support serialization of types.
        ///
        /// Uses internal SerializeAdapter_ class and partial specialization to determine the
        /// correct operation for serialization.
        /// @param[in] value         The value to serialize.
        /// @param[inout] buffer     Pointer to a buffer to be filled with object content.
        /// @param[inout] offset     Offset within the buffer. Is incremented by the serial representation size of T.
        /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
        /// @return  StdReturnType
        /// @retval  OK              Object was serialized
        /// @retval  GENERAL_ERROR   Not enough space for object or nullptr input.
        StdReturnType Serialize(const T& value, uint8_t* const buffer,
                uint32_t* offset, uint32_t maxSize)
        {
            return SerializeAdapter_<typename utils::UnderlyingType<T>::type>::Serialize(
                    static_cast<typename utils::UnderlyingType<T>::type>(value),
                    buffer, offset, maxSize);
        }

        /// @brief    Static method to support deserialization of types from stream.
        ///
        /// Uses internal SerializeAdapter_ class and partial specialization to determine the
        /// correct operation for deserialization.
        /// @param[out] value        The value to read from the buffer.
        /// @param[in] buffer        Pointer to a buffer from which the content is read.
        /// @param[inout] offset     Offset within buffer to read from. Is incremented by the serial representation size of T.
        /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
        /// @return  StdReturnType
        /// @retval  OK              Object was serialized
        /// @retval  GENERAL_ERROR   Not enough data to read value from stream or nullptr input.
        StdReturnType DeSerialize(T* value, const uint8_t* const buffer,
                uint32_t* offset, uint32_t maxSize)
        {
            return SerializeAdapter_<typename utils::UnderlyingType<T>::type>::DeSerialize(
                    reinterpret_cast<typename utils::UnderlyingType<T>::type*>(value),
                    buffer, offset, maxSize);
        }

        /// @brief    Get the serialization size of the value.
        /// @param    value         Value to retrieve the size for.
        /// @return   Size of the serial representation of T.
        uint32_t GetSerializedSize(const T& value)
        {
            //enum type and UnderlyingType should be the same size.
            return sizeof(value);
        }
    };
    /// @brief    Partial specialization of SerializeAdapter_ for types inheriting from ISerialize.
    ///
    /// Invokes T's methods of ISerialize to read from and write to buffer.
    template<class T>
    class SerializeAdapter_<T,
            typename utils::EnableIf<utils::IsDerivedFrom<T, ISerialize>::Is>::type>
    {
    public:

        /// @brief    Static method to support serialization of types.
        ///
        /// Uses internal SerializeAdapter_ class and partial specialization to determine the
        /// correct operation for serialization.
        /// @param[in] value         The value to serialize.
        /// @param[inout] buffer     Pointer to a buffer to be filled with object content.
        /// @param[inout] offset     Offset within the buffer. Is incremented by the serial representation size of T.
        /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
        /// @return  StdReturnType
        /// @retval  OK              Object was serialized
        /// @retval  GENERAL_ERROR   Not enough space for object or nullptr input.
        StdReturnType Serialize(const T& value, uint8_t* const buffer,
                uint32_t* offset, uint32_t maxSize)
        {
            // check for nullptr
            if(nullptr == buffer || nullptr == offset)
            {
                return StdReturnType::GENERAL_ERROR;
            }

            return value.Serialize(buffer, offset, maxSize);
        }

        /// @brief    Static method to support deserialization of types from stream.
        ///
        /// Uses internal SerializeAdapter_ class and partial specialization to determine the
        /// correct operation for deserialization.
        /// @param[out] value        The value to read from the buffer.
        /// @param[in] buffer        Pointer to a buffer from which the content is read.
        /// @param[inout] offset     Offset within buffer to read from. Is incremented by the serial representation size of T.
        /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
        /// @return  StdReturnType
        /// @retval  OK              Object was serialized
        /// @retval  GENERAL_ERROR   Not enough data to read value from stream or nullptr input.
        StdReturnType DeSerialize(T* value, const uint8_t* const buffer,
                uint32_t* offset, uint32_t maxSize)
        {
            // check for nullptr
            if(nullptr == value || nullptr == buffer || nullptr == offset)
            {
                return StdReturnType::GENERAL_ERROR;
            }

            return value->DeSerialize(buffer, offset, maxSize);
        }

        /// @brief    Get the serialization size of the value.
        /// @param    value         Value to retrieve the size for.
        /// @return   Size of the serial representation of T.
        uint32_t GetSerializedSize(const T& value)
        {
            return value.GetSerializedSize();
        }

    };

public:

    /// @brief    Static method to support serialization of types.
    ///
    /// Uses internal SerializeAdapter_ class and partial specialization to determine the
    /// correct operation for serialization.
    /// @param[in] value         The value to serialize.
    /// @param[inout] buffer     Pointer to a buffer to be filled with object content.
    /// @param[inout] offset     Offset within the buffer. Is incremented by the serial representation size of T.
    /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
    /// @return  StdReturnType
    /// @retval  OK              Object was serialized
    /// @retval  GENERAL_ERROR   Not enough space for object or nullptr input.
    template<typename T>
    static StdReturnType Serialize(const T& value, uint8_t* const buffer,
            uint32_t* offset, uint32_t maxSize)
    {
        SerializeAdapter_<T> adapter;
        return adapter.Serialize(value, buffer, offset, maxSize);
    }

    /// @brief    Static method to support deserialization of types from stream.
    ///
    /// Uses internal SerializeAdapter_ class and partial specialization to determine the
    /// correct operation for deserialization.
    /// @param[out] value        The value to read from the buffer.
    /// @param[in] buffer        Pointer to a buffer from which the content is read.
    /// @param[inout] offset     Offset within buffer to read from. Is incremented by the serial representation size of T.
    /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of T may not be larger than maxSize.
    /// @return  StdReturnType
    /// @retval  OK              Object was serialized
    /// @retval  GENERAL_ERROR   Not enough data to read value from stream or nullptr input.
    template<typename T>
    static StdReturnType DeSerialize(T* value, const uint8_t* const buffer,
            uint32_t* offset, uint32_t maxSize)
    {
        SerializeAdapter_<T> adapter;
        return adapter.DeSerialize(value, buffer, offset, maxSize);
    }

    /// @brief    Get the serialization size of the value.
    /// @param    value         Value to retrieve the size for.
    /// @return   Size of the serial representation of T.
    template<typename T>
    static uint32_t GetSerializedSize(const T& value)
    {
        SerializeAdapter_<T> adapter;
        return adapter.GetSerializedSize(value);
    }
};

/// @brief Specific implementation for boolean type, as there's a 'int-in-bool-context' error when using the integer type.
/// Additionally, for some reason, the standard does not allow explicit specialisation in non-namespace scope.
/// The implementation does not rely on a certain sizeof(bool), but always represents it as one byte.
template<>
class SerializeAdapter::SerializeAdapter_<bool,
         utils::EnableIf<true>::type>
{
public:
    /// Bool is represented as 1 (true) or 0 (false) on the wire.
    /// @param[in] value         The value to serialise.
    /// @param[inout] buffer     Pointer to a buffer to be filled with object content.
    /// @param[inout] offset     Offset within the buffer. Is incremented by the serial representation size of bool (1).
    /// @param[in] maxSize       Maximum size of the buffer. offset + serial size of bool may not be larger than maxSize.
    /// @return  StdReturnType
    /// @retval  OK              Object was serialised
    /// @retval  GENERAL_ERROR   Not enough space for object or nullptr input.
    StdReturnType Serialize(const bool& value, uint8_t buffer[],
            uint32_t* offset, uint32_t maxSize)
    {
        // check for nullptr
        if((nullptr == buffer) || (nullptr == offset))
        {
            return StdReturnType::GENERAL_ERROR;
        }

        //Reserve one byte on the wire.
        if ((*offset + 1U) > maxSize)
        {
            return StdReturnType::GENERAL_ERROR;
        }
        if (true == value)
        {
            buffer[*offset] = 1U;
        }
        else
        {
            buffer[*offset] = 0U;
        }
        *offset += 1U;
        return StdReturnType::OK;
    }

    StdReturnType DeSerialize(bool* value, const uint8_t buffer[],
            uint32_t* offset, uint32_t maxSize)
    {
        // check for nullptr
        if((nullptr == value) || (nullptr == buffer) || (nullptr == offset))
        {
            return StdReturnType::GENERAL_ERROR;
        }

        //Reserve one byte on the wire.
        if ((*offset + 1U) > maxSize)
        {
            return StdReturnType::GENERAL_ERROR;
        }
        if (1U == buffer[*offset])
        {
            *value = true;
        }
        else if (0U == buffer[*offset])
        {
            *value = false;
        }
        else
        {
            return StdReturnType::GENERAL_ERROR;
        }
        *offset += 1U;
        return StdReturnType::OK;
    }

    /// @brief    Get the serialization size of the value.
    /// @param    value         Value to retrieve the size for.
    /// @return   Size of the serial representation of T.
    uint32_t GetSerializedSize(const bool& value)
    {
        (void)value;
        return 1U;
    }

};

}  // namespace utils

}  // namespace exm

#endif // QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_SERIALIZEADAPTER_HPP_
