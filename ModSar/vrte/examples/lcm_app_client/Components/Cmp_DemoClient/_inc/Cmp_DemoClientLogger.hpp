//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      stmdemoclientlogger.hpp
/// @brief     use as a wrapper for logging
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#ifndef DEMOCLIENTAPPLOGGER_HPP_INCLUDED
#define DEMOCLIENTAPPLOGGER_HPP_INCLUDED

#include <memory>
#include <sstream>
#include <string>

#define WITH_ARA_LOG  1

#ifdef WITH_ARA_LOG
#include "ara/log/logger.h"
#else
#include <iostream>
#include <mutex>
static std::mutex m_logger_mutex;
#endif

enum EDemoClientAppLogLevel
{
    LL_FATAL   = 0,
    LL_ERROR   = 1,
    LL_WARN    = 2,
    LL_INFO    = 3,
    LL_DEBUG   = 4,
    LL_VERBOSE = 5
};

#define DEMO_SERVER_APP_FATAL(...)                                                                                     \
    bosch::vrte::stm::democlient::CDemoClientAppLogger::vLog(EDemoClientAppLogLevel::LL_FATAL, __FILE__, __LINE__,     \
                                                             __VA_ARGS__)
#define DEMO_SERVER_APP_ERROR(...)                                                                                     \
    bosch::vrte::stm::democlient::CDemoClientAppLogger::vLog(EDemoClientAppLogLevel::LL_ERROR, __FILE__, __LINE__,     \
                                                             __VA_ARGS__)
#define DEMO_SERVER_APP_WARN(...)                                                                                      \
    bosch::vrte::stm::democlient::CDemoClientAppLogger::vLog(EDemoClientAppLogLevel::LL_WARN, __FILE__, __LINE__,      \
                                                             __VA_ARGS__)
#define DEMO_SERVER_APP_INFO(...)                                                                                      \
    bosch::vrte::stm::democlient::CDemoClientAppLogger::vLog(EDemoClientAppLogLevel::LL_INFO, __FILE__, __LINE__,      \
                                                             __VA_ARGS__)
#define DEMO_CLIENT_APP_DEBUG(...)                                                                                     \
    bosch::vrte::stm::democlient::CDemoClientAppLogger::vLog(EDemoClientAppLogLevel::LL_DEBUG, __FILE__, __LINE__,     \
                                                             __VA_ARGS__)
#define DEMO_SERVER_APP_VERBOSE(...)                                                                                   \
    bosch::vrte::stm::democlient::CDemoClientAppLogger::vLog(EDemoClientAppLogLevel::LL_VERBOSE, __FILE__, __LINE__,   \
                                                             __VA_ARGS__)

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

class CDemoClientAppLogger
{
public:
    virtual ~CDemoClientAppLogger() = default;
    // no copy and move
    CDemoClientAppLogger(const CDemoClientAppLogger& other) = delete;
    CDemoClientAppLogger& operator=(const CDemoClientAppLogger& other) = delete;
    CDemoClientAppLogger(CDemoClientAppLogger&& other)                 = delete;
    CDemoClientAppLogger& operator=(CDemoClientAppLogger&& other) = delete;
    static void           setAppId(std::string f_appId);

    template <typename... LogEntries>
    static void vLogPreprocess(std::stringstream& f_ss, std::string f_filename, int f_lineno, LogEntries... f_entries)
    {
        std::string filename = vParseFileName(f_filename);
        vLogInternal(f_ss, f_entries...);
        f_ss << " [ " << filename << ":" << f_lineno << " ]";
    }

#ifdef WITH_ARA_LOG
    static ara::log::Logger& getLogger()
    {
        static ara::log::Logger& m_logger{ara::log::CreateLogger("DEMS", "This is default context")};
        return m_logger;
    }

    template <typename... LogEntries>
    static void vLog(EDemoClientAppLogLevel f_loglevel, std::string f_filename, int f_lineno, LogEntries... f_entries)
    {
        ara::log::Logger& m_logger = getLogger();
        std::stringstream strbuffer;
        vLogPreprocess(strbuffer, f_filename, f_lineno, f_entries...);
        switch (f_loglevel)
        {
        case EDemoClientAppLogLevel::LL_FATAL:
            m_logger.LogFatal() << strbuffer.str();
            break;
        case EDemoClientAppLogLevel::LL_ERROR:
            m_logger.LogError() << strbuffer.str();
            break;
        case EDemoClientAppLogLevel::LL_WARN:
            m_logger.LogWarn() << strbuffer.str();
            break;
        case EDemoClientAppLogLevel::LL_INFO:
            m_logger.LogInfo() << strbuffer.str();
            break;
        case EDemoClientAppLogLevel::LL_DEBUG:
            m_logger.LogDebug() << strbuffer.str();
            break;
        case EDemoClientAppLogLevel::LL_VERBOSE:
            m_logger.LogVerbose() << strbuffer.str();
            break;
        default:
            break;
        }
    };
#else
    template <typename... LogEntries>
    static void vLog(EDemoClientAppLogLevel f_loglevel, std::string f_filename, int f_lineno, LogEntries... f_entries)
    {
        std::stringstream strbuffer;
        vLogPreprocess(strbuffer, f_filename, f_lineno, f_entries...);
        {
            std::lock_guard<std::mutex> lock(m_logger_mutex);
            std::cout << LogLeveltoString(f_loglevel) << strbuffer.str() << std::endl;
        }
    }
#endif

private:
    static void vLogInternal(std::stringstream& f_buffer)
    {
        (void)f_buffer;
    };
    template <typename LogEntry, typename... MoreLogEntries>
    static void vLogInternal(std::stringstream& f_buffer, LogEntry f_entry, MoreLogEntries... f_entries)
    {
        f_buffer << f_entry;
        vLogInternal(f_buffer, f_entries...);
    };
    static std::string vParseFileName(std::string f_filePath);
    static std::string LogLeveltoString(EDemoClientAppLogLevel f_loglevel);
};
}  // namespace democlient
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // DEMOCLIENTAPPLOGGER_HPP_INCLUDED
