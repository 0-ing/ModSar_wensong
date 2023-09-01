//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/stream_buff.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_LOG_STREAM_BUFF_H_
#define UCM_AAP_LIBRARY_LIB_LOG_STREAM_BUFF_H_

#include <array>
#include <streambuf>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class StreamBuff : public std::streambuf
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_LIB_UTL_StreamBuff, Simple);
#endif

    using Base = std::streambuf;

    constexpr static std::streamsize buffer_size = 256;
    constexpr static std::streamsize buffer_maxfill = buffer_size - 4;

public:
    explicit StreamBuff() noexcept;

    StreamBuff(StreamBuff&&) noexcept = default;
    StreamBuff& operator=(StreamBuff&&) = default;

    StreamBuff(const StreamBuff&) = delete;
    StreamBuff& operator=(const StreamBuff&) = delete;

    virtual ~StreamBuff() = default;

    bool empty() const noexcept;

    /// @brief Resets the buffer by calling Base::setp()
    void reset() noexcept;

    /// @brief Prepares the buffer to be associated to a \ref Messsage
    /// Must be called after writing is finished and before the
    /// log writers are called with the \ref Message
    void finish() noexcept;

    /// @brief Return pointer to the data area
    const char_type* cdata() const noexcept;

protected:
    int_type overflow(int_type ch) override;
    std::streamsize xsputn(const char_type* s, std::streamsize n) override;

private:
    std::array<char_type, buffer_size> buffer_{};
};

inline bool StreamBuff::empty() const noexcept
{
    return pptr() == pbase();
}

inline const StreamBuff::char_type* StreamBuff::cdata() const noexcept
{
    return buffer_.data();
}

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_STREAM_BUFF_H_
