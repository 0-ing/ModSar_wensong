//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/sec/keys.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Hans Berghaell
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_LIB_SEC_KEYS_H_
#define UCM_AAP_LIBRARY_LIB_SEC_KEYS_H_

#include "ucm/mock/sequence.h"
#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace sec {


class Keys
    : virtual protected ucm::mock::Sequence
{
public:
    using value_type = std::uint8_t;
    using size_type  = std::size_t;
    using key_type   = std::vector<value_type>;
    using slot_type  = std::size_t;

    enum class EType
    {
        PublicKey,
        Certificate
    };

    virtual ~Keys() = default;

    template<typename T, typename... U>
    static std::unique_ptr<Keys> make(U&&...u)
    {
        static_assert(std::is_base_of<Keys, T>::value, "");
        return std::unique_ptr<T>(new T (static_cast<U&&>(u)...));
    }

    bool import(key_type  const&) { return pop<bool>(); }
    bool load  (slot_type const&) { return pop<bool>(); }
    bool load  (key_type  const&, EType const &) { return pop<bool>(); }

protected:
    Keys()                       = default;
    Keys(Keys const&)            = delete;
    Keys(Keys     &&)            = default;
    Keys& operator=(Keys const&) = delete;
    Keys& operator=(Keys     &&) = default;

    virtual bool _import(key_type  const&) = 0;
    virtual bool _load  (slot_type const&) = 0;
    virtual bool _load  (key_type  const&, EType const &) = 0;
};


}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SEC_KEYS_H_
