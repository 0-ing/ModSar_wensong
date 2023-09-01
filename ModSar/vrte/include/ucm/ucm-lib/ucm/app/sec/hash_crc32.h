//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/app/sec/hash_crc32.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_sec

#ifndef UCM_AAP_LIBRARY__UCM_APP_SEC__HASH_CRC32_H_
#define UCM_AAP_LIBRARY__UCM_APP_SEC__HASH_CRC32_H_

#include <inttypes.h>

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

/// @class HashCRC32
/// @ingroup bosch_vrte_ucm_app_sec
/// @brief CRC32 implementation.
///

class HashCRC32 final : public lib::sec::Hash
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_sec__HashCRC32, Simple);
#endif

    constexpr static std::size_t hsize = 4;

public:
    using size_type = lib::sec::Hash::size_type;

    explicit HashCRC32();

    HashCRC32(HashCRC32     &&) = default;
    HashCRC32(HashCRC32 const&) = delete;

    HashCRC32& operator=(HashCRC32     &&) = default;
    HashCRC32& operator=(HashCRC32 const&) = delete;

    ~HashCRC32() = default;

protected:
    void _init()                                        override;
    void _start()                                       override;
    void _process(const void* data, std::size_t length) override;
    void _end()                                         override;
    void _digest()                                      override;
    void _fini()                                        override;
    size_type _digest_size()                            override;

private:
    std::uint32_t value_{0};
};


}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_SEC__HASH_CRC32_H_
