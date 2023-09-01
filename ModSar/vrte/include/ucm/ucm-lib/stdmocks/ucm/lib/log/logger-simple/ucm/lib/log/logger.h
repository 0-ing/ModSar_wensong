//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         mock/ucm/lib/log/logger.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_LOG_LOGGER_H_
#define UCM_AAP_LIBRARY_LIB_LOG_LOGGER_H_

#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <cstddef>
#include <iomanip>
#include <iostream>

#include "ucm/lib/log/stream.h"
#include "ucm/lib/ara/ara_types.h"


namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class Logger final
{
public:
    explicit Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) noexcept = default;
    Logger& operator=(Logger&&) = default;

    ~Logger() = default;

    static void reset_writers() {}

    template<class... Rest>
    static Stream sverbose(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    static Stream sdebug(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    static Stream sinfo(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    static Stream swarning(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    static Stream serror(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    static Stream sfatal(Rest&&...) noexcept
    {
        return Stream();
    }


    Stream operator()() noexcept;

    template<class... Rest>
    Stream operator()(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    Stream verbose(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    Stream debug(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    Stream info(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    Stream warning(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    Stream error(Rest&&...) noexcept
    {
        return Stream();
    }

    template<class... Rest>
    Stream fatal(Rest&&...) noexcept
    {
        return Stream();
    }
};

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_LOGGER_H_
