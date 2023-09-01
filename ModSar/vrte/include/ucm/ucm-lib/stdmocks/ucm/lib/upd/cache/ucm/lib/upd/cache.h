//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/cache.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_CACHE_H_
#define UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_CACHE_H_

#include <mutex>
#include <memory>
#include <functional>
#include <unordered_map>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"
#include "ucm/lib/utl/object_locker.h"
#include "ucm/lib/utl/shared_locker.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace upd {

template<class _Type, class _Key = id_type>
class Cache final
      : virtual protected ucm::mock::Sequence
{
public:
    explicit Cache() noexcept = default;

    Cache(Cache&&) noexcept = default;
    Cache& operator=(Cache&&) = default;

    Cache(const Cache&) = default;
    Cache& operator=(const Cache&) = default;

    ~Cache() = default;

    auto size() const noexcept
    {
        return pop<size_t>();
    }

    void clear() noexcept
    {
        pop<void>();
    }

    bool any(std::function<bool(std::shared_ptr<_Type>&)>&& )
    {
        return pop<bool>();
    }

    bool all(std::function<bool(std::shared_ptr<_Type>&)>&& )
    {
        return pop<bool>();
    }

    void iterate(std::function<bool(std::shared_ptr<_Type>&)>&& )
    {
        pop<void>();
    }

    void erase_if(std::function<bool(std::shared_ptr<_Type>&)>&& )
    {
        pop<void>();
    }

    std::shared_ptr<_Type> remove(const _Key& )
    {
        return pop<std::shared_ptr<_Type>>();
    }

    std::shared_ptr<_Type> lookup(const _Key& )
    {
        return pop<std::shared_ptr<_Type>>();
    }

    std::shared_ptr<_Type> create(
            std::function<_Key()>&& ,
            std::function<std::shared_ptr<_Type>(const _Key&)>&& )
    {
        return pop<std::shared_ptr<_Type>>();
    }

    std::shared_ptr<_Type> try_create(
            std::function<_Key()>&& ,
            std::function<std::shared_ptr<_Type>(const _Key&)>&& )
    {
        return pop<std::shared_ptr<_Type>>();
    }
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_CACHE_H_
