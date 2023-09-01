//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/dir.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UTL_DIR_H_
#define UCM_AAP_LIBRARY_LIB_UTL_DIR_H_

#include "sys/mock_stat.h"

#include <string>
#include <vector>

#include "ucm/mock/sequence.h"
#include "ucm/lib/utl/syserror.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class Dir final
    : virtual protected ucm::mock::Sequence
{

public:
    explicit Dir(const mode_t&, std::string&&) {}
    explicit Dir(const mode_t&, const std::string&) {}

    Dir(const Dir&) = delete;
    Dir& operator=(const Dir&) = delete;

    // move semantic
    Dir(Dir&&) noexcept(true) = default;
    Dir& operator=(Dir&&) noexcept(true) = default;

    ~Dir() = default;

    auto syserror() const noexcept;

    const auto& path() const noexcept;
    const auto& oserror() const noexcept;

    std::size_t files_count(const std::string&) { return pop<std::size_t>(); }

    std::vector<std::string> scan_files(const std::string&)
    {
        return pop<std::vector<std::string>>();
    }

private:
    int oserror_{0};
    std::string path_{};
    std::vector<std::string> files_{};

    void create(const std::string&, mode_t mode);
};

inline auto Dir::syserror() const noexcept
{
    return pop<SysError>();
}

inline const auto& Dir::path() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& Dir::oserror() const noexcept
{
    return pop<int&&>();
}


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif /* UCM_AAP_LIBRARY_LIB_UTL_DIR_H_ */
