//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         Poco/JSON/parser.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Ashwin Kumar
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_POCO_JSON_PARSER_H_
#define UCM_AAP_LIBRARY_POCO_JSON_PARSER_H_


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
#pragma GCC diagnostic pop

#include <fstream>
#include "ucm/lib/cfg/poco_helpers.h"
#include "ucm/lib/cfg/table.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Array.h"

namespace Poco {
namespace JSON {

class Parser
{
public:
    virtual ~Parser() = default;

    Parser() = default;

    Dynamic::Var parse(const std::string& json);

    Dynamic::Var parse(std::istream& in);

protected:


    Parser(Parser&&) noexcept = default;
    Parser& operator=(Parser&&) = default;

    Parser(const Parser&) = default;
    Parser& operator=(const Parser&) = default;
};


inline Dynamic::Var Parser::parse(const std::string& json)
{
    Dynamic::Var Var_C;
    (void) (json);
    return Var_C;
}


inline Dynamic::Var Parser::parse(std::istream& in)
{
     Dynamic::Var Var_C;
     (void) (in);
     return Var_C;
}

}    // namespace JSON
}    // namespace Poco


#endif // UCM_AAP_LIBRARY_POCO_JSON_PARSER_H_
