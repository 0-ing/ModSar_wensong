//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================
//
/// @file common.h
/// @brief This file contains common types definitions for the logging API.
///
/// @attention Due to limitation of the C++ language, some internal implementation
/// (e.g. the function bodies) are coded directly into this header file.
/// Such code is NOT meant to be used or referred to by a user directly,
/// and is subject to CHANGE WITHOUT NOTICE.
/// Therefore DO NOT DEPEND ON any implementation details!
//==============================================================================
#ifndef ARA_LOG_COMMON_H_
#define ARA_LOG_COMMON_H_

#include <iostream>
#include <memory>
#include <ratio>
#include <string>
#include <type_traits>

namespace ara {
namespace log {

/**
 * @defgroup common Common Types
 * @brief Common type definitions for the logging API.
 */

/// @addtogroup common
/// @{

/**
 * @brief Log levels, in decreasing order of severity.
 *
 * Maps one-by-one to the values from DltLogLevelType.
 * @sa <dlt/dlt_types.h>
 *
 */
/// @traceid{SWS_LOG_00018}
enum class LogLevel : std::uint8_t {
    kOff = 0x00,     ///< No logging
    kFatal = 0x01,   ///< Fatal error, not recoverable
    kError = 0x02,   ///< Error with impact to correct functionality
    kWarn = 0x03,    ///< Warning if correct behavior cannot be ensured
    kInfo = 0x04,    ///< Informational, providing high level understanding
    kDebug = 0x05,   ///< Detailed information for programmers
    kVerbose = 0x06  ///< Extra-verbose debug messages (highest grade of information)
};

/**
 * @brief Log mode. Flags, used to configure the sink for log messages.
 * @note In order to combine flags, at least the OR and AND operators needs to be provided for this type.
 *
 */
/// @traceid{SWS_LOG_00019}
enum class LogMode : std::uint8_t {
    kRemote = 0x01,  ///< Sent remotely
    kFile = 0x02,    ///< Save to file
    kConsole = 0x04  ///< Forward to console
};

/**
 * Client state representing the connection state of an external client.
 */
/// @traceid{SWS_LOG_00098}
enum class ClientState : std::int8_t {
    kUnknown = -1,  //< DLT back-end not up and running yet, state cannot be determined
    kNotConnected,  //< No remote client detected
    kConnected      //< Remote client is connected
};

namespace internal {

/**
 * @brief LogReturn. Flags to define return values.
 * @note This is required to hide include/implementation of dlt on exported headers
 *
 * Maps one-by-one to the values from DltReturnValue.
 * @sa <dls/dlt_types.h>
 */
enum class LogReturnValue : std::int8_t {
    kReturnLoggingDisabled = -7,
    kReturnUserBufferFull = -6,
    kReturnWrongParameter = -5,
    kReturnBufferFull = -4,
    kReturnPipeFull = -3,
    kReturnPipeError = -2,
    kReturnError = -1,
    kReturnOk = 0,
    kReturnTrue = 1
};

/**
 * @brief Units of time in SI notation for a given ratio (period).
 * @note available units are:
 *  ns (nano second)
 *  us (micro second)
 *  ms (milli second)
 *  cs (centi second)
 *  ds (deci second)
 *  s (second)
 *  min (minute)
 *  h (hour)
 *  d (day)
 *  weeks : there is no standard symbol for week
 *  mo (month) : there is no standard symbol for month
 *  a (year)
 */

template <typename Period, typename std::enable_if<std::is_same<Period, std::nano>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "ns";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::micro>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "us";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::milli>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "ms";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::centi>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "cs";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::deci>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "ds";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::ratio<1>>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "s";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::ratio<60>>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "min";
}
template <typename Period, typename std::enable_if<std::is_same<Period, std::ratio<3600>>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "h";
}
template <typename Period, typename std::enable_if<std::is_same<Period, std::ratio<86400>>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "d";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::ratio<604800>>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "weeks";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::ratio<2629746>>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "mo";
}

template <typename Period, typename std::enable_if<std::is_same<Period, std::ratio<31556952>>::value>::type* = nullptr>
inline std::string duration_si_uint() {
    return "a";
}

}  // namespace internal

inline std::ostream& operator<<(std::ostream& os, const LogLevel& level) {
    switch (level) {
        case LogLevel::kOff:
            os << "Off";
            break;
        case LogLevel::kFatal:
            os << "Fatal";
            break;
        case LogLevel::kError:
            os << "Error";
            break;
        case LogLevel::kWarn:
            os << "Warn";
            break;
        case LogLevel::kInfo:
            os << "Info";
            break;
        case LogLevel::kDebug:
            os << "Debug";
            break;
        case LogLevel::kVerbose:
            os << "Verbose";
            break;
    }

    return os;
}

inline LogMode operator|(LogMode lhs, LogMode rhs) {
    return (static_cast<LogMode>(static_cast<typename std::underlying_type<LogMode>::type>(lhs) |
                                 static_cast<typename std::underlying_type<LogMode>::type>(rhs)));
}

inline typename std::underlying_type<LogMode>::type operator&(LogMode lhs, LogMode rhs) {
    return (static_cast<typename std::underlying_type<LogMode>::type>(lhs) &
            static_cast<typename std::underlying_type<LogMode>::type>(rhs));
}

/// @brief Maximum log message buffer size
/// @sa <dlt/dlt_user.h.in>
static constexpr size_t kLogBufMaxMsgSize = 300;

/// @brief Default log ring buffer size in bytes
/// @sa <dlt/dlt_user.h.in>
static constexpr size_t kRingbufferDefaultSize = 50000;

/// @}
} /* namespace log */
} /* namespace ara */

#endif  // ARA_LOG_COMMON_H_
