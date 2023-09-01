//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ISerialize.hpp
/// @brief     Interface to allow objects to be serialized and deserialized
/// @copyright Robert Bosch GmbH  2018
/// @author    baetz

#ifndef QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ISERIALIZE_HPP_
#define QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ISERIALIZE_HPP_

#include <stdint.h>
#include "utils/StdReturnType.hpp"

namespace exm {

namespace utils {

/// @brief Interface to allow objects to be serialized and deserialized.
class ISerialize {
public:

    /// @brief Virtual destructor foor interfaces.
    virtual ~ISerialize() {
    }

    /// @brief Serialize the object into a buffer.
    /// @param[inout] buffer     Pointer to a buffer to be filled with object content.
    /// @param[inout] offset     Offset within the buffer. Shall be incremented by object size.
    /// @param[in] maxSize       Maximum size of the buffer. offset + object size shall not be larger than maxSize.
    /// @return  StdReturnType
    /// @retval  OK              Object was serialized
    /// @retval  GENERAL_ERROR   Not enough space for object.
    virtual StdReturnType Serialize(uint8_t* const buffer, uint32_t* offset, uint32_t maxSize) const = 0;

    /// @brief Deserialize object content from buffer.
    /// @param[in] buffer        Pointer to a buffer from which the content is read.
    /// @param[inout] offset     Offset within buffer to read from. Shall be incremented by object size.
    /// @param[in] maxSize       Maximum size of the buffer. offset + object size shall not be larger than maxSize.
    /// @return  StdReturnType
    /// @retval  OK              Object was serialized
    /// @retval  GENERAL_ERROR   Not enough data to read object.
    virtual StdReturnType DeSerialize(const uint8_t* const buffer, uint32_t* offset, uint32_t maxSize) = 0;

    /// @brief Method to return the serialization size of the object.
    /// @return      Size of serial representation of the object in bytes.
    virtual uint32_t GetSerializedSize() const = 0;
};

}  // namespace utils

}  // namespace exm

#endif // QNX_EXM_DELIVERABLES_SRC_UTILS_INC_UTILS_ISERIALIZE_HPP_
