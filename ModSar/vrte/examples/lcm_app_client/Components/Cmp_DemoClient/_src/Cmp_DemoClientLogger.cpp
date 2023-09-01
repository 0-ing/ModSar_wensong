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
/// @file      stmexampleapplogger.cpp
/// @brief     use as a wrapper for logging
/// @copyright Robert Bosch GmbH 2019
/// @author    VRTE StM Team
//=============================================================================

#include "Cmp_DemoClientLogger.hpp"

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace democlient
{

std::string m_appId;

std::string CDemoClientAppLogger::vParseFileName(std::string f_filePath)
{
    std::size_t found = f_filePath.find_last_of("/\\");
    return f_filePath.substr(found + 1);
}

void CDemoClientAppLogger::setAppId(std::string f_appId)
{
    m_appId = f_appId;
}

std::string CDemoClientAppLogger::LogLeveltoString(EDemoClientAppLogLevel f_loglevel)
{
    std::string strLogLevel;
    switch (f_loglevel)
    {
    case EDemoClientAppLogLevel::LL_FATAL:
        strLogLevel = " [ FATAL ] ";
        break;
    case EDemoClientAppLogLevel::LL_ERROR:
        strLogLevel = " [ ERROR ] ";
        break;
    case EDemoClientAppLogLevel::LL_WARN:
        strLogLevel = " [ WARN ] ";
        break;
    case EDemoClientAppLogLevel::LL_INFO:
        strLogLevel = " [ INFO ] ";
        break;
    case EDemoClientAppLogLevel::LL_DEBUG:
        strLogLevel = " [ DEBUG ] ";
        break;
    case EDemoClientAppLogLevel::LL_VERBOSE:
        strLogLevel = " [ VERBOSE ] ";
        break;
    default:
        break;
    }
    return m_appId + ": " + strLogLevel;
}

}  // namespace exampleapp
}  // namespace stm
}  // namespace vrte
}  // namespace bosch
