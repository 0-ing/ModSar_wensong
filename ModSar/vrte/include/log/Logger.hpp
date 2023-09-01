//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      AraLog.hpp
/// @brief     Declaration/Definition of ARALog
/// @author    Jyothi Kuntegowda
//=============================================================================
#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include "log/ILog.hpp"

namespace ara
{
namespace log
{
class Logger;
}
}

namespace exm
{
namespace log
{

/// @brief Class for the Ara logging
class Logger : public ILog
{
public:
    /// @brief Destructor.
   virtual  ~Logger();

    /// @brief prevent copy construction
    Logger(const Logger &other) = delete;

    /// @brief prevent copy assignment
    Logger& operator=(const Logger& other) = delete;

    /// @brief Constructor.
    /// @param[in] istatDataAccessor interface to MFE
    /// @param[in] translator_  interface to function group accessor
    Logger();

    void Log(const Severity severity, const MessageString& message) override; //PRQA S 2502 #the declaration in Debug.hpp and here are slightly different as the number of args is different

    /// @brief Locks the logging internal mutex
    StdReturnType Lock() override;

    /// @brief Unlocks the logging internal mutex
    StdReturnType Unlock() override;

private:
    ara::log::Logger* aralogger = nullptr;
};

}  // namespace log
}  // namespace exm

#endif // ARALOG_HPP_INCLUDED

