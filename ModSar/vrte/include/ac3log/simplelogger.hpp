// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef IOX_UTILS_AC3LOG_SIMPLELOGGER_HPP
#define IOX_UTILS_AC3LOG_SIMPLELOGGER_HPP

#include "ara/core/initialization.h"
#include "stdout_forwarder.hpp"

#include <cstdint>
#include <cstring>

// ======== this is the ac3log interface ========

#define L_ERR 0u
#define L_MSG 1u
#define L_WARN 10u
#define L_INFO 20u
#define L_DEBUG 99u

static void stdout_log(const uint8_t debuglevel, char* msg)
{
    switch (debuglevel)
    {
    case L_ERR:
        log_error() << msg << std::endl;
        break;
    case L_MSG:
        log_info() << msg << std::endl;
        break;
    case L_WARN:
        log_warn() << msg << std::endl;
        break;
    case L_INFO:
        log_info() << msg << std::endl;
        break;
    case L_DEBUG:
        log_debug() << msg << std::endl;
        break;
    default:
        log_fatal() << msg << std::endl;
        break;
    }
}

extern uint8_t debuglevel;

static inline void log_init()
{
    // TODO: Quick fix, should be called in the ITs explicitly instead of here
    ara::core::Initialize();
}

inline void X_PRINTF(const uint8_t debuglevel, const char* msg)
{
    char buffer[2048];
    strncpy(buffer, msg, 2047u);

    stdout_log(debuglevel, buffer);
}

template<typename... Args>
void X_PRINTF(const uint8_t debuglevel, const char* msg, Args&&... args)
{
    char buffer[2048];
    std::snprintf(buffer, 2047u, msg, std::forward<Args>(args)...);

    stdout_log(debuglevel, buffer);
}

template<typename... Args>
void ERR_PRINTF(const char* msg, Args&&... args)
{
    X_PRINTF(L_ERR, msg, std::forward<Args>(args)...);
}

template<typename... Args>
void MSG_PRINTF(const char* msg, Args&&... args)
{
    X_PRINTF(L_MSG, msg, std::forward<Args>(args)...);
}

template<typename... Args>
void WARN_PRINTF(const char* msg, Args&&... args)
{
    X_PRINTF(L_WARN, msg, std::forward<Args>(args)...);
}

template<typename... Args>
void INFO_PRINTF(const char* msg, Args&&... args)
{
    X_PRINTF(L_INFO, msg, std::forward<Args>(args)...);
}

template<typename... Args>
void DEBUG_PRINTF(const char* msg, Args&&... args)
{
    X_PRINTF(L_DEBUG, msg, std::forward<Args>(args)...);
}

inline void LOG_X(const uint8_t debuglevel, const char* msg)
{
    X_PRINTF(debuglevel, msg);
}

inline void LOG_ERR(const char* msg)
{
    LOG_X(L_ERR, msg);
}

inline void LOG_MSG(const char* msg)
{
    LOG_X(L_MSG, msg);
}

inline void LOG_WARN(const char* msg)
{
    LOG_X(L_WARN, msg);
}

inline void LOG_INFO(const char* msg)
{
    LOG_X(L_INFO, msg);
}

inline void LOG_DEBUG(const char* msg)
{
    LOG_X(L_DEBUG, msg);
}

#endif // IOX_UTILS_AC3LOG_SIMPLELOGGER_HPP
