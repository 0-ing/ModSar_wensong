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
/// @file logger.h
/// @brief This file contains the DLT context abstraction for the logging API.
///
/// @attention Due to limitation of the C++ language, some internal implementation
/// (e.g. the function bodies) are coded directly into this header file.
/// Such code is NOT meant to be used or referred to by a user directly,
/// and is subject to CHANGE WITHOUT NOTICE.
/// Therefore DO NOT DEPEND ON any implementation details!
//==============================================================================
#ifndef ARA_LOG_LOGGER_H_
#define ARA_LOG_LOGGER_H_

#include <string>
#include <utility>

#include "ara/core/string.h"
#include "ara/core/string_view.h"
#include "ara/log/common.h"
#include "ara/log/log_stream.h"
#include "bosch/vrte/log/ILogger.h"

namespace ara {
namespace log {
/**
 * @brief The high-level logging API for AUTOSAR adaptive applications.
 *
 * It is based on the _Genivi DLT back-end_ and provides simple to use log methods and additional
 * formatting utilities. It also abstracts the de-/registration phases as well as the DLT back-end
 * resource handling.
 *
 * This logging API supports the Genivi DLT version __2.18.5__ and newer.
 *
 * @sa <a href="https://github.com/GENIVI/dlt-daemon">DLT-Daemon at Github</a> and
 *     <a href="https://github.com/GENIVI/dlt-viewer">DLT-Viewer at Github</a>
 *
 * The logging API supports the concept of _logging contexts_ as defined by DLT. This means that each log
 * message is associated with a particular log context. The <a href="https://github.com/GENIVI/dlt-viewer">
 * DLT-Viewer</a> application allows for filtering of such contexts as well as adjusting log severity
 * per context during runtime.
 *
 * It is up to the application developer whether he want to use multiple contexts, categorized by
 * sub-functionality, classes/modules, threads or whatever, or whether he just want to use a single
 * default context for the whole application.
 *
 * The logging API offers ready-to-use stream based calls that already supports all primitive data types.
 * The advantage is that applications can extend the logging framework to understand new/custom
 * types simply by providing the relevant stream operators as overloads, without having to touch the
 * framework's code itself.
 *
 * @sa Read description of @c LogStream for how-to write custom type handlers.
 *
 * @par Initialization
 * In order to distinguish the logs from different applications, every application in the system
 * a particular ID (_up to four-character_) and a description has to be assigned.
 * @par
 * These values has to be provided to the internal logging manager in order to register with the
 * DLT back-end. The user also has to specify the application's default log level. Only log messages
 * that have a higher log severity level will be processed. The log level is adjustable during runtime
 * via some client (e.g. <a href="https://github.com/GENIVI/dlt-viewer">DLT-Viewer</a>).
 *
 * @note It is highly recommended to assign system-wide unique IDs per application and even per process,
 * in case same application is started multiple times. If multiple processes registers with the same ID,
 * the logs will be mixed up, and the log output will be hardly to filter and to read. It is advised to
 * keep and maintain a central list of _ID to application/instance_.
 *
 * @attention If some application is allowed to fork, which is normally forbidden in AUTOSAR adaptive,
 * except for a very few special applications, the init call must be done __AFTER__ forking, otherwise
 * we will end up in undefined behavior. Apart from that, the logging API and the DLT back-end is thread
 * safe. That means, logging can be done asynchronous from multiple threads, within one registered
 * application and within same logging contexts.
 *
 * @par Logging contexts
 * To be able to log at least one context needs to be available per application. Logging contexts are
 * represented by the class @c Logger. Hereafter _logger_ or _DLT context_ are used as synonyms
 * for _logging context_.
 * @par
 * If the application requires only trivial logging setup, meaning if there is no need to have more
 * than one context at all, it is not necessary to create a context manually. The logging API will
 * provide one default context, based on lazy-init at the very first attempt to do a message log via
 * the convenience methods _Log<LogLevel>()_.
 * @par
 * Contexts are identified similarly like the application by an _up to four-character_ ID and
 * a description. They can either be defined scoped (within class or function or compilation unit),
 * or just globally. The default context provided by the logging framework, will get the ID _DFLT_.
 *
 * @warning Creating loggers __MUST__ be done via the convenience method @c CreateLogger().
 * Don't call @c Logger's @link
 * Logger::Logger(const std::string& ctxId, const std::string& ctxDescription, LogLevel ctxDefLogLevel)
 * @c ctor @endlink by yourself unless you know what you do.
 *
 * @note For runtime critical applications, it might be of interest to prevent any side effects
 * caused by the lazy-init of the default logger (if used at all) when doing the very first message
 * log. To achieve this, just do a log of some informal nature within your application init-phase.
 * However, this is optional.
 *
 * This is all that needs to be done in order to be able to start logging. Everything else is setup
 * and handled automatically in background.
 *
 * @par Early logging
 * All messages logged before the initialization is done will be stored inside a ring-buffer
 * with a limited size. That means, oldest entries are lost if the buffer exceeds.
 *
 * @note In DLT every context has its own severity level. To make the usage of the API less complex
 * an application-wide log level (that one specified in the init-phase) applies to all contexts until
 * they are changed by some DLT client, remotely. Since the loggers can be created before the
 * initialization call, they are created per default with most verbose level, to enable early logging.
 * That means, until the logging framework is not initialized, it is possible to log already into the
 * globally defined loggers with most verbose severity. As soon as the the logging framework becomes
 * up and running, all contexts are settled to the application-wide log level. This ensures that no
 * messages are lost before the init-phase.
 *
 * @par Usage
 * Only the main public header needs to be included and the logging namespace to shortcut the usage
 * (optional but recommended):
 * @code
 * #include <ara/logging/logger.h>
 * using namespace ara::log;
 *
 * Logger& g_loggerCtx0{CreateLogger(CTX0, "some context of application ABCD")}
 *
 * g_loggerCtx0.LogDebug() << "The answer is" << 42;
 * LogDebug() << "log into default context provided by the framework";
 * @endcode
 *
 * Behind the scenes, these methods creates a @c LogStream temporary object and prepares it for the
 * given log level. Every passed stream argument is getting copied to the internal message buffer
 * as payload with evaluated type information. There is no need to put spaces in between the single
 * arguments as client applications will represent the arguments anyway one-by-one.
 *
 * @par Message length
 * The maximum size of one single message that can be sent out depends on the underlying
 * _Genivi DLT back-end_ implementation, which is defined in @c DLT_USER_BUF_MAX_SIZE (inside
 * <dlt/dlt_user.h>). So, theoretically developers can add as much arguments as they want to the
 * message stream, if a message exceeds the buffer length, it will be simply cut-off by the back-end.
 * This needs to be kept in mind when dealing with big data that is to be logged, especially in
 * conjunction with the @c RawBuffer() stream handler.
 *
 * @warning Do not log in code triggered by the destruction of global/static objects. As the destruction
 * order of static objects is unspecified, your application may crash due to the fact that the logging
 * framework itself, or other relevant instances, having been already deregistered from DLT and killed
 * prior to your own instances. It is good practice to completely avoid logging in destructors unless
 * you can be absolutely sure that the object in question is destroyed during the runtime of the
 * application, rather than during the cleanup phase for static objects (after exiting @c main()).
 */

/**
 * @ingroup logger
 * @class Logger
 *
 * @brief Class representing a DLT logger context.
 *
 * DLT defines so called _contexts_ which can be seen as logger instances within one application
 * or process scope. Contexts have the same properties to be set up as for the application:
 *  -# ID (_up to four-character_)
 *  -# description text (opt.)
 *  -# default log severity level
 *
 * A context will be automatically registered against the DLT back-end during creation phase, as well
 * as automatically deregistered during process shutdown phase. So the end user does not care for the
 * objects life time.
 *
 * @warning Actually the user is not allowed to create a @c Logger object by himself. @c Logger contexts
 * needs to be created by the provided API call @c CreateLogger(). This is because the internal @c LogManager
 * is tracking all created log contexts and does checking for correct ID naming convention as well
 * as multiple instantiation attempts.
 */
/// @brief Logger class
class Logger final : public bosch::vrte::log::ILogger {
   private:
    bosch::vrte::log::ILogChannel* log_channel_;

   public:
    /**
     * @brief Creates a @c Logger object.
     *
     * Holds the DLT context which is registered in the DLT back-end.
     *
     * @warning This ctor __MUST__ not be used directly by an application, instead it is designated to
     * be called by the internal LogManager only, since it does track of the instances and cares for
     * the proper de-/registration in the DLT back-end. The only reason why this ctor is not private
     * is some technical issues with _c++11 std::forward_ implementation - it needs the ctor to be public.
     *
     * @param[in] ctxId             The _up to four-character_ ID
     * @param[in] ctxDescription    Some description
     * @param[in] ctxDefLogLevel    The context's default log reporting level
     */
    Logger(const ara::core::StringView& ctxId, const ara::core::StringView& ctxDescription, LogLevel ctxDefLogLevel);

    Logger(bosch::vrte::log::ILogChannel* log_channel);

    /**
     * @brief Creates a @c LogStream object.
     *
     * Returned object will accept arguments via the _insert stream operator_ "@c <<".
     *
     * @note In the normal usage scenario, the object's life time of the created @c LogStream is scoped
     * within one statement (ends with @c ; after last passed argument). If one wants to extend the
     * @c LogStream object's life time, the object might be assigned to a named variable.
     * @see Refer to the @c LogStream class documentation for further details.
     *
     * @return  @c LogStream object of Fatal severity.
     *
     */
    LogStream LogFatal() noexcept;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c LogStream object of Error severity.
     *
     */
    LogStream LogError() noexcept;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c LogStream object of Warn severity.
     *
     */
    LogStream LogWarn() noexcept;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c LogStream object of Info severity.
     *
     */
    LogStream LogInfo() noexcept;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c LogStream object of Debug severity.
     *
     */
    LogStream LogDebug() noexcept;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c LogStream object of Verbose severity.
     *
     */
    LogStream LogVerbose() noexcept;

    /**
     * @brief Check current configured log reporting level.
     *
     * Applications may want to check the actual configured reporting log level of certain loggers
     * before doing log data preparation that is runtime intensive.
     *
     * @param[in] logLevel  The to be checked log level.
     * @return              True if desired log level satisfies the configured reporting level.
     *
     */
    bool IsLogEnabled(LogLevel logLevel) const noexcept;

    /**
     * @brief Return the current active backend context
     *
     * @note The only current supported backend is DLT, but the direct access and implementation
     * should be hidden from the class consumer.
     */
    void* GetContext();

    /**
     * @brief Returns the context ID.
     * @return The _up to four-character_ ID
     */
    std::string GetId() const noexcept;
};

/**
 * @brief Creates a Logger instance.
 *
 * Holds the DLT context which is registered in the DLT back-end.
 *
 * @code
 * Logger& g_loggerCtx0{CreateLogger(CTX0, "the default context of application ABCD")}
 * @endcode
 *
 * @param[in] ctxId             The _up to four-character_ ID
 * @param[in] ctxDescription    Some description
 * @return                      @c Logger object of type @c Logger&
 */
Logger& CreateLogger(ara::core::StringView ctxId, ara::core::StringView ctxDescription) noexcept;

/**
 * @brief CreateLogger overload, Creates a Logger instance with a specified default LogLevel
 *
 * Holds the DLT context which is registered in the DLT back-end.
 *
 * @code
 * Logger& g_loggerCtx0{CreateLogger(CTX0, "the default context of application ABCD", LogLevel::kInfo)}
 * @endcode
 *
 * @param[in] ctxId             The up to four-character Context ID
 * @param[in] ctxDescription    Description of the Context object
 * @param[in] ctxDefLogLevel    The Context's default log reporting level
 * @return                      @c Logger object of type @c Logger&
 */
Logger& CreateLogger(ara::core::StringView ctxId, ara::core::StringView ctxDescription,
                     LogLevel ctxDefLogLevel) noexcept;
/**
 * @brief  Logs decimal numbers in hexadecimal format.
 *
 * Negatives are represented in 2's complement. The number of represented digits depends on the
 * overloaded parameter type length.
 *
 * @code
 * std::uint16_t num = 42;
 * LogInfo() << "This is some number in hex:" << HexFormat(num);
 * LogInfo() << "This is some negative number in hex:" << HexFormat(-num);
 * @endcode
 *
 * @param[in] value Decimal number to be represented in 8 digits
 * @return          @c LogHex8 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00022}
 */
constexpr LogHex8 HexFormat(std::uint8_t value) noexcept {
    return LogHex8{value};
}

/**
 * @brief Same as @c HexFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 8 digits
 * @return          @c LogHex16 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00023}
 */
constexpr LogHex8 HexFormat(std::int8_t value) noexcept {
    return LogHex8{static_cast<std::uint8_t>(value)};
}

/**
 * @brief Same as @c HexFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 16 digits
 * @return          @c LogHex16 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00024}
 */
constexpr LogHex16 HexFormat(std::uint16_t value) noexcept {
    return LogHex16{value};
}

/**
 * @brief Same as @c HexFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 16 digits
 * @return          @c LogHex16 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00025}
 */
constexpr LogHex16 HexFormat(std::int16_t value) noexcept {
    return LogHex16{static_cast<std::uint16_t>(value)};
}

/**
 * @brief Same as @c HexFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 32 digits
 * @return          @c LogHex32 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00026}
 */
constexpr LogHex32 HexFormat(std::uint32_t value) noexcept {
    return LogHex32{value};
}

/**
 * @brief Same as @c HexFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 32 digits
 * @return          @c LogHex32 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00027}
 */
constexpr LogHex32 HexFormat(std::int32_t value) noexcept {
    return LogHex32{static_cast<std::uint32_t>(value)};
}

/**
 * @brief Same as @c HexFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 64 digits
 * @return          @c LogHex64 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00028}
 */
constexpr LogHex64 HexFormat(std::uint64_t value) noexcept {
    return LogHex64{value};
}

/**
 * @brief Same as @c HexFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 64 digits
 * @return          @c LogHex64 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00015}
 * @traceid{SWS_LOG_00016}
 * @traceid{SWS_LOG_00029}
 */
constexpr LogHex64 HexFormat(std::int64_t value) noexcept {
    return LogHex64{static_cast<std::uint64_t>(value)};
}

/**
 * @brief Logs decimal numbers in binary format.
 *
 * Negatives are represented in 2's complement. The number of represented digits depends on the
 * overloaded parameter type length.
 *
 * @code
 * LogInfo() << "This is some number in bin:" << BinFormat(42);
 * LogInfo() << "This is some negative number in bin:" << BinFormat(-42);
 * @endcode
 *
 * @param[in] value Decimal number to be represented in 8 digits
 * @return          @c LogBin8 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00030}
 */
constexpr LogBin8 BinFormat(std::uint8_t value) noexcept {
    return LogBin8{value};
}

/**
 * @brief Same as @c BinFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 8 digits
 * @return          @c LogBin8 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00031}
 */
constexpr LogBin8 BinFormat(std::int8_t value) noexcept {
    return LogBin8{static_cast<std::uint8_t>(value)};
}

/**
 * @brief Same as @c BinFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 16 digits
 * @return          @c LogBin16 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00032}
 */
constexpr LogBin16 BinFormat(std::uint16_t value) noexcept {
    return LogBin16{value};
}

/**
 * @brief Same as @c BinFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 16 digits
 * @return          @c LogBin16 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00033}
 */
constexpr LogBin16 BinFormat(std::int16_t value) noexcept {
    return LogBin16{static_cast<std::uint16_t>(value)};
}

/**
 * @brief Same as @c BinFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 32 digits
 * @return          @c LogBin32 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00034}
 */
constexpr LogBin32 BinFormat(std::uint32_t value) noexcept {
    return LogBin32{value};
}

/**
 * @brief Same as @c BinFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 32 digits
 * @return          @c LogBin32 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00035}
 */
constexpr LogBin32 BinFormat(std::int32_t value) noexcept {
    return LogBin32{static_cast<std::uint32_t>(value)};
}

/**
 * @brief Same as @c BinFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 64 digits
 * @return          @c LogBin64 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00036}
 */
constexpr LogBin64 BinFormat(std::uint64_t value) noexcept {
    return LogBin64{value};
}

/**
 * @brief Same as @c BinFormat(std::uint8_t value).
 *
 * @param[in] value Decimal number to be represented in 64 digits
 * @return          @c LogBin64 type that has a built-in stream handler
 *
 * @traceid{SWS_LOG_00002}
 * @traceid{SWS_LOG_00017}
 * @traceid{SWS_LOG_00037}
 */
constexpr LogBin64 BinFormat(std::int64_t value) noexcept {
    return LogBin64{static_cast<std::uint64_t>(value)};
}

/**
 * @brief             Creates wrapper object with provided name and unit attributes for
 *                    all arithmetic types except bool, including their reference types.
 *
 * @tparam    T       Any arithmetic type except bool
 * @param[in] arg     an argument payload object
 * @param[in] name    an optional "name" attribute for arg
 * @param[in] unit    an optional "unit" attribute for arg
 * @return            a wrapper object holding the supplied arguments
 *
 * @traceid{SWS_LOG_00201}
 */
template <typename T, typename = std::enable_if_t<std::is_arithmetic<std::decay_t<T>>::value &&
                                                  !std::is_same<std::decay_t<T>, bool>::value>>
Argument<T> Arg(T&& arg, const char* name, const char* unit) noexcept {
    return {std::forward<T>(arg), name, unit};
}

/**
 * @brief             Creates wrapper object with provided name attribute for
 *                    all arithmetic types including their reference types,
 *                    types convertible to ara::core::StringView
 *                    and types convertible to ara::core::Span.
 *
 * @tparam    T       Any arithmetic type or ara::core::StringView or ara::core::Span<Byte> type
 * @param[in] arg     an argument payload object
 * @param[in] name    an optional "name" attribute for arg
 * @return            a wrapper object holding the supplied arguments
 *
 * @traceid{SWS_LOG_00201}
 */
template <typename T,
          typename = std::enable_if_t<std::is_arithmetic<std::decay_t<T>>::value ||
                                      std::is_convertible<T, ara::core::StringView>::value ||
                                      std::is_convertible<T, ara::core::Span<const ara::core::Byte>>::value>>
Argument<T> Arg(T&& arg, const char* name) noexcept {
    return {std::forward<T>(arg), name, nullptr};
}

/**
 * @brief             Creates wrapper object without attributes for
 *                    all arithmetic types including their reference types,
 *                    types convertible to ara::core::StringView
 *                    and types convertible to ara::core::Span.
 *
 * @tparam    T       Any arithmetic type or ara::core::StringView or ara::core::Span<Byte> type
 * @param[in] arg     an argument payload object
 * @return            a wrapper object holding the supplied arguments
 *
 * @traceid{SWS_LOG_00201}
 */
template <typename T,
          typename = std::enable_if_t<std::is_arithmetic<std::decay_t<T>>::value ||
                                      std::is_convertible<T, ara::core::StringView>::value ||
                                      std::is_convertible<T, ara::core::Span<const ara::core::Byte>>::value>>
Argument<T> Arg(T&& arg) noexcept {
    return {std::forward<T>(arg), nullptr, nullptr};
}

/**
 * Fetches the connection state from the DLT back-end of a possibly available remote client.
 *
 * @returns The current client state
 *
 */
ClientState remoteClientState() noexcept;

} /* namespace log */
} /* namespace ara */

#endif  // ARA_LOG_LOGGER_H_
