//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file         src/ucm/mocks/bit_flags.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_BUILD_UCM_MOCKS_BIT_FLAGS_H_
#define UCM_AAP_BUILD_UCM_MOCKS_BIT_FLAGS_H_

#include <type_traits>

namespace bosch    {
namespace vrte     {
namespace ucm      {
namespace mock     {

template<typename Enum, typename Store = unsigned char>
struct BitFlags
{
    using Num = typename std::underlying_type<Enum>::type;

    Store store {0};

    static constexpr Num num (Enum flag)
    {
        return static_cast<Num>(flag);
    }

    static constexpr bool sane(Enum flag)
    {
        return 0 <= num(flag) and num(flag) < sizeof(Store)*8;
    }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
    template<Enum flag> constexpr void is(bool arg)
    {
        static_assert(sane(flag), "not within storage range");
        if (arg)
            store |=  static_cast<Store>(1 << num(flag));
        else
            store &= ~static_cast<Store>(1 << num(flag));
    }
#pragma GCC diagnostic pop    
    template<Enum flag> constexpr bool is() const
    {
        static_assert(sane(flag), "");
        return store & (1 << num(flag));
    }
};

} // namespace mock
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // UCM_AAP_BUILD_UCM_MOCKS_BIT_FLAGS_H_
