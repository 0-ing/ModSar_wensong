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
//* @file        json_input_istream.h
//* @brief       example json input stream implementation with "std::istream"
//*
//* @swcomponent json_parser
//*******************************************************************************/

#ifndef JSON_INPUT_ISTREAM_H_23849784978432
#define JSON_INPUT_ISTREAM_H_23849784978432

#include <istream>

#include "json_input_interface.h"

namespace bosch
{
namespace vrte
{
namespace json
{

/**
 * @brief class for input from STL "ifstream"
 */

class JsonInputIStream final : public JsonInputInterface
{
public:
    /**
     * @brief constructor
     */
    JsonInputIStream(std::istream& istream) : m_istream(istream)
    {
        std::noskipws(m_istream);    // no skipping of whitespace !!
    }
    /**
     * @brief Method that implements the internal function for getting a character.
     * @param [in] c : Reference to character.
     * @return "true" if the character "c" is valid, false if the stream ends or an error occurred
     */
    virtual bool getc_implementation(char& c) noexcept override
    {
        try
        {
            if (m_istream.get(c))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        catch (...)
        {
            return false;
        }
    }

private:
    /**
     * @brief STL stream for input
     */
    std::istream& m_istream;
};

}
}
}

#endif
