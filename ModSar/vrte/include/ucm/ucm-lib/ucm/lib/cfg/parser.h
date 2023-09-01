//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/cfg/parser.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_CFG_PARSER_H_
#define UCM_AAP_LIBRARY_LIB_CFG_PARSER_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#if defined(JSON_PARSER_POCO)
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
#include <Poco/JSON/Object.h>
#pragma GCC diagnostic pop
#else // defined(JSON_PARSER_POCO)
#error Parser backend not set!
#endif

#include "ucm/lib/cfg/table.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace cfg {

class Parser
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ConfigParser, Simple);
#endif

public:
    virtual ~Parser() = default;

#if defined(JSON_PARSER_POCO)
    virtual bool parse(Table&, Poco::JSON::Object::Ptr) = 0;
#endif

protected:
    Parser() = default;

    Parser(Parser&&) noexcept = default;
    Parser& operator=(Parser&&) = default;

    Parser(const Parser&) = default;
    Parser& operator=(const Parser&) = default;
};

}    // namespace cfg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_CFG_PARSER_H_
