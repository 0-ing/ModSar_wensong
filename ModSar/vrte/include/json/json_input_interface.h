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
//* @file        json_input_interface.h
//* @brief       json input inteface header
//*
//* @swcomponent json_parser
//*******************************************************************************/

#ifndef JSON_INPUT_INTERFACE_H_23849784978432
#define JSON_INPUT_INTERFACE_H_23849784978432

namespace bosch
{
namespace vrte
{
namespace json
{

/**
 * @brief Interface class for input
 */

class JsonInputInterface
{
public:
    /**
     * @brief constructor
     */
    JsonInputInterface() : m_take_lastchar(false), m_block_forever(false), m_get_called_before(false),
            m_pos(0U),  m_line(1U), m_linepos(0U) {}
    /**
     * @brief make destructor virtual
     */
    virtual ~JsonInputInterface() = default;
    /**
     * @brief Method that has to be overloaded for input.
     * @param [in] c : Reference to character that is read.
     * @return "true" if the character "c" is valid, false if the stream ends or an error occurred
     */
    virtual bool getc_implementation(char& c) noexcept = 0;
    /**
     * @brief Method that handles the read again mechanism. This mechanism is generic
     */
    inline bool get(char& c) noexcept
    {
        m_get_called_before = true;
        if (m_block_forever)
        {
            // an fatal error before has blocked this input stream
            return false;
        }
        if (m_take_lastchar)
        {
            m_take_lastchar = false;
        }
        else
        {
            m_take_lastchar = 0;
            if (!getc_implementation(m_lastchar))
            {
                c = 0;
                return false;
            }
            else
            {
                saturated_increment(m_pos);
                if (m_lastchar == '\n')
                {
                    saturated_increment(m_line);
                    m_linepos = 0;
                }
                else
                {
                    saturated_increment(m_linepos);
                }
            }
        }
        c = m_lastchar;
        return true;
    }
    /**
     * @brief  Method needed for the read again mechanism. If this function is called twice
     *         without "get" inbetween than this "JsonInputInterface" will go to unusable state.
     *         This cannot happen because of the incoming data stream, but only for an error in the
     *         parser implementation
     */
    inline void unget() noexcept
    {
        if (m_take_lastchar || (!m_get_called_before))
        {
            m_block_forever = true; // fatal, should never happen, so any transfer at this point is blocked
        }
        m_take_lastchar = true;
    }

    /**
     * @brief Method to get current position of parsed text
     */
    inline uint32_t get_position() const noexcept { return m_pos; }

    /**
     * @brief Method to get current line of parsed text
     */

    inline uint32_t get_line() const noexcept { return m_line; }

    /**
     * @brief Method to get current position in the line of parsed text
     */

    inline uint32_t get_line_position() const noexcept { return m_linepos; }

    /**
     * @brief Method to reset to default state of the input interface, neccesary for reuse
     */

    inline void reset_to_defaults() noexcept
    {
        m_take_lastchar = false;
        m_block_forever = false;
        m_get_called_before = false;
        m_pos = 0U;
        m_line = 1U;
        m_linepos = 0U;
    }
private:
    /**
     * @brief Method for incrementing a value only if it is < UINT32_MAX,
     *        else stay at value UINT32_MAX
     * @param [in] value : value for saturated increment.
     */

    inline static void saturated_increment(uint32_t &value)
    {
        if (value < UINT32_MAX)
        {
            ++value;
        }
    }
    /**
     * @brief boolean value; "true" -> "getc_implementation" will not be called from "getc".
     *                       Instead, "m_lastchar" will be returned.
     */
    bool m_take_lastchar;
    /**
     * @brief boolean value; "true" -> "getc" will always return "false".
     */
    bool m_block_forever;
    /**
     * @brief boolean value; This is used to check if the "unget" function is the first method called from this object.
     *                       This
     */
    bool m_get_called_before;
    /**
     * @brief Last character that was read.
     */

    char m_lastchar;

    /**
     * @brief position byte that was read.
     */

    uint32_t m_pos;

    /**
     * @brief line that was read.
     */

    uint32_t m_line;

    /**
     * @brief position byte in line that was read.
     */

    uint32_t m_linepos;
};

}
}
}

#endif
