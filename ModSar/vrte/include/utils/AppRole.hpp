//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file   AppRole.hpp
/// @brief  Definition of class AppRole
//=============================================================================

#ifndef UTILS_APPROLE_HPP
#define UTILS_APPROLE_HPP

namespace exm
{
namespace utils
{

/// @brief Type which defines the different application roles. Each AppRole can
/// contain various roles it encompasses. There are various methods for dealing
/// with this.
class AppRole
{
public:
    /// @brief The individual flags.
    enum Flag : uint8_t
    {
        NoRole = 0x00U,       ///< No role is set for Application
        SM = 0x01U,           ///< Application role as state manager
        PHM = 0x02U,          ///< Application role as platform health manager
        EcuCfg = 0x04U,       ///< Application role as ECU configurator
        EarlyProcess = 0x08U, ///< Application role as early process
    };

    /// @brief Constructor
    /// @param flags_ The flags indicating which roles are set.
    constexpr AppRole(Flag flags_) : flags(static_cast<uint8_t>(flags_)) {}

    /// @brief Default Constructor with no flags
    constexpr AppRole() : AppRole(NoRole) {}

    /// @brief Checks if two values contain the exact same roles.
    /// @param rhs The other value to compare to.
    /// @return Returns whether the two values contain the exact same roles.
    constexpr inline bool operator==(const AppRole& rhs) const { return flags == rhs.flags; }

    /// @brief Checks if two values don't contain the exact same roles.
    /// @param rhs The other value to compare to.
    /// @return Returns whether the two values don't contain the exact same roles.
    constexpr inline bool operator!=(const AppRole& rhs) const { return flags != rhs.flags; }

    /// @brief Returns true if all of the roles in other are contained within
    /// our roles.
    /// @param other The roles that should all be contained within our roles.
    /// @return Value indicating if all the roles in other are contained within
    /// our roles.
    constexpr bool Contains(AppRole other) const { return (flags & other.flags) == other.flags; }

    /// @brief Returns true if there are roles common to both values.
    /// @param other The roles that might intersect with our roles.
    /// @return Value indicating if there are roles common to both values.
    constexpr bool Intersects(AppRole other) const { return (flags & other.flags) != 0U; }

    /// @brief Insert additional roles into the value.
    /// @param role The roles to insert.
    void Insert(AppRole role) { flags |= role.flags; }

private:
    uint8_t flags; ///< The flags indicating which roles are set.
};
}

} // namespaces

#endif /* header include protection */
