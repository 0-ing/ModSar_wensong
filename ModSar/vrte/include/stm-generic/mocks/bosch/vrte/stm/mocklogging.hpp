//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      tests/VRTE_UT/mocks/include/bosch/vrte/stm/mocklogging.hpp
/// @brief     Logging Mock class.
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_MOCKLOGGING_HPP_INCLUDED
#define BOSCH_VRTE_STM_MOCKLOGGING_HPP_INCLUDED

#include "bosch/vrte/stm/logging.hpp"

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace bosch
{
namespace vrte
{
namespace stm
{

/// @brief Capture CLogger traces.
/// CLogger is a singleton and cannot be mocked. To still be able to check
/// traces in unit tests this helper class will temporarily replace the
/// logging callback method.
class CCaptureTraces
{
public:
    /// @brief Constructor
    /// Will replace the CLogger callback.
    CCaptureTraces()
    {
        m_oldcallback    = CLogger::GetCallback();
        m_oldMinLogLevel = CLogger::GetMinLogLevel();
        CLogger::Init(std::bind(&CCaptureTraces::callback, this, std::placeholders::_1, std::placeholders::_2,
                                std::placeholders::_3),
                      CLogger::LogLevel::Verbose);
    }

    /// @brief Destructor
    /// Restores the previous CLogger callback.
    ~CCaptureTraces()
    {
        // Restore logger
        CLogger::Init(m_oldcallback, m_oldMinLogLevel);
    }

    /// @brief Check if a trace was generated with given log level containing given message.
    /// @param f_level      Log level
    /// @param f_message    Substring that a match must contain.
    /// @return             true if at least one message with given level contains given message.
    bool contains(CLogger::LogLevel f_level, const std::string& f_message) const
    {
        return m_traces.end() !=
               std::find_if(m_traces.begin(), m_traces.end(),
                            [f_level, f_message](const std::pair<CLogger::LogLevel, std::string>& f_trace) {
                                return f_trace.first == f_level && f_trace.second.find(f_message) != std::string::npos;
                            });
    }

private:
    /// @brief Callback collecting all traces.
    /// @param f_level      Trace log level.
    /// @param f_message    Trace log message.
    void callback(CLogger::Context, CLogger::LogLevel f_level, const std::string& f_message)
    {
        m_traces.push_back({f_level, f_message});
    }

    CLogger::callback_t                                    m_oldcallback;
    CLogger::LogLevel                                      m_oldMinLogLevel;
    std::vector<std::pair<CLogger::LogLevel, std::string>> m_traces;
};

}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_MOCKLOGGING_HPP_INCLUDED
