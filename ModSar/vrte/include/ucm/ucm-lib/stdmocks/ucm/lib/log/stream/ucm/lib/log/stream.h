//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/stream.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_LOG_STREAM_H_
#define UCM_AAP_LIBRARY_LIB_LOG_STREAM_H_

#include <vector>
#include <atomic>
#include <memory>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/log/writer.h"
#include "ucm/lib/log/message.h"
#include "ucm/lib/ara/ara_types.h"
#include "ucm/lib/log/stream_buff.h"
#include "ucm/lib/utl/source_location.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class Stream
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_LIB_UTL_Stream, Simple);
#endif

public:
    explicit Stream() = default;

    explicit Stream(std::ostream&, StreamBuff&,
                    std::vector<std::unique_ptr<Writer>>&) noexcept
    {
    }

    explicit Stream(const ara::ARATypes::LogLevelType&, std::ostream&,
                    StreamBuff&, std::vector<std::unique_ptr<Writer>>&) noexcept
    {
    }

    explicit Stream(const Context&, const ara::ARATypes::LogLevelType&,
                    std::ostream&, StreamBuff&,
                    std::vector<std::unique_ptr<Writer>>&) noexcept
    {
    }

    Stream(const Stream&) = delete;
    Stream& operator=(const Stream&) = delete;

    Stream(Stream&&) noexcept = default;
    Stream& operator=(Stream&&) = delete;

    ~Stream() = default;

    void print() const noexcept { pop<void>(); }

    /// @brief The method specializes on saving the location into
    /// the \ref Message
    void print(const utl::source_location&) noexcept { pop<void>(); }

    /// @brief The method specializes on saving the log level into
    /// the \ref Message
    void print(const ara::ARATypes::LogLevelType&) noexcept { pop<void>(); }

    /// @brief Anything that does not have specializer goes to the std::ostream
    template<class First, class... Rest>
    void print(First first, Rest&&... rest)
    {
        pop<void>();
    }

    /// @brief Send send everythig to the printer, except for control sequences
    template<typename T>
    Stream& operator<<(T&&) noexcept
    {
        return pop<Stream&>();
    }

    /// @brief Handle control sequences
    Stream& operator<<(std::ostream& (*)(std::ostream&)) noexcept { return pop<Stream&>(); }
};

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_STREAM_H_
