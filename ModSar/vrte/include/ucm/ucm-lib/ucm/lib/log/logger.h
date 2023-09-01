//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/logger.h
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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error.h"
#include "ucm/lib/log/stream.h"
#include "ucm/lib/ara/ara_types.h"
#include "ucm/lib/utl/source_location.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace log   {

class Logger final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_LIB_UTL_Logger, Simple);
#endif

    static void print(Stream& stream) noexcept
    {
        stream << std::dec;
    }

    template<class First, class... Rest>
    static void print(Stream& stream, First first, Rest&&... rest) noexcept
    {
        stream << first;
        print(stream, std::forward<Rest>(rest)...);
    }

public:
    using Level = ara::ARATypes::LogLevelType;

    static void init() noexcept;

    static void fini() noexcept;

    static Logger* tls_tlogger() noexcept;

    explicit Logger();

    explicit Logger(const Context& context);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) noexcept = default;
    Logger& operator=(Logger&&) = default;

    ~Logger() = default;

    static void append_writer(std::unique_ptr<Writer>&&);

    static void reset_writers();


    template<class... Rest> static Stream
    sverbose(utl::source_location sloc = utl::source_location::current(),
             Rest&&... rest) noexcept
    {
        Stream stream = create_stream(ara::ARATypes::LogLevelType::kVerbose);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest> static Stream
    sdebug(utl::source_location sloc = utl::source_location::current(),
           Rest&&... rest) noexcept
    {
        Stream stream = create_stream(ara::ARATypes::LogLevelType::kDebug);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest> static Stream
    sinfo(utl::source_location sloc = utl::source_location::current(),
          Rest&&... rest) noexcept
    {
        Stream stream = create_stream(ara::ARATypes::LogLevelType::kInfo);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest> static Stream
    swarning(utl::source_location sloc = utl::source_location::current(),
             Rest&&... rest) noexcept
    {
        Stream stream = create_stream(ara::ARATypes::LogLevelType::kWarning);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest> static Stream
    serror(utl::source_location sloc = utl::source_location::current(),
           Rest&&... rest) noexcept
    {
        Stream stream = create_stream(ara::ARATypes::LogLevelType::kError);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest> static Stream
    sfatal(utl::source_location sloc = utl::source_location::current(),
           Rest&&... rest) noexcept
    {
        Stream stream = create_stream(ara::ARATypes::LogLevelType::kFatal);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }


    Stream operator()() noexcept;

    template<class... Rest> Stream
    operator()(utl::source_location sloc = utl::source_location::current(),
               Rest&&... rest) noexcept
    {
        Stream stream = create_stream();
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest>
    Stream verbose(utl::source_location sloc = utl::source_location::current(),
                   Rest&&... rest) noexcept
    {
        Stream stream =
                create_stream(context_, ara::ARATypes::LogLevelType::kVerbose);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest>
    Stream debug(utl::source_location sloc = utl::source_location::current(),
                 Rest&&... rest) noexcept
    {
        Stream stream =
                create_stream(context_, ara::ARATypes::LogLevelType::kDebug);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest>
    Stream info(utl::source_location sloc = utl::source_location::current(),
                Rest&&... rest) noexcept
    {
        Stream stream =
                create_stream(context_, ara::ARATypes::LogLevelType::kInfo);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest>
    Stream warning(utl::source_location sloc = utl::source_location::current(),
                   Rest&&... rest) noexcept
    {
        Stream stream =
                create_stream(context_, ara::ARATypes::LogLevelType::kWarning);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest>
    Stream error(utl::source_location sloc = utl::source_location::current(),
                 Rest&&... rest) noexcept
    {
        Stream stream =
                create_stream(context_, ara::ARATypes::LogLevelType::kError);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    template<class... Rest>
    Stream fatal(utl::source_location sloc = utl::source_location::current(),
                 Rest&&... rest) noexcept
    {
        Stream stream =
                create_stream(context_, ara::ARATypes::LogLevelType::kFatal);
        stream << sloc;
        print(stream, std::forward<Rest>(rest)...);
        return stream;
    }

    void loglevel(const Writer::level_type&) noexcept;

    static Logger& default_logger() noexcept;

    Stream ucm_error(const Error&);

private:
    Context context_{};
    static std::vector<std::unique_ptr<Writer>> writers_;

    Stream ucm_error(const Level&, const Error&);

    static Stream create_stream() noexcept;

    static Stream create_stream(const ara::ARATypes::LogLevelType&) noexcept;

    static Stream create_stream(const Context&,
                                const ara::ARATypes::LogLevelType&) noexcept;
};

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_LOGGER_H_
