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
//* @file        json_parser_interfacee.h
//* @brief       json parser interface header
//*
//* @swcomponent json_parser
//*******************************************************************************/

#ifndef JSON_PARSER_INTERFACE_H_23849784978432
#define JSON_PARSER_INTERFACE_H_23849784978432

#include <cstdint>
#include <stddef.h>

#include "json_input_interface.h"
#include "json_storer_interface.h"
#include "json_types.h"

namespace bosch
{
namespace vrte
{
namespace json
{

/**
 * @brief parser interface
 */

class JsonParserBaseItem;

class JsonParserInterface
{
public:
    /**
     * @brief Factory method for creating the parser. This one will be created from the memory that is given as
     * arguments.
     * @param [in] mem_size : size of the memory the parser uses.
     * @param [in] memory : pointer to that memory
     * @param [in] storer : Storer class that will be used by the returned parser object to store parts of the JSON
     * script.
     * @return nullptr -> not enogug memory, else a pointer to the instance of a parser. The rest of the memory will
     *                    be used by the parser later while parsing.
     */
    static JsonParserInterface*
    create_parser(const size_t mem_size, void* memory, JsonStorerInterface& storer) noexcept;
    /**
     * @brief make destructor virtual
     */
    virtual ~JsonParserInterface() = default;
    /**
     * @brief parser function that parses data from "input" and sends the result of each element to the
     *               "storer" that was defined while creating the parser.
     * @param [in] input object: input, Derivation of "JsomInputInterface".
     * @param [in] max_caller_deepness : maximum caller deepness that should be used while parsing.
     *                                   The parser will stop if the limit is reached.
     *                                   Each bracket ( "[" and "{" ) of the json file
     *                                   will need a value increased by 1.
     * @return JSON_NO_ERROR or some error occurred. See "json_types.h" for more infos-
     */
    virtual JsonError parse(JsonInputInterface& input, const uint32_t max_caller_deepness) noexcept = 0;

    /**
     * @brief get error position of parsed text
     * @param [in] pos : reference to absolute position in text.
     * @param [in] line : reference to line that has error to parse.
     * @param [in] line_position : position in the line.
     * @return true if some error occurred, false if not. References are only updated if return value is true
     */
    virtual bool get_error_position(uint32_t &pos, uint32_t &line, uint32_t &line_position) const noexcept = 0;

    /**
     * @brief get verbose error text for an error code.
     * @param [in] error_code : error code to check.
     * @return pointer to const char pointer that holds the c like string.
     */
    static const char* get_error_text(const JsonError error_code);
    /**
     * @brief overloaded delete operator to prevent of damaging the heap.
     *        The object should be created with "create_parser" that don't use also the heap
     * @param [in] pointer to object.
     */
    void operator delete(void*) {}

    /**
     * @brief Create method for the different items. The first character decides which type
     *        of item will be created
     * @param [in] first_char for object
     * @return pointer ot ther new created item or "nullptr". "nullptr" means that the
     *         parser runs out of memory
     */
    virtual JsonParserBaseItem* create(const char first_char) noexcept = 0;
    /**
     * @brief add extra char on heap for the current item. This works only for the last item that was created on memory.
     *        This function is used to handle vairable length strings.
     * @return "false" -> parser runs out of memory
     */
    virtual bool add_extra_char() noexcept = 0;
    /**
     * @brief reset the pointer of the current memory back to an older value.
     * @param [in] old_memory : old mmeory pointer
     * @return "false" -> old memory is not in the currently used area
     */
    virtual bool set_old_memory(void* old_memory) noexcept = 0;
    /**
     * @brief return the object of type "JsonStorerInterface" that was given to the creator function
     * @return the storer.
     */
    virtual JsonStorerInterface& get_json_storer() noexcept = 0;
    /**
     * @brief helper function that is used in different places to read over whitespaces
     * @param [in] input object: input, Derivation of "JsomInputInterface".
     * @param [in] c : Reference to character that is read. is is only valid if the return
     *                 value of this function is "JSON_NO_ERROR"
     * @return JSON_NO_ERROR or some error occurred. See "json_types.h" for more infos-
     */
    virtual JsonError get_first_char_after_whiterspace(JsonInputInterface& input, char& c) noexcept = 0;
    /**
     * @brief increment and check maximum caller deeppness.
     * @return false -> maximum deepness reached
     */

    virtual bool increment_caller_deepness() noexcept = 0;
    /**
     * @brief decrement and check if caller deeppness still >= 0.
     * @return false -> decement failure
     */
    virtual bool decrement_caller_deepness() noexcept = 0;
};

}
}
}

#endif
