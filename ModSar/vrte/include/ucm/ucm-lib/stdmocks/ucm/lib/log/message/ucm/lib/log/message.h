//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/message.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_LOG_MESSAGE_H_
#define UCM_AAP_LIBRARY_LIB_LOG_MESSAGE_H_

#include <chrono>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/log/context.h"
#include "ucm/lib/ara/ara_types.h"
#include "ucm/lib/utl/source_location.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class Message
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_LIB_UTL_Message, Simple);
#endif

public:
    using clock_type = std::chrono::high_resolution_clock;

    explicit Message(const std::size_t& seq) noexcept
	    : seqnum_{seq}
		, timestamp_(clock_type::now())
	{	
	}

    explicit Message(const ara::ARATypes::LogLevelType& level,
                     const std::size_t& seq) noexcept
	    : seqnum_{seq}
        , timestamp_(clock_type::now())
        , level_{level}
	{	   
	}

    explicit Message(const ara::ARATypes::LogLevelType& level,
                     const Context& context, const std::size_t& seq) noexcept
	    : context_(context)
        , seqnum_{seq}
        , timestamp_(clock_type::now())
        , level_{level}
	{
	}	

    Message(Message&&) noexcept = default;
    Message& operator=(Message&&) = default;

    Message(const Message&) = default;
    Message& operator=(const Message&) = default;

    ~Message() = default;

    bool valid() const noexcept;

    bool sloc_valid() const noexcept;

    const auto& level() const noexcept;

    const char* text() const noexcept;

    const Context& context() const noexcept;

    std::size_t sequence_number() const noexcept;

    const clock_type::time_point& timestamp() const noexcept;

    const utl::source_location& source_location() const noexcept;



    Message& operator=(const char*) noexcept;

    Message& operator=(const Context&) noexcept;

    Message& operator=(const utl::source_location&) noexcept;

    Message& operator=(const ara::ARATypes::LogLevelType&) noexcept;

private:
    Context context_{};
    std::size_t seqnum_;
    bool sloc_valid_{false};
    const char* text_{nullptr};
    utl::source_location sloc_{};
    clock_type::time_point timestamp_;
    ara::ARATypes::LogLevelType level_{ara::ARATypes::LogLevelType::kDebug};
};

inline bool Message::valid() const noexcept
{
    return pop<bool>();
}

inline bool Message::sloc_valid() const noexcept
{
    return pop<bool>();
}

inline const auto& Message::level() const noexcept
{
    return pop<ara::ARATypes::LogLevelType const&>();
}

inline const char* Message::text() const noexcept
{
    return pop<const char*>();
}

inline const Context& Message::context() const noexcept
{
    return pop<Context const&>();
}

inline std::size_t Message::sequence_number() const noexcept
{
    return pop<std::size_t>();
}

inline const utl::source_location& Message::source_location() const noexcept
{
    return pop<utl::source_location const&>();
}

inline const Message::clock_type::time_point& Message::timestamp() const noexcept
{
    return pop<Message::clock_type::time_point const&>();
}

inline Message& Message::operator=(const char*) noexcept
{
    return pop<Message&>();
}

inline Message& Message::operator=(const Context&) noexcept
{
    return pop<Message&>();
}

inline Message& Message::operator=(const utl::source_location&) noexcept
{
    return pop<Message&>();
}

inline Message& Message::operator=(const ara::ARATypes::LogLevelType&) noexcept
{
    return pop<Message&>();
}

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_MESSAGE_H_
