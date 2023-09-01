//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      StringTable.hpp
/// @brief     Public header of the execution manager for StringTable
/// @author

#ifndef LDR_STRINGTABLE_HPP_INCLUDED
#define LDR_STRINGTABLE_HPP_INCLUDED

#include "ldr/LoaderConfig.hpp"
#include "log/Debug.hpp"
#include <stdint.h>

#include "utils/c/string.hpp"    //wrapper to prevent direct inclusion of libc headers

namespace exm
{
namespace ldr
{

    /// @class StringTable
    ///  @brief class responsible to create a base class for Arguments and Environment variables
    template<uint32_t N_OF_STRINGS, uint32_t STRING_SIZE>
    class StringTable
    {
        public:
            /// @brief Default Constructor
            StringTable():
                table(), ptrtable(), count(0U)
            {
                for(uint32_t i=0U; i<N_OF_STRINGS; i++)
                {
                    table[i][0] = '\0';
                    ptrtable[i] = nullptr;
                }
                ptrtable[N_OF_STRINGS] = nullptr;
            }

            /// @brief Default Destructor
            ~StringTable()
            {
            }

            /// @brief prevent copy construction
            /// @private
            StringTable(const StringTable &other) = delete;

            /// @brief prevent copy assignment
            /// @private
            StringTable& operator=(const StringTable& other) = delete;

            /// @brief Adding arguments to the executable
            /// @param[in]  string  String that is to be added
            /// @return 0 for success
            /// @return -1 fir failure
            int32_t add_string(const char* string)
            {

                size_t len = strnlen(string, STRING_SIZE+1U); /* SIZE+1 to ensure user does not pass string larger than SIZE */

                /* Check if empty string passed */
                if(count >= N_OF_STRINGS)
                {
                    return -1;
                }
                /* Check if empty string passed */
                if(0U == len)
                {
                    return -1;
                }
                /* check if the string is too large  */
                if(len > STRING_SIZE)
                {
                    return -1;
                }

                /* adding string to the table and updating the ptrtable */
                char* addr = table[count];
                DEBUG_INFO_F("addr=%p, string=%p", addr, string); // PRQA S 3842 # Macro is mapped to certified QNX API that is expected to check for NULL-pointer and end of string delimiter.
                (void)strncpy( addr, string, STRING_SIZE+1U); /* SIZE+1 for \0 */
                ptrtable[count] = addr;
                count++;

                return 0;
            }

            /// @brief Returns the argument count  of an instance
            /// @return Argument count of an instance
            uint32_t get_count() const { return count; }
            /// @brief Returns the array of pointers that hold addresses of strings from the table
            /// @return Array of pointers that hold the addresses of strings
            char** get_ptrtable() {return ptrtable; }
            /// @brief Returns a particular string from the table
            /// @param index Array index of the string table
            /// @return String from the string table
            char* get_string(uint32_t index){ return table[index]; }

        private:
            /// @brief String table to hold the arguments
            char table[N_OF_STRINGS][STRING_SIZE+1U];  /* +1 for \0 */

            /// @brief array of pointers to hold addresses of strings from the table
            char* ptrtable[N_OF_STRINGS+1U];  /* +1 for NULL termination */
            uint32_t count;                                                         ///< @brief to hold number of argument each instance holds
    };
} /* namespace utils */
} /* namespace exm */
#endif
