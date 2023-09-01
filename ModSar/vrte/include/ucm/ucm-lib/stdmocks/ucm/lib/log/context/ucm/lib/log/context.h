//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_LOG_CONTEXT_H_
#define UCM_AAP_LIBRARY_LIB_LOG_CONTEXT_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace log {

class Context final
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_LIB_UTL_Writer, Simple);
#endif
public:
    constexpr static auto id_default() noexcept
    {
        return static_cast<id_type>(0);
    }

    Context() noexcept
        : transid_(id_default())	
	{ 
	   pop<void>(); 
	}

    Context(const id_type& transid) noexcept
	    : transid_(transid)
	{ 
	   pop<void>(); 
	}

    Context(Context&&) noexcept = default;
    Context& operator=(Context&&) = default;

    Context(const Context&) = default;
    Context& operator=(const Context&) = default;

    ~Context() = default;

    const auto& operator()() const noexcept;

private:
    id_type transid_;
};

inline const auto& Context::operator()() const noexcept
{
    return pop<id_type const&>();
}

}    // namespace log
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_LOG_CONTEXT_H_
