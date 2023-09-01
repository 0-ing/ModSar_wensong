//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/logging.hpp
/// @brief     STM wrapper for ara:log and DLT.
///            This wrapper allows us to provide traces that always include
///            filename, line number and function name.
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================
//
// Example usage:
//
// \code
// #define STM_LOG_CONTEXT OSM
// #include "bosch/vrte/stm/logging.hpp"
//
// void foo(uint64_t event) {
//     LOG_WARN() << "This is a warning on event " << strevent(event);
// }
// \endcode
//
// When creating new log traces always answer the following questions:
//
//  1. Does the trace give meaningful information?
//     Example:
//         Bad:     "open() failed"
//         OK:      "open() failed: " << strerror(errno)
//         Good:    "open(" << quote(path) << ") failed: " << strerror(errno)
//                  << ". Maybe the current working dir is not set to base path."
//         Awesome: Give hint based on errno content.
//
//  2. Does the trace use the correct context?
//
//  3. Does the trace use the correct severity?
//     Fatal:   Program terminates right after printing this message.
//     Error:   Program will continue, but not work as expected.
//     Warning: Program will (probably) continue as expected but issue should
//              be reported to dev team.
//     Info:    Shows important status information.
//     Debug:   Debug information for developers.
//     Verbose: Verbose information with insights into the behaviour of the
//              system.
//
//  4. Does removing the trace change control flow?
//     Bad:     LOG_INFO() << set(42)
//     Good:    LOG_INFO() << getConst()
//
//  5. Does the trace expose critical data from security perspective?
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_LOGGING_HPP_INCLUDED
#define BOSCH_VRTE_STM_LOGGING_HPP_INCLUDED

#include <functional>
#include <sstream>
#include <string>

#ifdef STM_LOG_CONTEXT
#define LOG_FATAL                                                                                                      \
    ::bosch::vrte::stm::CLogger(::bosch::vrte::stm::CLogger::LogLevel::Fatal,                                          \
                                ::bosch::vrte::stm::CLogger::Context::STM_LOG_CONTEXT, __FILE__, __LINE__, __func__)   \
        .getStream
#define LOG_ERROR                                                                                                      \
    ::bosch::vrte::stm::CLogger(::bosch::vrte::stm::CLogger::LogLevel::Error,                                          \
                                ::bosch::vrte::stm::CLogger::Context::STM_LOG_CONTEXT, __FILE__, __LINE__, __func__)   \
        .getStream
#define LOG_WARN                                                                                                       \
    ::bosch::vrte::stm::CLogger(::bosch::vrte::stm::CLogger::LogLevel::Warn,                                           \
                                ::bosch::vrte::stm::CLogger::Context::STM_LOG_CONTEXT, __FILE__, __LINE__, __func__)   \
        .getStream
#define LOG_INFO                                                                                                       \
    ::bosch::vrte::stm::CLogger(::bosch::vrte::stm::CLogger::LogLevel::Info,                                           \
                                ::bosch::vrte::stm::CLogger::Context::STM_LOG_CONTEXT, __FILE__, __LINE__, __func__)   \
        .getStream
#define LOG_DEBUG                                                                                                      \
    ::bosch::vrte::stm::CLogger(::bosch::vrte::stm::CLogger::LogLevel::Debug,                                          \
                                ::bosch::vrte::stm::CLogger::Context::STM_LOG_CONTEXT, __FILE__, __LINE__, __func__)   \
        .getStream
#define LOG_VERBOSE                                                                                                    \
    ::bosch::vrte::stm::CLogger(::bosch::vrte::stm::CLogger::LogLevel::Verbose,                                        \
                                ::bosch::vrte::stm::CLogger::Context::STM_LOG_CONTEXT, __FILE__, __LINE__, __func__)   \
        .getStream
#endif

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief Quote given message.
/// @param [in] message     message to quote
/// @return                 "message"
std::string quote(const std::string& message);

/// @brief Logger class for stdout.
///
/// CLogger encapsulates the differences between sending traces to ara:log and sending them to stdout.
class CLogger
{
public:
    /// @brief List of log levels.
    enum class LogLevel
    {
        Off = 0,
        Fatal,
        Error,
        Warn,
        Info,
        Debug,
        Verbose,
        Count
    };

    /// @brief List of STM log contexts.
    /// If a new context is added CLogger::getContext() and the contextNames array
    /// in CLogger() need to be updated.
    enum class Context : uint8_t
    {
        ALL,
        CM,
        EH,
        FGM,
        OSM,
        SM,
        PLG,
        CFG,
        NMS,
        Count
    };

    /// Typedef for callback function syntax.
    typedef std::function<void(Context, LogLevel, const std::string&)> callback_t;

    /// @brief Initialize logging.
    /// Set the callback to which all log messages shall be forwarded.
    /// It is safe to not call Init().
    /// @param f_callback   Callback
    /// @param f_min        Minimum log level. All log messages below f_min will be ignored.
    static void Init(callback_t f_callback, LogLevel f_min = LogLevel::Verbose) noexcept;

    /// @brief Get the current callback.
    /// This method can be used in order to temporary replace the callback method
    /// (e.g. for unit tests).
    static callback_t GetCallback();

    /// @brief Get the current minimum log level.
    /// This method can be used in order to temporary replace the callback method
    /// (e.g. for unit tests).
    static LogLevel GetMinLogLevel();

    /// @brief Constructor
    /// @param f_level      Trace level.
    /// @param f_context    Trace context.
    /// @param f_file       Path to file that raised this trace.
    ///                     Directory will be stripped from the file path.
    /// @param f_line       Line that raised this trace.
    /// @param f_func       Function that raised this trace.
    CLogger(LogLevel f_level, Context f_context, const char* f_file, int f_line, const char* f_func);

    /// @brief Destructor
    virtual ~CLogger();

    /// @brief Get the stream object for appending additional strings to the trace message.
    std::stringstream& getStream();

protected:
    Context           m_context;
    LogLevel          m_level;
    std::stringstream m_stream;
    std::string       m_appendix;
};

/// @brief Callback function that forwards logs to a stream.
/// This function is not automatically installed, but can be used in CLogger::Init().
/// @param f_stream         output stream (e.g. std::cout)
/// @param f_context        log context
/// @param f_level          log level
/// @param f_message        log message
void log_callback_stdout(std::ostream&      f_stream,
                         CLogger::Context   f_context,
                         CLogger::LogLevel  f_level,
                         const std::string& f_message);

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_LOGGING_HPP_INCLUDED
