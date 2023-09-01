//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/ref_logger.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_LOG__REF_LOGGER__H_
#define UCM_AAP_LIBRARY__UCM_LIB_LOG__REF_LOGGER__H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/log/logger.h"
#include "ucm/lib/log/null_stream.h"
#include "ucm/lib/utl/source_location.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace log   {

class RefLogger
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_log__RefLogger, Simple);
#endif
public:
    explicit RefLogger(Logger&) noexcept
    {
    }

    RefLogger(RefLogger     &&) = default;
    RefLogger(RefLogger const&) = default;

    RefLogger& operator=(RefLogger     &&) = default;
    RefLogger& operator=(RefLogger const&) = default;

    virtual ~RefLogger() = default;

    template<class... Rest> Stream
    log_verbose(utl::source_location sloc = utl::source_location::current(),
                Rest&&... rest) noexcept
    {
        return Stream();
    }

    template<class... Rest> Stream
    log_debug(utl::source_location sloc = utl::source_location::current(),
              Rest&&... rest) noexcept
    {
        return Stream();
    }

    template<class... Rest> Stream
    log_info(utl::source_location sloc = utl::source_location::current(),
             Rest&&... rest) noexcept
    {
        return Stream();
    }

    template<class... Rest> Stream
    log_warning(utl::source_location sloc = utl::source_location::current(),
                Rest&&... rest) noexcept
    {
        return Stream();
    }

    template<class... Rest> Stream
    log_error(utl::source_location sloc = utl::source_location::current(),
              Rest&&... rest) noexcept
    {
        return Stream();
    }

    template<class... Rest> Stream
    log_fatal(utl::source_location sloc = utl::source_location::current(),
              Rest&&... rest) noexcept
    {
        return Stream();
    }
};

}    // namespace log
}    // namespace lib

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_verbose(bosch::vrte::ucm::lib::utl::source_location sloc
                = bosch::vrte::ucm::lib::utl::source_location::current(),
            Rest&&... rest) noexcept
{
    (void)sloc;
    return bosch::vrte::ucm::lib::log::Stream();
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_debug(bosch::vrte::ucm::lib::utl::source_location sloc
              = bosch::vrte::ucm::lib::utl::source_location::current(),
          Rest&&... rest) noexcept
{
    (void)sloc;
    return bosch::vrte::ucm::lib::log::Stream{};
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_info(bosch::vrte::ucm::lib::utl::source_location sloc
             = bosch::vrte::ucm::lib::utl::source_location::current(),
         Rest&&... rest) noexcept
{
    (void)sloc;
    return bosch::vrte::ucm::lib::log::Stream();
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_warning(bosch::vrte::ucm::lib::utl::source_location sloc
                = bosch::vrte::ucm::lib::utl::source_location::current(),
            Rest&&... rest) noexcept
{
    (void)sloc;
    return bosch::vrte::ucm::lib::log::Stream();
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_error(bosch::vrte::ucm::lib::utl::source_location sloc
              = bosch::vrte::ucm::lib::utl::source_location::current(),
          Rest&&... rest) noexcept
{
    (void)sloc;
    return bosch::vrte::ucm::lib::log::Stream();
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_fatal(bosch::vrte::ucm::lib::utl::source_location sloc
              = bosch::vrte::ucm::lib::utl::source_location::current(),
          Rest&&... rest) noexcept
{
    (void)sloc;
    return bosch::vrte::ucm::lib::log::Stream();
}

template<class... Rest> bosch::vrte::ucm::lib::log::NullStream
log_print(Rest&&...) noexcept
{
    return bosch::vrte::ucm::lib::log::NullStream{};
}

inline bosch::vrte::ucm::lib::log::Stream ucm_log_error(const Error&) noexcept
{
    return bosch::vrte::ucm::lib::log::Stream();
}


}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_LOG__REF_LOGGER__H_
