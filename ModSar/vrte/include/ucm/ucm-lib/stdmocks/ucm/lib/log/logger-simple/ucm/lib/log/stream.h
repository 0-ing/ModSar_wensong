//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         mock/ucm/lib/log/stream.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_LOG_STREAM_H_
#define UCM_AAP_LIBRARY_LIB_LOG_STREAM_H_

#include <ostream>

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class Stream
{
public:
    template<typename T>
    Stream& operator<<(T&&) noexcept
    {
        return *this;
    }

    Stream& operator<<(std::ostream& (*F)(std::ostream&)) noexcept;
};

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_STREAM_H_
