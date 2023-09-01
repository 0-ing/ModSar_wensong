//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/signal.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_SIGNAL_H_
#define UCM_AAP_LIBRARY_LIB_PPL_SIGNAL_H_

#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/ara/ara_types.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Signal
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Lib_Pipeline_Signal, Simple);
#endif

public:
    enum class Command : unsigned
    {
        kInvalid,
        kPing,         // Ping command
        kAbort,        // Abort command
        kTerminate,    // Terminate command
        kLastEnum
    };

    using Result = ara::ARATypes::ApplicationErrorsType;

    Signal() noexcept = default;
    Signal(const Result& value) noexcept
        : result_{value}
    {
    }
    Signal(const Command& value) noexcept
        : command_{value}
    {

    }
    explicit Signal(const Command& value, const Result& result) noexcept
    : result_{result}, command_{value}
    {

    }

    // copy semantics
    Signal(const Signal&) = default;
    Signal& operator=(const Signal&) = default;

    // move semantic
    Signal(Signal&&) noexcept = default;
    Signal& operator=(Signal&&) = default;

    ~Signal() = default;

    void reset() noexcept { pop<void>(); }

    const Result& result() const noexcept;
    void result(const Result&) noexcept;

    const Command& command() const noexcept;
    void command(const Command&) noexcept;

private:
    Result  result_{Result::Ok};
    Command command_{Command::kInvalid};
};

inline const Signal::Result& Signal::result() const noexcept
{
    return pop<Signal::Result const&>();
}

inline void Signal::result(const Signal::Result&) noexcept
{
    pop<void>();
}

inline const Signal::Command& Signal::command() const noexcept
{
    return pop<Signal::Command const&>();
}

inline void Signal::command(const Signal::Command&) noexcept
{
    pop<void>();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_SIGNAL_H_
