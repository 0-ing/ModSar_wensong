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

#include "ucm/mock/sequence.h"
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
    : virtual protected ucm::mock::Sequence
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
    explicit Logger() { pop<void>(); }

    explicit Logger(const Context& context)
	    : context_(context)
	{
		pop<void>();
	}

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) noexcept = default;
    Logger& operator=(Logger&&) = default;

    ~Logger() = default;

    static void append_writer(std::unique_ptr<Writer>&&) { pop<void>(); }

    static void reset_writers() { pop<void>(); }


    template<class... Rest> static Stream
    sverbose(utl::source_location = utl::source_location::current(),
             Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest> static Stream
    sdebug(utl::source_location = utl::source_location::current(),
           Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest> static Stream
    sinfo(utl::source_location = utl::source_location::current(),
          Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest> static Stream
    swarning(utl::source_location = utl::source_location::current(),
             Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest> static Stream
    serror(utl::source_location = utl::source_location::current(),
           Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest> static Stream
    sfatal(utl::source_location = utl::source_location::current(),
           Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }


    Stream operator()() noexcept { return pop<Stream&&>(); }

    template<class... Rest> Stream
    operator()(utl::source_location = utl::source_location::current(),
               Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest>
    Stream verbose(utl::source_location = utl::source_location::current(),
                   Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest>
    Stream debug(utl::source_location = utl::source_location::current(),
                 Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest>
    Stream info(utl::source_location = utl::source_location::current(),
                Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest>
    Stream warning(utl::source_location = utl::source_location::current(),
                   Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest>
    Stream error(utl::source_location = utl::source_location::current(),
                 Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    template<class... Rest>
    Stream fatal(utl::source_location = utl::source_location::current(),
                 Rest&&... rest) noexcept
    {
        return pop<Stream&&>();
    }

    void loglevel(const Writer::level_type&) noexcept { pop<void>(); }

private:
    Context context_{};
    static std::vector<std::unique_ptr<Writer>> writers_;
    thread_local static std::ostream ostream_;
    thread_local static StreamBuff stream_buffer_;

    static Stream create_stream() noexcept { return pop<Stream&&>(); }

    static Stream create_stream(const ara::ARATypes::LogLevelType&) noexcept { return pop<Stream&&>(); }

    static Stream create_stream(const Context&,
                                const ara::ARATypes::LogLevelType&) noexcept { return pop<Stream&&>(); }
};

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_LOGGER_H_
