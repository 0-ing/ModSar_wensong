//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         src/ucm/app/sec/hash_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_APP_SEC_HASH_FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY_APP_SEC_HASH_FACTORY_IMPL_H_

#include "ucm/lib/sec/hash_factory.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace app {
namespace sec {

class HashFactoryImpl final
    : public lib::sec::HashFactory
    , virtual protected ucm::mock::Sequence
{
public:
    std::unique_ptr<lib::sec::Hash> create(std::string const&) override
    {
    	lib::sec::Hash* ptr = pop<lib::sec::Hash*>();
    	return std::unique_ptr<lib::sec::Hash>(ptr);
    }
};

}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_APP_SEC_HASH_FACTORY_IMPL_H_
