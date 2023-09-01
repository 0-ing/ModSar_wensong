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

#ifndef UCM_AAP_LIBRARY__UCM_APP_SEC__HASH_CRC32_H_
#define UCM_AAP_LIBRARY__UCM_APP_SEC__HASH_CRC32_H_

#include <inttypes.h>

#include "ucm/mock/sequence.h"

#include "ucm/lib/sec/hash.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace sec   {


class HashCRC32 final
    : public lib::sec::Hash
    , virtual protected ucm::mock::Sequence
{
public:
    using size_type = std::size_t;

    explicit HashCRC32() = default;

    HashCRC32(HashCRC32     &&) = default;
    HashCRC32(HashCRC32 const&) = default;

    HashCRC32& operator=(HashCRC32     &&) = default;
    HashCRC32& operator=(HashCRC32 const&) = default;

    ~HashCRC32() = default;

protected:
    void _init()                            override { return pop<void>(); }
    void _start()                           override { return pop<void>(); }
    void _process(const void*, std::size_t) override { return pop<void>(); }
    void _end()                             override { return pop<void>(); }
    void _digest()                          override { return pop<void>(); }
    void _fini()                            override { return pop<void>(); }
    size_type _digest_size()                override { return pop<size_type>(); }
};


}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_APP_SEC_HASH_IMPL_H_
