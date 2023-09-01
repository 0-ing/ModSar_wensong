//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/lib/sec/hash_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_SEC_HASH_FACTORY_H_
#define UCM_AAP_LIBRARY_LIB_SEC_HASH_FACTORY_H_

#include <memory>
#include <string>

#include "ucm/mock/sequence.h"
#include "ucm/lib/sec/hash.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sec   {

class HashFactory : virtual protected ucm::mock::Sequence
{
public:
    virtual ~HashFactory() = default;
    virtual std::unique_ptr<Hash> create(std::string const&)
    {
        return pop<std::unique_ptr<Hash>&&>();
    }

protected:
    HashFactory() = default;
    HashFactory(HashFactory const&)            = default;
    HashFactory(HashFactory     &&) noexcept   = default;
    HashFactory& operator=(HashFactory const&) = default;
    HashFactory& operator=(HashFactory     &&) = default;
};

}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SEC_HASH_FACTORY_H_
