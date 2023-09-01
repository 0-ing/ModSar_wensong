//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/vrte/sec/sha2.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_sec


#ifndef UCM_AAP_PROCESSING_VRTE_VRTE_SEC_SHA2_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE_VRTE_SEC_SHA2_IMPL_H_

#include "ucm/lib/sec/hash.h"
#include "ucm/vrte/sec/ara_crypto_includes.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include <memory>

/// @addtogroup bosch_vrte_ucm_vrte_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace sec   {

/// @brief SHA2 interface implementation.
///

class SHA2Impl : public lib::sec::Hash
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, Simple);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, translate);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, SHA2Impl);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, init_failure);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, init_success);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, start);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, process);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, end);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, fini);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, digest_size);
    FRIEND_TEST(Test_Vrte_Sec_SHA2Impl, digest);
#endif

protected:

    explicit SHA2Impl(ara::core::String,
                      std::shared_ptr<ara::core::InstanceSpecifier>&);

    virtual ~SHA2Impl();
    SHA2Impl(SHA2Impl const&) = delete;
    SHA2Impl(SHA2Impl     &&) = default;
    SHA2Impl& operator= (SHA2Impl const&) = delete;
    SHA2Impl& operator= (SHA2Impl     &&) = default;

    // interface implementation
    void _init() override;
    void _start() override;
    void _process(const void* data, std::size_t length) override;
    void _end() override;
    void _fini() override;
    void _digest() override;
    size_type _digest_size() override;

private:

    ara::crypto::cryp::HashFunctionCtx::Uptr      ctx_{};
    ara::core::String                             primitive_ {};
    std::shared_ptr<ara::core::InstanceSpecifier> instance_;
};


}    // namespace sec
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_VRTE_SEC_SHA2_IMPL_H_
