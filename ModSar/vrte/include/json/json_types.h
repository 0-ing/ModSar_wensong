//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

//******************************************************************************
//* @file        json_types.h
//* @brief       json types header
//*
//* @swcomponent json_parser
//*******************************************************************************/

#ifndef JSON_TYPES_H_23849784978432
#define JSON_TYPES_H_23849784978432

namespace bosch
{
namespace vrte
{
namespace json
{

/**
 * @brief Error Codes that can be returnted if some error occurs.
 */

enum JsonError
{
    JSON_NO_ERROR = 0,  /**< No error. */
    JSON_OUT_OF_MEMORY, /**< Out of Memory while parsing. */
    JSON_PARSE_ERROR,   /**< The input fits not the JSON grammar. */
    JSON_CALL_ERROR,    /**< More recursive calles than parameterized are in the input. */
    JSON_STORER_ERROR,  /**< Storer reports an error, pasring was aborted. */
    JSON_MEMORY_ERROR   /**< Memory corruption. This means that something strange happened or an implementation bug. */
};

}
}
}

#endif
