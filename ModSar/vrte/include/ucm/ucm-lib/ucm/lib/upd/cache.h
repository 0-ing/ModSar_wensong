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
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd__Cache, Any);
    FRIEND_TEST(Test__ucm_lib_upd__Cache, All);
    FRIEND_TEST(Test__ucm_lib_upd__Cache, CTor);
    FRIEND_TEST(Test__ucm_lib_upd__Cache, Create);
    FRIEND_TEST(Test__ucm_lib_upd__Cache, Lookup);
    FRIEND_TEST(Test__ucm_lib_upd__Cache, Remove);
    FRIEND_TEST(Test__ucm_lib_upd__Cache, EraseIf);
    FRIEND_TEST(Test__ucm_lib_upd__Cache, TryCreate);
#endif

public:
    explicit Cache() = default;

    Cache(Cache     &&) = default;
    Cache(const Cache&) = default;

    Cache& operator=(Cache     &&) = default;
    Cache& operator=(const Cache&) = default;

    ~Cache() = default;

    auto size() const noexcept
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return store_.size();
    }

    void clear() noexcept
    {
        std::unique_lock<std::mutex> lock(mutex_);
        cache_reset();
        store_.clear();
    }

    bool any(std::function<bool(std::shared_ptr<_Type>&)>&& cb)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        for(auto it = store_.begin(); it != store_.end(); ++it) {
            //auto item = lockit(it->second);
            //if (not callback(item))
            if (cb(it->second))
                return true;
        }
        return false;
    }

    bool all(std::function<bool(std::shared_ptr<_Type>&)>&& cb)
    {
        return not any([&cb] (std::shared_ptr<_Type>& arg) {
            return not cb(arg);
        });
    }

    void iterate(std::function<bool(std::shared_ptr<_Type>&)>&& cb)
    {
        all(std::move(cb));
    }

    void erase_if(std::function<bool(std::shared_ptr<_Type>&)>&& pred)
    {
        auto predicate = std::move(pred);

        std::unique_lock<std::mutex> lock(mutex_);

        for(auto it = store_.begin(); it != store_.end(); ) {
            try {
                //auto item = lockit(it->second);
                //if (predicate(item)) {
                if (predicate(it->second)) {
                    it = store_.erase(it);
                } else {
                    ++it;
                }
            } catch(...) {
                ++it;
            }
        }

        cache_reset();
    }

    std::shared_ptr<_Type> remove(const _Key& key)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        cache_reset(key);

        auto lk = store_.find(key);
        if (lk != store_.end()) {
            //auto element = lockit(lk->second);
            auto element = lk->second;
            lk = store_.erase(lk);
            return element;
        }

        throw std::runtime_error("'" + std::to_string(key) + "' not found");
    }

    std::shared_ptr<_Type> lookup(const _Key& key)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        if (cached_) {
            if (key == cached_->key())
                //return lockit(cached_);
                return cached_;
        }

        auto lk = store_.find(key);
        if (lk != store_.end()) {
            //return lockit(cache_update(lk->second));
            return cache_update(lk->second);
        }

        throw std::runtime_error("'" + std::to_string(key) + "' not found");
    }

    std::shared_ptr<_Type> create(
            std::function<_Key()>&& arg_key,
            std::function<std::shared_ptr<_Type>(const _Key&)>&& arg_item)
    {
        auto f_key = std::move(arg_key);
        auto f_item = std::move(arg_item);

        std::unique_lock<std::mutex> lock(mutex_);

        auto key = f_key();
        auto val = store_.find(key);
        while (val != store_.end()) {
            key = f_key();
            val = store_.find(key);
        }

        auto item = f_item(key);
        return create(item);
    }

    std::shared_ptr<_Type> try_create(
            std::function<_Key()>&& arg_key,
            std::function<std::shared_ptr<_Type>(const _Key&)>&& arg_item)
    {
        auto f_key = std::move(arg_key);
        auto f_item = std::move(arg_item);

        std::unique_lock<std::mutex> lock(mutex_);

        auto key = f_key();
        auto val = store_.find(key);
        if (val != store_.end()) {
            return cache_update(val->second);
        } else {
            auto item = f_item(key);
            return create(item);
        }
    }

private:
    mutable std::mutex mutex_{};

    std::shared_ptr<_Type> cached_{};
    std::unordered_map<_Key, std::shared_ptr<_Type>> store_{};

    std::shared_ptr<_Type>& cache_update(
            std::shared_ptr<_Type>& element) noexcept
    {
        cached_ = element;
        return cached_;
    }

    void cache_reset() noexcept
    {
        cached_.reset();
    }

    void cache_reset(const _Key& key) noexcept
    {
        if (cached_) {
            if (key == cached_->key()) {
                cached_.reset();
            }
        }
    }

    void cache_reset(std::shared_ptr<_Type>& element) noexcept
    {
        if (cached_) {
            if (element->key() == cached_->key()) {
                cached_.reset();
            }
        }
    }

    std::shared_ptr<_Type> create(std::shared_ptr<_Type>& element)
    {
        auto lk = store_.find(element->key());
        if (lk != store_.end()) {
            //return lockit(cache_update(lk->second));
            return cache_update(lk->second);
        } else {
            auto kvpair = store_.emplace(element->key(), element);
            //return lockit(cache_update(kvpair.first->second));
            return cache_update(kvpair.first->second);
        }
    }

//    std::shared_ptr<_Type> lockit(std::shared_ptr<_Type>& element)
//    {
//        auto locked_element =
//                lib::utl::SharedLocker<_Type>::lockit(element);
//        locked_element->touch();
//        return std::move(locked_element);
//    }
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UPD_TRANSACTION_CACHE_H_
