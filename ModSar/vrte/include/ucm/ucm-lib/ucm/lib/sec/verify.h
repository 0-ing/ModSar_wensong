//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/sec/verify.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Hans Berghaell
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_LIB_SEC_VERIFY_H_
#define UCM_AAP_LIBRARY_LIB_SEC_VERIFY_H_

#include "ara/core/result.h"
#include "ara/core/vector.h"

#include <cstdint>
#include <memory>
#include <type_traits>

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sec   {


class Verify
{
public:
    using size_type  = std::size_t;
    using value_type = ::ara::core::Byte;
    using Digest     = ::ara::core::Vector<value_type>;

    virtual ~Verify() = default;

    template<typename T, typename... U>
    static std::unique_ptr<Verify> make(U&&...u)
    {
        static_assert(std::is_base_of<Verify, T>::value, "");
        return std::make_unique<T>(static_cast<U&&>(u)...);
    }

protected:
    Verify()                         = default;
    Verify(Verify const&)            = delete;
    Verify(Verify     &&)            = default;
    Verify& operator=(Verify const&) = delete;
    Verify& operator=(Verify     &&) = default;

public:
    bool verify(Digest const& hash, Digest const& signature);

protected:
    virtual bool _verify(Digest const& hash, Digest const& signature) = 0;
};


}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SEC_VERIFY_H_
