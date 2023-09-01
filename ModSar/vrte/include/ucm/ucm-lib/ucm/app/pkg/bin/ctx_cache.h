//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/ctx_cache.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CTX_CACHE_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CTX_CACHE_H_

#include <mutex>
#include <array>
#include <memory>
#include <unordered_map>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/provider.h"
#include "ucm/lib/pkg/bin/handle.h"
#include "ucm/app/pkg/bin/context.h"


/// @addtogroup bosch_vrte_ucm_app_pkg_bin
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {

/// @class CtxCache
/// @ingroup bosch_vrte_ucm_app_pkg_bin
/// @brief The class is a cache for the SWP processing contexts.
///
/// A SWP processing context is composed from the buffers for the Authentication
/// tag and the data processing blocks.
///
/// At the moment the container is based on std::array. Should there be any
/// performance considerations - it can be re-based on some linked list
/// implementation.
///
/// @note At the moment of the initial development only v0102 of the SWP
/// binary format is available. Should UCM supports more than this one
/// additional Context container and Context map needs to be introduced,
/// together with their accessors and this note removed.
///
class CtxCache final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_app_pkg_bin_ctx_cache, Ctor);
    FRIEND_TEST(Test_ucm_app_pkg_bin_ctx_cache, v0102_acquire);
    FRIEND_TEST(Test_ucm_app_pkg_bin_ctx_cache, v0102_acquire_key);
    FRIEND_TEST(Test_ucm_app_pkg_bin_ctx_cache, lock_entry);
	FRIEND_TEST(Test_ucm_app_pkg_bin_ctx_cache, lock_entry_catch);
#endif

    constexpr static std::size_t v0102_size = 4;

public:
    using Handle = lib::pkg::bin::Handle;

private:
    using Entry = std::shared_ptr<Context>;
    using Cache = std::unordered_map<Handle, Entry>;
    using Store0102 = std::array<Entry, v0102_size>;

public:

    explicit CtxCache(lib::sec::Provider& sec_provider);

    CtxCache(CtxCache     &&) = delete;
    CtxCache(CtxCache const&) = delete;

    CtxCache& operator=(CtxCache     &&) = delete;
    CtxCache& operator=(CtxCache const&) = delete;

    ~CtxCache() = default;

    std::shared_ptr<Context> v0102_acquire() noexcept;

    std::shared_ptr<Context> v0102_acquire(const Handle&) noexcept;

private:
    Cache     ctx_cache_{};
    Store0102 ctx_v0102_{};
    mutable std::mutex mutex_{};

    Entry lock_entry(const Handle&, Entry) noexcept;
};

}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CTX_CACHE_H_
