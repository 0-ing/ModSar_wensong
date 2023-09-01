//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/fg_state.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__FG_STATE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__FG_STATE_H_

#include <string>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/system_error.h"
#include "ucm/generic_error.h"
#include "ucm/lib/log/ref_logger.h"


/// @defgroup bosch_vrte_ucm_lib_stm__FG_State__ut Function group state
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief State for a function group.
///
/// The state for a FG is currently represented as a string. In contrast to an
/// enum this gives a better flexibility in future - one does not need to
/// change the state type, but make the transformation at the actual call
/// to STM.
class FG_State final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_stm__FG_State, CTor);
    FRIEND_TEST(Test__ucm_lib_stm__FG_State, Operator);
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
    /// @brief Construct a function group state object.
    explicit FG_State() noexcept(constructible) = default;

    /// @brief Construct a function group state object
    /// @param value The initial value for the state
    explicit FG_State(std::string&& value) noexcept(move_constructible)
        : value_(std::move(value))
    {}

    /// @brief Construct a function group state object
    /// @param value The initial value for the state
    explicit FG_State(const std::string& value) noexcept(copy_constructible)
        : value_{value}
    {}

    FG_State(FG_State     &&) noexcept(move_constructible) = default;
    FG_State(FG_State const&) noexcept(copy_constructible) = default;

    FG_State& operator=(FG_State     &&) noexcept(move_assignable) = default;
    FG_State& operator=(FG_State const&)  = default;

    ~FG_State() = default;

    /// @brief Evaluate FG_State in boolean context.
    /// The operator is helper to check if the state value is valid.
    explicit operator bool() const noexcept;

    /// @brief Set value for the state object.
    /// @param value The new value for the state.
    void value(std::string&& value) noexcept(move_assignable);

    /// @brief Accessor for the value of the state object.
    const auto& value() const noexcept;

private:
    std::string value_{};   ///< Value of the state object.
};

inline FG_State::operator bool() const noexcept
{
    return not value_.empty();
}

inline void FG_State::value(std::string&& newval) noexcept(move_assignable)
{
    value_ = std::move(newval);
}

inline const auto& FG_State::value() const noexcept
{
    return value_;
}

inline bool operator==(const FG_State& lhs, const FG_State& rhs)
{
    return lhs.value() == rhs.value();
}

inline bool operator!=(const FG_State& lhs, const FG_State& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream&, const FG_State&) noexcept;

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

namespace std
{
    template<>
    struct hash<bosch::vrte::ucm::lib::stm::FG_State>
    {
        std::size_t
        operator()(const bosch::vrte::ucm::lib::stm::FG_State& state)
        const noexcept
        {
            return std::hash<std::string>{}(state.value());
        }
    };

    template<>
    struct equal_to<bosch::vrte::ucm::lib::stm::FG_State>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::stm::FG_State &lhs,
                   const bosch::vrte::ucm::lib::stm::FG_State &rhs) const
        {
            return lhs == rhs;
        }
    };

    template<>
    struct less<bosch::vrte::ucm::lib::stm::FG_State>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::stm::FG_State &lhs,
                   const bosch::vrte::ucm::lib::stm::FG_State &rhs) const
        {
            return lhs.value() < rhs.value();
        }
    };
}   // namespace std


#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__FG_STATE_H_
