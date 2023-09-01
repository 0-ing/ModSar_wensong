//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      ILog.hpp
/// @brief     Declaration/Definition of ILog
/// @author    Jyothi Kuntegowda
//=============================================================================

#ifndef ILOG_HPP_INCLUDED
#define ILOG_HPP_INCLUDED

#include "log/SeverityLevel.hpp"
#include "utils/AppInstId.hpp"
#include "utils/FuncGroupId.hpp"
#include "utils/FuncGroupStateId.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/String.hpp"

#include "utils/c/stdarg.hpp"     //wrapper to prevent direct inclusion of libc headers

// required interfaces
#include "log/ILogStaticDataAccessor.hpp"
#include "fga/IFuncGroupUniqueIdTranslator.hpp"

namespace exm
{
namespace log
{

typedef utils::String<512U> MessageString;

/// @brief Class for the Log Interface
class ILog
{
public:
    /// @brief destructor
    virtual ~ILog()
    {
    }

    /// @brief Generic Logger interface function.
    /// @param[in] severity          Severity level of  error.
    /// @param[in] message           Formated message.
    virtual void Log(const Severity severity, const MessageString& message) = 0;

    /// @brief Locks the logging internal mutex
    virtual StdReturnType Lock() = 0;

    /// @brief Unlocks the logging internal mutex
    virtual StdReturnType Unlock() = 0;

    static void SetLogger(log::ILog& logger_, log::ILogStaticDataAccessor &istatDataAccessor_, fga::IFuncGroupUniqueIdTranslator &funcIdtranslator_);

    static void SetLogLevel(const Severity severity);
};

}  // namespace log
}  // namespace exm

#endif //ILOG_HPP_INCLUDED
