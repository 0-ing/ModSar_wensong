//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/cfg/poco_helpers.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_CFG_POCO_HELPERS_H_
#define UCM_AAP_LIBRARY_LIB_CFG_POCO_HELPERS_H_

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wsign-promo"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wstrict-overflow"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#pragma GCC diagnostic pop

#include "ucm/mock/sequence.h"
#include "ucm/lib/types.h"
#include "ucm/lib/swc/version.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace cfg   {

struct PocoHelpers
    : virtual protected ucm::mock::Sequence
{
    PocoHelpers() = default;

    PocoHelpers(PocoHelpers&&) = delete;
    PocoHelpers& operator=(PocoHelpers&&) = delete;

    PocoHelpers(const PocoHelpers&) = delete;
    PocoHelpers& operator=(const PocoHelpers&) = delete;

    ~PocoHelpers() = default;

    template <typename T>
    static bool get(const char*, T&, bool,
                    Poco::JSON::Object::Ptr)
    {
        return pop<bool>();
    }

    static bool get_memaddr(const char*, usize_type&,
                            bool, Poco::JSON::Object::Ptr)
    {
        return pop<bool>();
    }
};

}    // namespace cfg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_CFG_POCO_HELPERS_H_
