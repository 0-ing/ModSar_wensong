//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================
//
/// @file ILogStream.h
/// @brief This file contains the interface definition of LogStream
//==============================================================================

#ifndef BOSCH_VRTE_LOG_ILOGSTREAM_H_
#define BOSCH_VRTE_LOG_ILOGSTREAM_H_

#include <ara/core/error_code.h>
#include <ara/core/span.h>
#include <ara/core/string.h>
#include <ara/core/string_view.h>
#include <ara/core/utility.h>
#include <ara/log/common.h>

// Forward declarations
namespace ara {
namespace log {

struct LogHex8;
struct LogHex16;
struct LogHex32;
struct LogHex64;
struct LogBin8;
struct LogBin16;
struct LogBin32;
struct LogBin64;

}  // namespace log
}  // namespace ara

namespace bosch {
namespace vrte {
namespace log {

class ILogStreamImpl {
   public:
    virtual ~ILogStreamImpl() {
    }

    /**
     * @brief Check if logs should be forwarded
     *
     * Retrieves the internal forwarding state.
     * This will be false if the loglevel of the logger object is below the
     * LogStream loglevel.
     * Updates from the Logger will be fetched at construction and after every
     * flush.
     * @return Will messages be forwarded?
     */
    virtual bool isActive() = 0;

    virtual void Flush() = 0;
    /**
     * @brief Writes boolean parameter into message.
     *
     */
    virtual void operator<<(bool value) = 0;
    /**
     * @brief Writes unsigned int 8 bit parameter into message.
     *
     */
    virtual void operator<<(std::uint8_t value) = 0;
    /**
     * @brief Writes unsigned int 16 bit parameter into message.
     *
     */
    virtual void operator<<(std::uint16_t value) = 0;
    /**
     * @brief Writes unsigned int 32 bit parameter into message.
     *
     */
    virtual void operator<<(std::uint32_t value) = 0;
    /**
     * @brief Writes unsigned int 64 bit parameter into message.
     *
     */
    virtual void operator<<(std::uint64_t value) = 0;
    /**
     * @brief Writes signed int 8 bit parameter into message.
     *
     */
    virtual void operator<<(std::int8_t value) = 0;
    /**
     * @brief Writes signed int 16 bit parameter into message.
     *
     */
    virtual void operator<<(std::int16_t value) = 0;
    /**
     * @brief Writes signed int 32 bit parameter into message.
     *
     */
    virtual void operator<<(std::int32_t value) = 0;
    /**
     * @brief Writes signed int 64 bit parameter into message.
     *
     */
    virtual void operator<<(std::int64_t value) = 0;
    /**
     * @brief Writes float 32 bit parameter into message.
     *
     */
    virtual void operator<<(float value) = 0;
    /**
     * @brief Writes float 64 bit parameter into message.
     *
     */
    virtual void operator<<(double value) = 0;
    /**
     * @brief Writes null terminated UTF8 string into message.
     *
     */
    virtual void operator<<(const char* const value) = 0;
    /**
     *  @brief Writes ara::core::StringView into message.
     *
     */

    virtual void operator<<(const ara::core::StringView value) = 0;

    /**
     *  @brief Writes ara::core::String into message.
     *
     */
    virtual void operator<<(const ara::core::String& value) = 0;

    /**
     *  @brief Write a byte sequence into message.
     *
     */
    virtual void operator<<(ara::core::Span<const ara::core::Byte> data) = 0;

    /**
     * @brief Writes ara::log::LogHex parameter into message, formatted as hexadecimal 8 digits.
     *
     */
    virtual void operator<<(const ara::log::LogHex8& value) = 0;
    /**
     * @brief Writes ara::log::LogHex parameter into message, formatted as hexadecimal 16 digits.
     *
     */
    virtual void operator<<(const ara::log::LogHex16& value) = 0;
    /**
     * @brief Writes ara::log::LogHex parameter into message, formatted as hexadecimal 32 digits.
     *
     */
    virtual void operator<<(const ara::log::LogHex32& value) = 0;
    /**
     * @brief Writes ara::log::LogHex parameter into message, formatted as hexadecimal 64 digits.
     *
     */
    virtual void operator<<(const ara::log::LogHex64& value) = 0;
    /**
     * @brief Writes ara::log::LogBin parameter into message, formatted as binary 8 digits.
     *
     */
    virtual void operator<<(const ara::log::LogBin8& value) = 0;
    /**
     *  @brief Writes ara::log::LogBi parameter into message, formatted as binary 16 digits.
     *
     */
    virtual void operator<<(const ara::log::LogBin16& value) = 0;
    /**
     *  @brief Writes ara::log::LogBi parameter into message, formatted as binary 32 digits.
     *
     */
    virtual void operator<<(const ara::log::LogBin32& value) = 0;
    /**
     *  @brief Writes ara::log::LogBi parameter into message, formatted as binary 64 digits.
     *
     */
    virtual void operator<<(const ara::log::LogBin64& value) = 0;

    virtual void putValue(bool value, const char* name, const char* /*ignore*/) = 0;
    virtual void putValue(std::uint8_t value, const char* name, const char* unit) = 0;
    virtual void putValue(std::uint16_t value, const char* name, const char* unit) = 0;
    virtual void putValue(std::uint32_t value, const char* name, const char* unit) = 0;
    virtual void putValue(std::uint64_t value, const char* name, const char* unit) = 0;
    virtual void putValue(std::int8_t value, const char* name, const char* unit) = 0;
    virtual void putValue(std::int16_t value, const char* name, const char* unit) = 0;
    virtual void putValue(std::int32_t value, const char* name, const char* unit) = 0;
    virtual void putValue(std::int64_t value, const char* name, const char* unit) = 0;
    virtual void putValue(float value, const char* name, const char* unit) = 0;
    virtual void putValue(double value, const char* name, const char* unit) = 0;
    virtual void putValue(const ara::core::StringView& value, const char* name, const char* /*ignore*/) = 0;
    virtual void putValue(const char* value, const char* name, const char* /*ignore*/) = 0;
    virtual void putValue(const ara::core::Span<const ara::core::Byte>& value, const char* name,
                          const char* /*ignore*/) = 0;
};

}  // namespace log
}  // namespace vrte
}  // namespace bosch
#endif  // BOSCH_VRTE_LOG_ILOGSTREAM_H_
