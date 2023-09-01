//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/null_stream.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_LOG__NULL_STREAM_H_
#define UCM_AAP_LIBRARY__UCM_LIB_LOG__NULL_STREAM_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace log   {

class NullStream final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_log__NullStream, Simple);
#endif

public:
    explicit NullStream() noexcept = default;

    NullStream(NullStream     &&) noexcept = default;
    NullStream(NullStream const&) noexcept = default;

    NullStream& operator=(NullStream     &&) noexcept = delete;
    NullStream& operator=(NullStream const&) noexcept = delete;

    ~NullStream() = default;

    template<typename T>
    NullStream& operator<<(T&&) noexcept
    { return *this; }

    NullStream& operator<<(std::ostream& (*)(std::ostream&)) noexcept
    { return *this; }
};

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_LOG__NULL_STREAM_H_
