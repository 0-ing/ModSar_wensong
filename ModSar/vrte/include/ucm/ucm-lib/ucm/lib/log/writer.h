//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/writer.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_LOG_WRITER_H_
#define UCM_AAP_LIBRARY_LIB_LOG_WRITER_H_

#include <mutex>
#include <atomic>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/log/message.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class Writer
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_log_Writer, CTor);
    FRIEND_TEST(Test_ucm_lib_log_Writer, Output);
    FRIEND_TEST(Test_ucm_lib_log_Writer, Context);
    FRIEND_TEST(Test_ucm_lib_log_Writer, CTorMove);
    FRIEND_TEST(Test_ucm_lib_log_Writer, MessageLevelOK);
#endif

public:
    using level_type = ara::ARATypes::LogLevelType;

    Writer() noexcept = default;

    explicit Writer(const level_type&);

    Writer(Writer&&) noexcept;
    Writer& operator=(Writer&&);

    Writer(const Writer&) = delete;
    Writer& operator=(const Writer&) = delete;

    virtual ~Writer() = default;

    virtual void output(const Message&) noexcept;

    auto loglevel() const noexcept;
    void loglevel(const level_type&) noexcept;

protected:
    mutable std::mutex mutex_{};

    void context(const Message&, char*, size_t) noexcept;

    bool message_levelok(const Message&) const noexcept;

private:
    std::atomic<level_type> level_{level_type::kVerbose};

    static const char *trim_filename(const char *) noexcept;
};

inline bool Writer::message_levelok(const Message& message) const noexcept
{
    return static_cast<unsigned>(message.level())
            <= static_cast<unsigned>(level_.load(std::memory_order_relaxed));
}

inline auto Writer::loglevel() const noexcept
{
    return level_.load(std::memory_order_relaxed);
}

inline void Writer::loglevel(const level_type& value) noexcept
{
    level_.store(value, std::memory_order_relaxed);
}


}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_WRITER_H_
