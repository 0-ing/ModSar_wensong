//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Arguments.hpp
/// @brief     Public header of the execution manager for ldr::StringTable
/// @copyright Robert Bosch GmbH  2017
/// @author

#ifndef LDR_ARGUMENTS_HPP_INCLUDED
#define LDR_ARGUMENTS_HPP_INCLUDED

#include "ldr/StringTable.hpp"
#include "ldr/LoaderConfig.hpp"

namespace exm
{
namespace ldr
{
    /// @class Arguments
    /// @brief class responsible to create a derived class  for Arguments based on ldr::StringTable class
    class Arguments
    {
    public:
        /// @brief Constructor
        ///    - passes table pointer to base class
        ///    - Initializes the table to empty strings
        Arguments(){}

        /// @brief destructor
        ~Arguments(){}

        /// @brief No copy constructor needed.
        Arguments(const Arguments&) = delete;

        /// @brief No copy assignment operator needed.
        Arguments& operator=(const Arguments&) = delete;

        /// @brief Adding arguments to the executable
        /// @param[in] string    Argument string
        /// @retval -1   error
        /// @retval 0    succesful
        int32_t add_arg(const char* string)
        {
            return arg_table.add_string(string);
        }

        /// @brief Returns the arguments of an instance
        /// @return     Argument of the instance
        char** get_argv(){ return arg_table.get_ptrtable(); }

        /// @brief Returns the argument count  of an instance
        /// @return     Argument count of the instance
        uint32_t get_argc() const{ return arg_table.get_count(); }

        /// @brief Returns the argument based on index
        /// @param[in]  index    Index of the table
        /// @return     Returns the argument based on the index
        char* get_arg(uint32_t index){ return arg_table.get_string(index); }

    private:
        /// @brief effective maximum number of arguments
        static constexpr uint16_t EFF_ARG_STR_MAX = ARG_STR_MAX+1U; // +1 for argv[0]

        ldr::StringTable<EFF_ARG_STR_MAX, ARG_ENV_SIZE> arg_table;
 };

} /* namespace ldr */
} /* namespace exm */
#endif
