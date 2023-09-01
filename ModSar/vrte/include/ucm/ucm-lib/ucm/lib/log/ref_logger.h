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
#ifndef UCM_SECTION_DIAGNOSE
#include "ucm/lib/log/null_stream.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace log   {

/// Sets and maintains in RAII fashion a global and TSD logger for the
/// execution context.
class RefLogger final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_log__RefLogger, Simple);
#endif
public:
    /// Set both of the loggers.
    /// This constructor is supposed to be called only in a single-threaded
    /// runtime environment.
    explicit RefLogger(Logger *global, Logger *thread) noexcept;

    /// Set only the TSD logger.
    explicit RefLogger(Logger *thread) noexcept;

    RefLogger(RefLogger     &&) = default;
    RefLogger(RefLogger const&) = default;

    RefLogger& operator=(RefLogger     &&) = default;
    RefLogger& operator=(RefLogger const&) = default;

    /// Recover the previous pointer values for the global and thread loggers.
    /// The pointer for a logger is recovered only if the affected flag is set.
    ~RefLogger();

    /// Return a Logger pointer to be used for logging.
    /// The selection of a logger is done following the rules:
    /// 1. unless thread_logger_curr_ == nullptr - return it
    /// 2. unless global_logger_curr_ == nullptr - return it
    /// 3. throw std::logic_error if no logger is set
    static Logger* logger() noexcept;

    /// Read accessor for the global logger
    static Logger* global_logger() noexcept;

    /// Read accessor for the thread specific logger
    static Logger* thread_logger() noexcept;

private:
    bool global_affected_;
    bool thread_affected_;
    Logger *global_logger_prev_;
    Logger *thread_logger_prev_;
    static Logger *global_logger_curr_;
    thread_local static Logger *thread_logger_curr_;

    explicit RefLogger(Logger *glogger, bool gflag,
                       Logger *tlogger, bool tflag) noexcept;
};

inline Logger* RefLogger::global_logger() noexcept
{
    return global_logger_curr_;
}

inline Logger* RefLogger::thread_logger() noexcept
{
    return thread_logger_curr_;
}

}    // namespace log
}    // namespace lib

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_verbose(bosch::vrte::ucm::lib::utl::source_location sloc
                = bosch::vrte::ucm::lib::utl::source_location::current(),
            Rest&&... rest) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return RefLogger::logger()->verbose(sloc, std::forward<Rest>(rest)...);
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_debug(bosch::vrte::ucm::lib::utl::source_location sloc
              = bosch::vrte::ucm::lib::utl::source_location::current(),
          Rest&&... rest) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return RefLogger::logger()->debug(sloc, std::forward<Rest>(rest)...);
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_info(bosch::vrte::ucm::lib::utl::source_location sloc
             = bosch::vrte::ucm::lib::utl::source_location::current(),
         Rest&&... rest) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return RefLogger::logger()->info(sloc, std::forward<Rest>(rest)...);
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_warning(bosch::vrte::ucm::lib::utl::source_location sloc
                = bosch::vrte::ucm::lib::utl::source_location::current(),
            Rest&&... rest) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return RefLogger::logger()->warning(sloc, std::forward<Rest>(rest)...);
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_error(bosch::vrte::ucm::lib::utl::source_location sloc
              = bosch::vrte::ucm::lib::utl::source_location::current(),
          Rest&&... rest) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return RefLogger::logger()->error(sloc, std::forward<Rest>(rest)...);
}

template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_fatal(bosch::vrte::ucm::lib::utl::source_location sloc
              = bosch::vrte::ucm::lib::utl::source_location::current(),
          Rest&&... rest) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return RefLogger::logger()->fatal(sloc, std::forward<Rest>(rest)...);
}

#ifdef UCM_SECTION_DIAGNOSE
template<class... Rest> bosch::vrte::ucm::lib::log::Stream
log_print(bosch::vrte::ucm::lib::utl::source_location sloc
              = bosch::vrte::ucm::lib::utl::source_location::current(),
          Rest&&... rest) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return RefLogger::logger()->verbose(sloc, std::forward<Rest>(rest)...);
}
#else
template<class... Rest> bosch::vrte::ucm::lib::log::NullStream
log_print(Rest&&...) noexcept
{
    using namespace bosch::vrte::ucm::lib::log;
    return NullStream{};
}
#endif

lib::log::Stream ucm_log_error(const Error& err) noexcept;

}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_LOG__REF_LOGGER__H_
