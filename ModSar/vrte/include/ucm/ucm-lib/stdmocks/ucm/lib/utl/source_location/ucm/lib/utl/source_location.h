//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/source_location.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_SOURCE_LOCATION_H_
#define UCM_AAP_LIBRARY_LIB_UTL_SOURCE_LOCATION_H_

#include <string>
#include <cstddef>

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class source_location
{

public:
    static constexpr source_location
    current(const char* file = __builtin_FILE(),
            const char* func = __builtin_FUNCTION(),
            int line = __builtin_LINE(), int column = 0) noexcept
    {
        return source_location{file, func, line, column};
    }

    constexpr
    source_location(const char* file_name = __builtin_FILE(),
                    const char* function_name = __builtin_FUNCTION(),
                    int line = __builtin_LINE(), int column = 0) noexcept
        : line_(line)
        , column_{column}
        , filename_{file_name}
        , function_{function_name}
    {
    }

    constexpr uint_least32_t line() const noexcept       { return line_;     }
    constexpr uint_least32_t column() const noexcept     { return column_;   }
    constexpr const char* file_name() const noexcept     { return filename_; }
    constexpr const char* function_name() const noexcept { return function_; }

private:
    int line_{0};
    int column_{0};
    const char* filename_;
    const char* function_;
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif  // UCM_AAP_LIBRARY_LIB_UTL_SOURCE_LOCATION_H_
