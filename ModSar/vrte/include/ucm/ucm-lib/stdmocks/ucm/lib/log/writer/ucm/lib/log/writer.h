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
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class Writer : virtual protected ucm::mock::Sequence
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

    explicit Writer(const level_type& level) noexcept
    : level_{level}
    {
    }

    Writer(Writer&& other) noexcept
        : level_{other.level_.load()}
    {
    }

    Writer& operator=(Writer&&)
    {
        return *this;
    }

    Writer(const Writer&) = delete;
    Writer& operator=(const Writer&) = delete;

    virtual ~Writer() = default;

    virtual void output(const Message&) noexcept { pop<void>(); }

    auto loglevel() const noexcept;
    void loglevel(const level_type&) noexcept;

protected:
    void context(const Message&, char*, size_t) noexcept { pop<void>(); }

    bool message_levelok(const Message&) const noexcept;

private:
    mutable std::mutex mutex_{};
    std::atomic<level_type> level_{level_type::kVerbose};
};

inline bool Writer::message_levelok(const Message&) const noexcept
{
    return pop<bool>();
}

inline auto Writer::loglevel() const noexcept
{
    return pop<level_type>();
}

inline void Writer::loglevel(const level_type&) noexcept
{
    pop<void>();
}


}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_WRITER_H_
