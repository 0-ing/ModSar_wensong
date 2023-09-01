//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2020-2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file ILogger.h
/// @brief This file contains the interface definition of Logger
///
/// @attention Due to testability reasons the ILogger is introduced.
/// Such code is NOT meant to be used or referred to by a user directly,
/// and is subject to CHANGE WITHOUT NOTICE.
/// Therefore DO NOT USE any implementation details outside of dev-aap-ara-log!
//==============================================================================

#ifndef BOSCH_VRTE_LOG_ILOGGER_H_
#define BOSCH_VRTE_LOG_ILOGGER_H_

#include <atomic>
#include <string>

#include "ara/log/common.h"
#include "ara/log/log_stream.h"

namespace bosch {
namespace vrte {
namespace log {

class ILogChannel;

/**
 * @ingroup logger
 * @class ILogger
 *
 * @brief Abstract base class for Logger. Is to be used exclusively for unit testing pourposes.
 */
class ILogger {
   public:
    virtual ~ILogger() {
    }

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c LogStream object of Fatal severity.
     */
    virtual ara::log::LogStream LogFatal() = 0;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c LogStream object of Error severity.
     */
    virtual ara::log::LogStream LogError() = 0;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c ara::log::LogStream object of Warn severity.
     */
    virtual ara::log::LogStream LogWarn() = 0;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c ara::log::LogStream object of Info severity.
     */
    virtual ara::log::LogStream LogInfo() = 0;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c ara::log::LogStream object of Debug severity.
     */
    virtual ara::log::LogStream LogDebug() = 0;

    /**
     * @brief Same as @c Logger::LogFatal().
     * @return  @c ara::log::LogStream object of Verbose severity.
     */
    virtual ara::log::LogStream LogVerbose() = 0;

    /**
     * @brief Check current configured log reporting level.
     *
     * Applications may want to check the actual configured reporting log level of certain loggers
     * before doing log data preparation that is runtime intensive.
     *
     * @param[in] logLevel  The to be checked log level.
     * @return              True if desired log level satisfies the configured reporting level.
     */
    virtual bool IsLogEnabled(ara::log::LogLevel logLevel) const = 0;

    /**
     * @brief Return the current active backend context
     *
     * @note The only current supported backend is DLT, but the direct access and implementation
     * should be hidden from the class consumer.
     */
    virtual void* GetContext() = 0;

    /**
     * @brief Returns the context ID.
     * @return  The _up to four-character_ ID
     */
    virtual std::string GetId() const = 0;
};

} /* namespace log */
} /* namespace vrte */
} /* namespace bosch */

#endif  // BOSCH_VRTE_LOG_ILOGGER_H_
