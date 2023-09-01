//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/fg_ident.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__FG_IDENT_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__FG_IDENT_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/log/ref_logger.h"


/// @defgroup bosch_vrte_ucm_lib_stm__FG_Ident__ut Function group identity
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief Identity of a function group.
///
/// The class represents a unique identification of a function group (FG).
/// At the moment a unique string is designated to serve as unique identifier
/// for function group. In future this could change and the new type should be
/// transformed to a std::string name by the constructor.
class FG_Ident final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Ident, CTor);
    FRIEND_TEST(Test__ucm_vrte_stm__FG_Ident, Compare);
#endif

    constexpr static bool constructible =
            std::is_nothrow_constructible<std::string>::value;
    constexpr static bool move_assignable =
            std::is_nothrow_move_assignable<std::string>::value;
    constexpr static bool copy_assignable =
            std::is_nothrow_copy_assignable<std::string>::value;
    constexpr static bool move_constructible =
            std::is_nothrow_move_constructible<std::string>::value;
    constexpr static bool copy_constructible =
            std::is_nothrow_copy_constructible<std::string>::value;

public:
    /// @brief Construct the FG Identity object.
    FG_Ident(std::string&& value) noexcept(move_constructible)
        : name_(std::move(value))
    {}

    /// @brief Construct the FG Identity object.
    FG_Ident(const std::string& value) noexcept(copy_constructible)
        : name_{value}
    {}

    FG_Ident(FG_Ident     &&) noexcept(move_constructible) = default;
    FG_Ident(FG_Ident const&) noexcept(copy_constructible) = default;

    FG_Ident& operator=(FG_Ident     &&) noexcept(move_assignable) = delete;
    FG_Ident& operator=(FG_Ident const&) noexcept(copy_assignable) = delete;

    ~FG_Ident() = default;

    /// @brief Read accessor for the identity name.
    const auto& name() const noexcept;

private:
    const std::string name_;
};

inline const auto& FG_Ident::name() const noexcept
{
    return name_;
}

inline bool operator==(const FG_Ident& lhs, const FG_Ident& rhs)
{
    return lhs.name() == rhs.name();
}

inline bool operator!=(const FG_Ident& lhs, const FG_Ident& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream&, const FG_Ident&) noexcept;

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

namespace std
{
    template<>
    struct hash<bosch::vrte::ucm::lib::stm::FG_Ident>
    {
        std::size_t
        operator()(const bosch::vrte::ucm::lib::stm::FG_Ident& ident)
        const noexcept
        {
            return std::hash<std::string>{}(ident.name());
        }
    };

    template<>
    struct equal_to<bosch::vrte::ucm::lib::stm::FG_Ident>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::stm::FG_Ident &lhs,
                   const bosch::vrte::ucm::lib::stm::FG_Ident &rhs) const
        {
            return lhs.name() == rhs.name();
        }
    };

    template<>
    struct less<bosch::vrte::ucm::lib::stm::FG_Ident>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::stm::FG_Ident &lhs,
                   const bosch::vrte::ucm::lib::stm::FG_Ident &rhs) const
        {
            return lhs.name() < rhs.name();
        }
    };
}   // namespace std

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__FG_IDENT_H_
