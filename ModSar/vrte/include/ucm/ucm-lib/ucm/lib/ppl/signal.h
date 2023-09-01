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

#include "ucm/lib/ara/ara_types.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Signal
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
    Signal(const Result&) noexcept;
    Signal(const Command&) noexcept;
    explicit Signal(const Command&, const Result&) noexcept;

    // copy semantics
    Signal(const Signal&) = default;
    Signal& operator=(const Signal&) = default;

    // move semantic
    Signal(Signal&&) noexcept = default;
    Signal& operator=(Signal&&) = default;

    ~Signal() = default;

    void reset() noexcept;

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
    return result_;
}

inline void Signal::result(const Signal::Result& value) noexcept
{
    result_ = value;
}

inline const Signal::Command& Signal::command() const noexcept
{
    return command_;
}

inline void Signal::command(const Signal::Command& value) noexcept
{
    command_ = value;
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_SIGNAL_H_
