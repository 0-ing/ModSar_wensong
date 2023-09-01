//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/token.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks
///

#ifndef UCM_AAP_LIBRARY_LIB_PPL_TOKEN_H_
#define UCM_AAP_LIBRARY_LIB_PPL_TOKEN_H_

#include <thread>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/ppl/tag.h"
#include "ucm/lib/ppl/frame.h"
#include "ucm/lib/ppl/signal.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace ppl {

class Token final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Lib_Pipeline_Token, Simple1);
    FRIEND_TEST(Test_Lib_Pipeline_Token, Simple2);
    FRIEND_TEST(Test_Lib_Pipeline_Token, Simple3);
    FRIEND_TEST(Test_Lib_Pipeline_Token, Simple4);
#endif

public:
    Token() noexcept = default;
    explicit Token(Frame&&) noexcept;
    explicit Token(Signal&&) noexcept;
    explicit Token(Frame&&, Signal&&) noexcept;

    // copy semantics
    Token(const Token& other) = delete;
    Token& operator=(const Token&) = delete;

    // move semantic
    Token(Token&&) noexcept = default;
    Token& operator=(Token&&) = default;

    ~Token() = default;

    /// @brief return ** pointer to the next token
    auto next() noexcept;
    void next(Token*) noexcept;

    /// @brief return reference to the Frame object contained
    auto& frame() noexcept;

    void load(Frame&&) noexcept;

    void load(Signal&&) noexcept;

    void load(const Signal&) noexcept;

    /// @brief return reference to the signal object contained
    const Signal& signal() const noexcept;

    /// @brief Check if the Token may be discarded
    auto may_discard() const noexcept;

    void reset() noexcept;

    const auto& tag() const noexcept;

    void tag(const Tag&) noexcept;

private:
    Tag tag_{};
    Frame frame_{};
    Signal signal_{};
    Token* next_{nullptr};
};

inline const auto& Token::tag() const noexcept
{
    return tag_;
}

inline void Token::tag(const Tag& other) noexcept
{
    tag_ = other;
}

inline auto Token::next() noexcept
{
    return next_;
}

inline void Token::next(Token* other) noexcept
{
    next_ = other;
}

inline auto& Token::frame() noexcept
{
    return frame_;
}

inline const Signal& Token::signal() const noexcept
{
    return signal_;
}

inline auto Token::may_discard() const noexcept
{
    return frame_.may_discard();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_PPL_TOKEN_H_
