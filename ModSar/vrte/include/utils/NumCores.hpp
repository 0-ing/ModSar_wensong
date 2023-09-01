//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file       NumCores.hpp
/// @brief      NumCores allows the retrieval of the number of cores on the system.
/// @copyright  Robert Bosch GmbH  2019
/// @author     Christopher Serr

#ifndef UTILS_NUMCORES_HPP_INCLUDED
#define UTILS_NUMCORES_HPP_INCLUDED

#include <stdint.h>
#ifdef __QNX__
#include <sys/syspage.h>
#else
#include <sys/unistd.h>
#endif
#include "StdReturnType.hpp"

#include "utils/c/stdio.hpp"        //wrapper to prevent direct inclusion of libc headers

namespace exm
{
namespace utils
{

/// @brief NumCores allows the retrieval of the number of cores on the system.
class NumCores
{
public:
    /// @brief The maximum amount of cores representable.
    static constexpr uint32_t MAX = 32U;

    /// @brief Retrieves the amount of logical cores. With hyper threading these
    /// may not match the actual physical amount of cores.
    NumCores() : nCores(MAX)
    {
#ifdef __QNX__
        int64_t value = static_cast<int64_t>(_syspage_ptr->num_cpu);
#else
        int64_t value = sysconf(_SC_NPROCESSORS_ONLN);
        if (value < 0)
        {
            // Could not determine number, _SC_NPROCESSORS_ONLN may not be supported.
            // We simply assume all the cores that can be in a core mask are
            // valid then.
            value = static_cast<int64_t>(MAX);
        }
#endif // __QNX__

        if (value < 1) // Not covered: The syspage_ptr is read only. This fixes up broken values by
                       // only using a single core in that scenario.
        {
            value = 1; // Not covered: The syspage_ptr is read only. This fixes up broken values by
                       // only using a single core in that scenario.
        }

        if (value > static_cast<int64_t>(
                        MAX)) // Not covered: The syspage_ptr is read only. This fixes up broken
                              // values by only using a single core in that scenario.
        {
            value = static_cast<int64_t>(MAX); // Not covered: The syspage_ptr is read only. This fixes up broken values
                         // by only using a single core in that scenario.
        }

        nCores = static_cast<uint32_t>(value);
    }

    /// @brief NumCores Constructor
    /// Sets the number of cores
    /// @param value Number of cores
    constexpr NumCores(uint32_t value) : nCores(value) {}

    /// @brief Accesses the amount of cores as an integer.
    /// @return The amount of cores as an integer.
    constexpr uint32_t GetValue() const { return nCores; }

    /// @brief Retrieves a core mask where all the bits are set for all the
    /// cores represented by the amount of cores.
    /// @return The corresponding core mask.
    constexpr uint32_t ToMask() const { return (1U << static_cast<uint64_t>(nCores)) - 1U; }

    /// @brief Validates a core mask against the amount of cores. If the core
    /// mask is 0 or bits corresponding to cores not available, then
    /// StdReturnType::INVALID_ARGUMENTS is returned.
    /// @param mask Core mask
    /// @return StdReturnType
    /// @retval OK Success
    /// @retval INVALID_ARGUMENTS The core mask is not valid.
    StdReturnType ValidateMask(uint32_t const mask) const
    {
        uint32_t const coresAsMask = this->ToMask();
        if ((mask & coresAsMask) != mask)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }
        if (mask == 0U)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }
        return StdReturnType::OK;
    }

private:
    uint32_t nCores; ///< The amount of cores as an integer.
};

} // namespace utils
} // namespace exm
#endif
