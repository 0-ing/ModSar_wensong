//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/app/sec/hash_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_sec

#ifndef UCM_AAP_LIBRARY_APP_SEC_HASH_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_HASH_IMPL_H_

#include "ucm/lib/sec/hash.h"

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

/// @addtogroup bosch_vrte_ucm_app_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace sec   {

/// @class HashImpl
/// @ingroup bosch_vrte_ucm_app_sec
/// @brief Hash calculation implementation.
///

class HashImpl final : public lib::sec::Hash
{
#if defined(GOOGLE_TEST)
    friend class HashImplUt;
#endif

public:
    using size_type = lib::sec::Hash::size_type;

    HashImpl(size_type const&) noexcept;
    virtual ~HashImpl();

protected:
    void _init()                                        override;
    void _start()                                       override;
    void _process(const void* data, std::size_t length) override;
    void _end()                                         override;
    void _digest()                                      override;
    void _fini()                                        override;
    size_type _digest_size()                            override;

private:
    size_type hsize_{};

};


}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY_APP_SEC_HASH_IMPL_H_
