//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by DENSO CORPORATION and Robert Bosch GmbH.
// All rights reserved.
//
// This file is property of DENSO CORPORATION and Robert Bosch GmbH. Any
// unauthorized copy, use or distribution is an offensive act against
// international law and may be prosecuted under federal law. Its content is
// company confidential.
//=============================================================================
//
/// @file      e2e_types.hpp
/// @brief     Common types for E2E
/// @copyright Robert Bosch GmbH  2022
//=============================================================================

#ifndef E2ETYPES_HPP
#define E2ETYPES_HPP

#include <cstddef>
#include <cstdint>

namespace com
{
namespace e2e
{
/// @brief The enumeration class defines the message type
enum class MessageType : uint8_t
{
    kRequest  = 0, ///< Request message
    kResponse = 1, ///< Response message
};

/// @brief The enumeration class defines the message result
enum class MessageResult : uint8_t
{
    kOk    = 0, ///< Request message or normal response message
    kError = 1, ///< Error response message
};

} // namespace e2e
} // namespace com

#endif
