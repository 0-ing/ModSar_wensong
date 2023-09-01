//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2020-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================
//
/// @file logstream.h
/// @brief This file contains the stream based message handler.
///
/// @attention Due to limitation of the C++ language, some internal implementation
/// (e.g. the function bodies) are coded directly into this header file.
/// Such code is NOT meant to be used or referred to by a user directly,
/// and is subject to CHANGE WITHOUT NOTICE.
/// Therefore DO NOT DEPEND ON any implementation details!
//==============================================================================
#ifndef ARA_LOG_LOG_STREAM_H_
#define ARA_LOG_LOG_STREAM_H_

#include <chrono>
#include <memory>
#include <string>
#include <utility>

#ifndef ARA_NO_EXCEPTIONS
#include <ara/core/instance_specifier.h>
#endif

#include "ara/log/common.h"
#include "bosch/vrte/log/ILogStream.h"

namespace bosch {
namespace vrte {
namespace log {

class ILogChannel;

}  // namespace log
}  // namespace vrte
}  // namespace bosch

namespace ara {
namespace log {
/**
 * @defgroup logstream Log Stream
 * @brief Stream based message handler.
 */

/**
 * @ingroup logstream
 * @class LogStream
 *
 * @brief Class representing a log message.
 *
 * Insert stream operators are to be used for appending data.
 *
 * @note Normally, you would not use this class directly, but use one of the log methods provided in
 * the main logging API or an instance of the Logger class instead. Those methods automatically setup
 * an object of this class with the given log severity level. The only reason to get in touch with this
 * class directly is if you want to hold a @c LogStream object longer than the default one-statement scope.
 * This is useful in order to create log messages that are distributed over multiple code lines.
 * See @c Flush() method for further information.
 *
 * Every call on the insert stream operator against this object will be processed as a call to the
 * underlying DLT back-end, which means that the message buffer is going to be filled with payload data.
 *
 * Once this object gets out of scope (in normal usage as soon as the statement ends), its @c dtor is
 * calling the message flush command on the DLT back-end which marks the message buffer as ready to be
 * sent out remotely.
 *
 * @c LogStream supports all of the primitive data types (PoDs) natively. However, it can be easily extended
 * for your own complex types by providing a stream operator that makes use of already supported types.
 *
 * @code
 * struct MyCustomType {
 *   std::int8_t foo;
 *   std::string bar;
 * };
 *
 * LogStream& operator<<(LogStream& out, const MyCustomType& value) {
 *     return (out << value.foo << value.bar);
 * }
 *
 * g_loggerCtx0.LogDebug() << MyCustomType{42, "The answer is"};
 * @endcode
 */

// Forward declarations
class Logger;

/*
 * Helper struct that is utilized as custom type.
 * Holds an integer value that will be logged with a special format.
 */
/// @traceid{SWS_LOG_00108}
struct LogHex8 {
    std::uint8_t value;
};
/// @traceid{SWS_LOG_00109}
struct LogHex16 {
    std::uint16_t value;
};
/// @traceid{SWS_LOG_00110}
struct LogHex32 {
    std::uint32_t value;
};
/// @traceid{SWS_LOG_00111}
struct LogHex64 {
    std::uint64_t value;
};
/// @traceid{SWS_LOG_00112}
struct LogBin8 {
    std::uint8_t value;
};
/// @traceid{SWS_LOG_00113}
struct LogBin16 {
    std::uint16_t value;
};
/// @traceid{SWS_LOG_00114}
struct LogBin32 {
    std::uint32_t value;
};
/// @traceid{SWS_LOG_00115}
struct LogBin64 {
    std::uint64_t value;
};
/*
 * Structure that is utilized to create wrapper object for the given arguments.
 * Holds an argument payload object, name & unit attribute for argument.
 */
template <typename T>
struct Argument {
    const T value;
    const char* const name;
    const char* const unit;
};

/// @brief LogStream class
/// @version LOGSTREAM_MAJOR 1
/// @version LOGSTREAM_MINOR 0
class LogStream final {
   public:
    LogStream() = delete;

    /**
     * @brief Creates the message stream object.
     *
     * Initiates it with the given log level directly on the back-end.
     *
     * @param[in] logLevel  The severity level of this message
     * @param[in] logger    The associated logger context
     */
    LogStream(LogLevel logLevel, Logger& logger) noexcept;
    LogStream(LogLevel logLevel, bosch::vrte::log::ILogChannel* logger) noexcept;

    /**
     * @brief Flushes the log message before destroying the stream object.
     *
     * Unless it was not explicitly flushed before, by calling @c Flush().
     */
    ~LogStream();

    /*
     * The big five.
     *
     * We actually don't want this class movable or copyable, but enforce RVO instead.
     * Since "Guaranteed copy elision" will be supported up from C++17, declaring the move ctor
     * without definition is a workaround and is necessary because we have a custom dtor.
     * With the missing move ctor implementation, explicit calls of std::move() on objects
     * of this class, will be prevented by a compile error.
     */
    LogStream(const LogStream&) = delete;
    LogStream& operator=(const LogStream&) = delete;
    LogStream(LogStream&&);
    LogStream& operator=(LogStream&&) = delete;

    /**
     * @brief Processes the current log buffer.
     *
     * And prepares the object for new message in one go. Further usage of the @c LogStream object
     * after calling this method will end up in a new message. Use this method in case you want to
     * build your message distributed over multiple code lines.
     *
     * @code
     * LogStream logInfoBuilder{g_loggerCtx0.LogInfo()};
     * logInfoBuilder << "message builder...";
     *
     * logInfoBuilder << 123;
     * logInfoBuilder << "one more param.";
     * logInfoBuilder << 4.56;
     * logInfoBuilder << "we're done...";
     * logInfoBuilder.Flush(); // sends out what is in the buffer as one single message
     *
     * logInfoBuilder << "new message initiated...";
     * @endcode
     *
     * @note Calling @c Flush() is only necessary if the @c LogStream object is going to be re-used within
     * the same scope. Otherwise, if the object goes out of scope (e.g. end of function block), than
     * flush operation will be anyway done internally by the @c dtor.
     *
     */
    /// @traceid{SWS_LOG_00039}
    void Flush() noexcept;
    /// @name DLT primitive types
    /// Build-in support for DLT native types.
    /// @{
    /**
     * @brief Writes boolean parameter into message.
     *
     * @param[in] value  bool value
     * @return    bool value written to LogStream
     */
    /// @traceid{SWS_LOG_00040}
    LogStream& operator<<(bool value) noexcept;
    /**
     * @brief Writes unsigned int 8 bit parameter into message.
     *
     * @param[in] value  unsigned int value to be represented in 8 bit
     * @return    unsigned int 8 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00041}
    LogStream& operator<<(std::uint8_t value) noexcept;
    /**
     * @brief Writes unsigned int 16 bit parameter into message.
     *
     * @param[in] value  unsigned int value to be represented in 16 bit
     * @return    unsigned int 16 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00042}
    LogStream& operator<<(std::uint16_t value) noexcept;
    /**
     * @brief Writes unsigned int 32 bit parameter into message.
     *
     * @param[in] value  unsigned int value to be represented in 32 bit
     * @return    unsigned int 32 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00043}
    LogStream& operator<<(std::uint32_t value) noexcept;
    /**
     * @brief Writes unsigned int 64 bit parameter into message.
     *
     * @param[in] value  unsigned int value to be represented in 64 bit
     * @return    unsigned int 64 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00044}
    LogStream& operator<<(std::uint64_t value) noexcept;
    /**
     * @brief Writes signed int 8 bit parameter into message.
     *
     * @param[in] value  signed int value to be represented in 8 bit
     * @return    signed int 8 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00045}
    LogStream& operator<<(std::int8_t value) noexcept;
    /**
     * @brief Writes signed int 16 bit parameter into message.
     *
     * @param[in] value  signed int value to be represented in 16 bit
     * @return    signed int 16 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00046}
    LogStream& operator<<(std::int16_t value) noexcept;
    /**
     * @brief Writes signed int 32 bit parameter into message.
     *
     * @param[in] value  signed int value to be represented in 32 bit
     * @return    signed int 32 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00047}
    LogStream& operator<<(std::int32_t value) noexcept;
    /**
     * @brief Writes signed int 64 bit parameter into message.
     *
     * @param[in] value  signed int value to be represented in 64 bit
     * @return    signed int 64 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00048}
    LogStream& operator<<(std::int64_t value) noexcept;
    /**
     * @brief Writes float 32 bit parameter into message.
     *
     * @param[in] value  float value to be represented in 32 bit
     * @return    float 32 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00049}
    LogStream& operator<<(float value) noexcept;
    /**
     * @brief Writes float 64 bit parameter into message.
     *
     * @param[in] value  signed int value to be represented in 64 bit
     * @return    double 64 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00050}
    LogStream& operator<<(double value) noexcept;
    /**
     * @brief Writes null terminated UTF8 string into message.
     *
     * @param[in] value  const char pointer value
     * @return    string value written to LogStream
     */
    /// @traceid{SWS_LOG_00051}
    LogStream& operator<<(const char* const value) noexcept;
    /// @}

    /// @name DLT special types
    /// Build-in support for DLT special format types.
    /// @{

    /**
     * @brief Writes unsigned int parameter into message, formatted as hexadecimal 8 digits.
     *
     * @param[in] value  hexadecimal value to be represented in 8 bit
     * @return    unsigned int 8 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00053}
    LogStream& operator<<(const LogHex8& value) noexcept;

    /**
     * @brief Writes unsigned int parameter into message, formatted as hexadecimal 16 digits.
     *
     * @param[in] value  hexadecimal int value to be represented in 16 bit
     * @return    unsigned int 16 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00054}
    LogStream& operator<<(const LogHex16& value) noexcept;

    /**
     * @brief Writes unsigned int parameter into message, formatted as hexadecimal 32 digits.
     *
     * @param[in] value  hexadecimal int value to be represented in 32 bit
     * @return    unsigned int 32 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00055}
    LogStream& operator<<(const LogHex32& value) noexcept;

    /**
     * @brief Writes unsigned int parameter into message, formatted as hexadecimal 64 digits.
     *
     * @param[in] value  hexadecimal int value to be represented in 64 bit
     * @return    unsigned int 64 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00056}
    LogStream& operator<<(const LogHex64& value) noexcept;

    /**
     * @brief Writes unsigned int parameter into message, formatted as binary 8 digits.
     *
     * @param[in] value  binary value to be represented in 8 bit
     * @return    unsigned int 8 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00057}
    LogStream& operator<<(const LogBin8& value) noexcept;

    /**
     *  @brief Writes unsigned int parameter into message, formatted as binary 16 digits.
     *
     * @param[in] value  binary value to be represented in 16 bit
     * @return    unsigned int 16 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00058}
    LogStream& operator<<(const LogBin16& value) noexcept;

    /**
     *  @brief Writes unsigned int parameter into message, formatted as binary 32 digits.
     *
     * @param[in] value  binary value to be represented in 32 bit
     * @return    unsigned int 32 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00059}
    LogStream& operator<<(const LogBin32& value) noexcept;

    /**
     *  @brief Writes unsigned int parameter into message, formatted as binary 64 digits.
     *
     * @param[in] value  binary value to be represented in 64 bit
     * @return    unsigned int 64 bit value written to LogStream
     */
    /// @traceid{SWS_LOG_00060}
    LogStream& operator<<(const LogBin64& value) noexcept;

    /**
     *  @brief Writes ara::core::StringView into message.
     *
     * @param[in] value  ara::core::StringView value
     * @return    ara::core::StringView value written to LogStream
     */
    /// @traceid{SWS_LOG_00062}
    LogStream& operator<<(const ara::core::StringView value) noexcept;

    /**
     *  @brief Writes ara::core::String into message.
     *
     * @param[in] value  ara::core::String value
     * @return    ara::core::String value written to LogStream
     */
    LogStream& operator<<(const ara::core::String& value) noexcept;

    /**
     *  @brief Writes source file location into the message.
     *         Format: <FileName>:<LineNum> <Payload>
     *         Example usage:  WithLocation(__FILE__, __LINE__)
     *                         WithLocation(__FILE__, 2)
     *
     * @param[in] file  ara::core::StringView value
     * @param[in] line  int value
     * @return    source file location written to LogStream
     */
    /// @traceid{SWS_LOG_00129}
    LogStream& WithLocation(core::StringView file, int line) noexcept;

    /**
     *  @brief Writes ara::core::Span into message.
     *
     * @param[in] data  core Byte data
     * @return    core::Span< const core::Byte > written to LogStream
     */
    LogStream& operator<<(core::Span<const core::Byte> data) noexcept;

    /**
     * @brief Writes an argument with attributes into the message
     *
     * @param[in] arg  ara::log::Argument object
     * @return    ara::core::Argument attributes written to LogStream
     * @traceid{SWS_LOG_00203}
     */
    template <typename T>
    LogStream& operator<<(const Argument<T>& arg) noexcept {
        putValue(arg.value, arg.name, arg.unit);
        return *this;
    }

    /// @}

   private:
    void* logLocalData_;  // TODO: Remove after complete rollout of ara-log mocks to other fcs

    void putValue(bool value, const char* name, const char* /*ignore*/) noexcept;
    void putValue(std::uint8_t value, const char* name, const char* unit) noexcept;
    void putValue(std::uint16_t value, const char* name, const char* unit) noexcept;
    void putValue(std::uint32_t value, const char* name, const char* unit) noexcept;
    void putValue(std::uint64_t value, const char* name, const char* unit) noexcept;
    void putValue(std::int8_t value, const char* name, const char* unit) noexcept;
    void putValue(std::int16_t value, const char* name, const char* unit) noexcept;
    void putValue(std::int32_t value, const char* name, const char* unit) noexcept;
    void putValue(std::int64_t value, const char* name, const char* unit) noexcept;
    void putValue(float value, const char* name, const char* unit) noexcept;
    void putValue(double value, const char* name, const char* unit) noexcept;
    void putValue(const ara::core::StringView& value, const char* name, const char* /*ignore*/) noexcept;
    void putValue(const char* value, const char* name, const char* /*ignore*/) noexcept;
    void putValue(const ara::core::Span<const ara::core::Byte>& value, const char* name,
                  const char* /*ignore*/) noexcept;

    /**
     * ToDo: The type needs to be made opaque. It cannot be made opaque now, because other FCs implement LogStream
     * stubs in their test code. They will get unknown type errors if they cannot call a destructor on the pImpl.
     */
    std::unique_ptr<bosch::vrte::log::ILogStreamImpl> pImpl_;
};

/// Support for LogStream objects as rvalue reference. Enables custom type <<operator overload as first call
template <typename T>
LogStream& operator<<(LogStream&& out, T&& value) noexcept {
    return (out << std::forward<T>(value));
}

/// Support for signed long long (transforms into std::int64_t on 64 bit platforms)
template <typename T = void, typename std::enable_if<((!std::is_same<long long, std::int64_t>::value) &&
                                                      (sizeof(long long) == sizeof(std::int64_t))),
                                                     T>::type* = nullptr>
inline LogStream& operator<<(LogStream& out, long long value) noexcept {
    return (out << static_cast<std::int64_t>(value));
}

/// Support for unsigned long long (transforms into std::uint64_t on 64 bit platforms)
template <typename T = void, typename std::enable_if<((!std::is_same<unsigned long long, std::uint64_t>::value) &&
                                                      (sizeof(unsigned long long) == sizeof(std::uint64_t))),
                                                     T>::type* = nullptr>
inline LogStream& operator<<(LogStream& out, unsigned long long value) noexcept {
    return (out << static_cast<std::uint64_t>(value));
}

/// @name Extra types
/// Support for extra types that transforms into DLT native types.
/// @addtogroup logstream
/// @{
/// @brief Writes LogLevel enum parameter as text into message.
/// @traceid{SWS_LOG_00063}
LogStream& operator<<(LogStream& out, LogLevel value) noexcept;

constexpr LogHex32 loghex(std::uint32_t val) noexcept {
    return LogHex32{val};
}
constexpr LogHex64 loghex(std::uint64_t val) noexcept {
    return LogHex64{val};
}

/// @brief Writes pointer address into message, formatted as hexadecimal.
inline LogStream& operator<<(LogStream& out, const void* const value) noexcept {
    return (out << loghex(reinterpret_cast<std::uintptr_t>(value)));
}

/// @brief Writes std::string into message.
inline LogStream& operator<<(LogStream& out, const std::string& value) noexcept {
    return (out << value.c_str());
}

#ifndef ARA_NO_EXCEPTIONS
/// @brief Writes ara::core::InstanceSpecifier into message.
/// @traceid{SWS_LOG_00126}
inline LogStream& operator<<(LogStream& out, const ara::core::InstanceSpecifier& value) noexcept {
    return (out << value.ToString());
}
#endif

namespace {
// lambda to get ara::core::String from const char*, to overcome lack of operator+ overloads
// and rvalue assignments to non-const reference of core String type.
auto to_str = [](const char* str) -> ara::core::String { return ara::core::String(str); };
}  // namespace

/// @brief Writes ara::core::ErrorCode into message.
/// @traceid{SWS_LOG_00124}
inline LogStream& operator<<(LogStream& out, const core::ErrorCode& ec) noexcept {
    // Frame the ErrorCode message as mentioned in SWS_LOG_00124, Chapt. 8.3.1
    ara::core::String error_str = to_str("ErrorDomain: ") + ec.Domain().Name();
    error_str += to_str(", ErrorCode: ") + std::to_string(ec.Value());
    error_str += to_str(", ErrorMessage: ") + ec.Message().data();

    return (out << error_str.data());
}

/// @brief Writes std::chrono::duration instance with corresponding unit in SI notation into the message
/// @traceid{SWS_LOG_00125}
/// @brief Writes std::chrono::duration instance with signed long long data type
template <typename Rep, typename Period, std::enable_if_t<std::is_same<long long, Rep>::value, bool> = true>
inline LogStream& operator<<(LogStream& out, const std::chrono::duration<Rep, Period>& value) noexcept {
    return (out << static_cast<std::int64_t>(value.count()) << internal::duration_si_uint<Period>());
}

/// @brief Writes std::chrono::duration instance with unsigned long long data type
template <typename Rep, typename Period, std::enable_if_t<std::is_same<unsigned long long, Rep>::value, bool> = true>
inline LogStream& operator<<(LogStream& out, const std::chrono::duration<Rep, Period>& value) noexcept {
    return (out << static_cast<std::uint64_t>(value.count()) << internal::duration_si_uint<Period>());
}

/// @brief Writes std::chrono::duration instance with all other data type
template <typename Rep, typename Period,
          std::enable_if_t<!std::is_same<unsigned long long, Rep>::value && !std::is_same<long long, Rep>::value,
                           bool> = true>
inline LogStream& operator<<(LogStream& out, const std::chrono::duration<Rep, Period>& value) noexcept {
    return (out << value.count() << internal::duration_si_uint<Period>());
}

/// @}

}  // namespace log
}  // namespace ara

#endif  // ARA_LOG_LOG_STREAM_H_
