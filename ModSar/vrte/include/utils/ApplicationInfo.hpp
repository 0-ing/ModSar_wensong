//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ApplicationInfo.hpp
/// @brief     class to hold Type of application
/// @copyright Robert Bosch GmbH  2018
/// @author    Arnaud Riess

#ifndef UTILS_APPLICATIONINFO_HPP_INCLUDED
#define UTILS_APPLICATIONINFO_HPP_INCLUDED


namespace exm
{
namespace utils
{

    /// @brief Class to hold application type information
    class ApplicationInfo
    {
        public:
            uint32_t start_timeout; ///< @brief Start timeout in ms
            uint32_t stop_timeout;  ///< @brief Stop timeout in ms
            bool isOneShot;         ///< @brief Set if the application is one shot (will terminate by itself).
            bool isReporting;       ///< @brief Set if the application is reporting its state to the execution manager.
            uint32_t executionError; ///< process execution error
            uint32_t numberOfRestartAttempts;

            ApplicationInfo():
                start_timeout(0U),
                stop_timeout(0U),
                isOneShot(false),
                isReporting(true),
                executionError(1U)
            {}
    };

}/* namespace utils */
}/* namespace exm */
#endif


