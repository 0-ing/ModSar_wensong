//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/sec/provider.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_LIB_SEC_PROVIDER_H_
#define UCM_AAP_LIBRARY_LIB_SEC_PROVIDER_H_

#include <string>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/hash_factory.h"
#include "ucm/lib/sec/verify_factory.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sec   {

class Provider final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(TEST_UCM_LIB_SEC_PROVIDER, Simple);
#endif
public:

    explicit Provider() noexcept = default;

    Provider(const Provider& other) = delete;
    Provider& operator=(const Provider&) = delete;

    Provider(Provider&&) = default;
    Provider& operator=(Provider&&) = default;

    ~Provider() = default;

    auto& hash_factory() noexcept;
    auto& verify_factory() noexcept;

    void set_factory(std::unique_ptr<HashFactory>&&) noexcept;
    void set_factory(std::unique_ptr<VerifyFactory>&&) noexcept;

private:
    std::unique_ptr<HashFactory> hash_factory_{};
    std::unique_ptr<VerifyFactory> verify_factory_{};
};


inline auto& Provider::hash_factory() noexcept
{
    return *hash_factory_;
}

inline auto& Provider::verify_factory() noexcept
{
    return *verify_factory_;
}

}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SEC_PROVIDER_H_
