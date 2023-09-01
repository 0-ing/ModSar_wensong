//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file       Debug.hpp
/// @brief      Debug framework: set of macros that can be used for internal debugging.
/// @copyright  Robert Bosch GmbH 2017
/// @author


#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#include "log/Log.hpp"

#define DEBUG_LEVEL_NONE    (-1)///<    DEBUG_LEVEL_NONE : Debug disabled
#define DEBUG_LEVEL_DEBUG   (0)///<     DEBUG_LEVEL_DEBUG : debug information
#define DEBUG_LEVEL_ERRORS  (1)///<    DEBUG_LEVEL_ERRORS : Debug level show errors
#define DEBUG_LEVEL_WARNING (2)///<    DEBUG_LEVEL_WARNING : debug level show warnings and errors
#define DEBUG_LEVEL_INFO    (3)///<    DEBUG_LEVEL_INFO : debug level all above

/// @brief    DEBUG_LEVEL : debug level information
#ifndef DEBUG_LEVEL
    #define DEBUG_LEVEL DEBUG_LEVEL_NONE
#endif

/// @brief    DEBUG_DEBUG : Macro to collect debug information in given format
#if (DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG)
    #define DEBUG_DEBUG(format) exm::log::Log(exm::Severity::DEBUG, format)
    #define DEBUG_DEBUG_F(format, ...) exm::log::Log(exm::Severity::DEBUG, format, ##__VA_ARGS__)
#else
    #define DEBUG_DEBUG(format)
    #define DEBUG_DEBUG_F(format, ...)
#endif

/// @brief    DEBUG_ERROR : A critical error
#if (DEBUG_LEVEL >= DEBUG_LEVEL_ERRORS)
    #define DEBUG_ERROR(format) exm::log::Log(exm::Severity::ERROR, format)
    #define DEBUG_ERROR_F(format, ...) exm::log::Log(exm::Severity::ERROR, format, ##__VA_ARGS__)
#else
    #define DEBUG_ERROR(format)
    #define DEBUG_ERROR_F(format, ...)
#endif

/// @brief    DEBUG_WARNING : A non-critical error, may  be useful to debug
#if (DEBUG_LEVEL >= DEBUG_LEVEL_WARNING)
    #define DEBUG_WARNING(format) exm::log::Log(exm::Severity::WARN, format)
    #define DEBUG_WARNING_F(format, ...) exm::log::Log(exm::Severity::WARN, format, ##__VA_ARGS__)
#else
    #define DEBUG_WARNING(format)
    #define DEBUG_WARNING_F(format, ...)
#endif

/// @brief    DEBUG_INFO : Macro to collect debug information in given format
#if (DEBUG_LEVEL >= DEBUG_LEVEL_INFO)
    #define DEBUG_INFO(format) exm::log::Log(exm::Severity::INFO, format)
    #define DEBUG_INFO_F(format, ...) exm::log::Log(exm::Severity::INFO, format, ##__VA_ARGS__)
#else
    #define DEBUG_INFO(format)
    #define DEBUG_INFO_F(format, ...)
#endif

#endif // DEBUG_HPP_INCLUDED

