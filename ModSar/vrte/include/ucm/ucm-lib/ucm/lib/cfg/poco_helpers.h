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
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"
#pragma GCC diagnostic pop

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/swc/version.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace cfg {

struct PocoHelpers
{
    PocoHelpers() = default;

    PocoHelpers(PocoHelpers&&) = delete;
    PocoHelpers& operator=(PocoHelpers&&) = delete;

    PocoHelpers(const PocoHelpers&) = delete;
    PocoHelpers& operator=(const PocoHelpers&) = delete;

    ~PocoHelpers() = default;

    template <typename T>
    static bool get(const char* key, T& value, bool required,
                    Poco::JSON::Object::Ptr json)
    {
        using namespace Poco::JSON;
        using namespace Poco::Dynamic;

        if (!json->has(key)) {
            if (not required)
                return false;
            std::string msg{"'" + std::string{key} + "' is missing from JSON"};
            throw std::runtime_error(msg);
        }
        else if (json->isObject(key)) {
            Var var = json->get(key);
            value = var.extract<Object::Ptr>()->getValue<T>("value");
        }
        else {
            value = json->getValue<T>(key);
        }
        return true;
    }

    static bool get_memaddr(const char* key, usize_type& value,
                            bool required, Poco::JSON::Object::Ptr json);

};

}    // namespace cfg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_CFG_POCO_HELPERS_H_
