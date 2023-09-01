//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/stm/fg_cache/ucm/lib/stm/fg_cache.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__FG_CACHE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__FG_CACHE_H_

#include <mutex>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

#include "ucm/lib/stm/error.h"
#include "ucm/lib/stm/proxy.h"
#include "ucm/lib/stm/fg_store.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

class FG_Cache final : virtual protected ucm::mock::Sequence
{
public:
    explicit FG_Cache() {}

    FG_Cache(FG_Cache     &&) = delete;
    FG_Cache(FG_Cache const&) = delete;

    FG_Cache& operator=(FG_Cache     &&) = delete;
    FG_Cache& operator=(FG_Cache const&) = delete;

    ~FG_Cache() = default;

    void proxy_set(Proxy*) noexcept {}

    Error remove(const FG_Ident&) noexcept
    { return pop<Error>(); }

    Error insert(FG_Ident&&, FG_State&&) noexcept
    { return pop<Error>(); }

    Error update(const FG_Ident&, FG_State&&) noexcept
    { return pop<Error>(); }

    Error update(const FG_State&,
                 const std::vector<std::string>) noexcept
    { return pop<Error>(); }

    Error fg_verify(const std::vector<std::string>&) noexcept
    { return pop<Error>(); }

    Error fg_activate(const std::vector<std::string>&) noexcept
    { return pop<Error>(); }

    Error fg_rollback(const std::vector<std::string>&) noexcept
    { return pop<Error>(); }
};

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__FG_CACHE_H_
