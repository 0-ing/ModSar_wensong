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

#ifndef UCM_AAP_LIBRARY_APP_SEC_HASH_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_HASH_IMPL_H_

#include "ucm/lib/sec/hash.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace sec {


class HashImpl final
    : public lib::sec::Hash
    , virtual protected ucm::mock::Sequence
{
public:
    using size_type = lib::sec::Hash::size_type;

    HashImpl(size_type const&) noexcept {}
    virtual ~HashImpl() = default;

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
