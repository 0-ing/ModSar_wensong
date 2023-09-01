//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/fg_entry.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__FG_ENTRY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__FG_ENTRY_H_

#include <mutex>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/stm/fg_ident.h"
#include "ucm/lib/stm/fg_state.h"
#include "ucm/lib/log/ref_logger.h"

/// @defgroup bosch_vrte_ucm_lib_stm__FG_Entry__ut Function group entry
/// @ingroup bosch_vrte_ucm_lib_stm__ut
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

/// @brief Function Group entry.
///
/// The class represents a FG, composed of its identity together with its
/// previous, current and next states. A simple FSM is supported as well, to
/// show the progress of a FG state change.
class FG_Entry final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_stm__FG_Entry, CTor);
    FRIEND_TEST(Test__ucm_lib_stm__FG_Entry, Change);
    FRIEND_TEST(Test__ucm_lib_stm__FG_Entry, Operator);
#endif

public:
    /// @brief Simple FSM for change phases of a FG state
    enum class FSM : unsigned
    {
        kReq,   ///< State change in progress cstate_ != nstate_
        kAck,   ///< State acknowledged i.e. cstate_ == nstate_
        kNak    ///< State change failed cstate_ != nstate_
    };

private:
    constexpr static bool constructible =
            (std::is_nothrow_move_constructible<FG_State>::value and
             std::is_nothrow_copy_constructible<FG_State>::value and
             std::is_nothrow_move_constructible<FG_Ident>::value and
             std::is_nothrow_constructible<FSM>::value);
    constexpr static bool move_assignable =
            (std::is_nothrow_move_assignable<FG_State>::value and
             std::is_nothrow_move_assignable<FG_Ident>::value and
             std::is_nothrow_move_assignable<FSM>::value);
    constexpr static bool copy_assignable =
            (std::is_nothrow_copy_assignable<FG_State>::value and
             std::is_nothrow_copy_assignable<FG_Ident>::value and
             std::is_nothrow_copy_assignable<FSM>::value);
    constexpr static bool move_constructible =
            (std::is_nothrow_move_constructible<FG_State>::value and
             std::is_nothrow_move_constructible<FG_Ident>::value and
             std::is_nothrow_move_constructible<FSM>::value);
    constexpr static bool copy_constructible =
            (std::is_nothrow_copy_constructible<FG_State>::value and
             std::is_nothrow_copy_constructible<FG_Ident>::value and
             std::is_nothrow_copy_constructible<FSM>::value);
    constexpr static bool fgs_move_assignable =
            std::is_nothrow_move_assignable<FG_State>::value;
    constexpr static bool fgs_copy_assignable =
            std::is_nothrow_copy_assignable<FG_State>::value;
    constexpr static bool fsm_copy_asignable =
             std::is_nothrow_move_assignable<FSM>::value;

public:
    /// @brief Construct a FG_Entry object.
    /// @param ident Identity of the FG
    /// @param state Initial state of the FG
    explicit FG_Entry(FG_Ident&& ident, FG_State&& state)
        noexcept(constructible);

    FG_Entry(FG_Entry     &&) noexcept(move_constructible) = default;
    FG_Entry(FG_Entry const&) noexcept(copy_constructible) = delete;

    FG_Entry& operator=(FG_Entry     &&) noexcept(move_assignable) = delete;
    FG_Entry& operator=(FG_Entry const&) noexcept(copy_assignable) = delete;

    ~FG_Entry() = default;

    /// @brief Getter for the FunctionGroup ident.name()
    const auto& name() const noexcept;

    /// @brief Getter for the FunctionGroup ident.
    const auto& ident() const noexcept;

    /// @brief Getter for the previous state value
    const auto& pstate() const noexcept;

    /// @brief Getter for the current state value
    const auto& cstate() const noexcept;

    /// @brief Getter for the next state value
    const auto& nstate() const noexcept;

    /// @brief Begin state update.
    ///
    /// state nstate_ = state
    /// fsm_ = FSM::kReq
    void req_change(FG_State&& state)
        noexcept(fgs_move_assignable and fsm_copy_asignable);

    /// @brief Acknowledge state update.
    ///
    /// pstate_ = cstate_
    /// cstate_ = nstate_,
    /// fsm_ = FSM::kAck
    void ack_change()
        noexcept(fgs_move_assignable and
                 fgs_copy_assignable and
                 fsm_copy_asignable);

    /// @brief Reject state update.
    ///
    /// fsm_ = FSM::kNak
    void nak_change()
        noexcept(fsm_copy_asignable);

    /// @brief Clear state update.
    ///
    /// nstate_ = cstate_
    /// fsm_ = FSM::kAck
    void clr_change()
        noexcept(fgs_copy_assignable and fsm_copy_asignable);

    /// @brief Clear state update.
    ///
    /// nstate_ = cstate_ = state
    /// fsm_ = FSM::kAck
    void clr_change(FG_State&& state)
        noexcept(fgs_move_assignable and
                 fgs_copy_assignable and
                 fsm_copy_asignable);

private:
    FSM      fsm_;      ///< Result of the state change
    FG_Ident ident_;    ///< Identity of the FG entry
    FG_State pstate_;   ///< Previous state
    FG_State cstate_;   ///< Current state
    FG_State nstate_;   ///< Next state (i.e. requested)
};

inline const auto& FG_Entry::name() const noexcept
{
    return ident_.name();
}

inline const auto& FG_Entry::ident() const noexcept
{
    return ident_;
}

inline const auto& FG_Entry::pstate() const noexcept
{
    return pstate_.value();
}

inline const auto& FG_Entry::cstate() const noexcept
{
    return cstate_.value();
}

inline const auto& FG_Entry::nstate() const noexcept
{
    return nstate_.value();
}

inline bool operator==(const FG_Entry& lhs, const FG_Entry& rhs)
{
    return lhs.ident() == rhs.ident();
}

inline bool operator!=(const FG_Entry& lhs, const FG_Entry& rhs)
{
    return !(lhs == rhs);
}

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

namespace std
{
    template<>
    struct hash<bosch::vrte::ucm::lib::stm::FG_Entry>
    {
        std::size_t
        operator()(const bosch::vrte::ucm::lib::stm::FG_Entry& entry)
        const noexcept
        {
            return std::hash<std::string>{}(entry.name());
        }
    };

    template<>
    struct equal_to<bosch::vrte::ucm::lib::stm::FG_Entry>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::stm::FG_Entry &lhs,
                   const bosch::vrte::ucm::lib::stm::FG_Entry &rhs) const
        {
            return lhs == rhs;
        }
    };

    template<>
    struct less<bosch::vrte::ucm::lib::stm::FG_Entry>
    {
        bool
        operator()(const bosch::vrte::ucm::lib::stm::FG_Entry &lhs,
                   const bosch::vrte::ucm::lib::stm::FG_Entry &rhs) const
        {
            return lhs.name() < rhs.name();
        }
    };
}   // namespace std

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__FG_ENTRY_H_
