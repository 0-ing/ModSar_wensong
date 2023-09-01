//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================


/// @file      EnVariables.hpp
/// @brief     class responsible to create a derived class EnvVars based on ldr::StringTable class
/// @copyright Robert Bosch GmbH  2017
/// @author

#ifndef LDR_ENVVARS_HPP_INCLUDED
#define LDR_ENVVARS_HPP_INCLUDED

#include "ldr/StringTable.hpp"
#include "ldr/LoaderConfig.hpp"

namespace exm
{
namespace ldr
{

    /// @class EnvVars
    /// @brief class responsible to create a derived class EnvVars based on ldr::StringTable class
    class EnvVars
    {
    public:
        /// @brief Constructor
        ///    - passes table pointer to base class
        ///    - Initializes the table to empty strings
        EnvVars(){}

        /// @brief destructor
        ~EnvVars(){}

        /// @brief No copy constructor needed.
        EnvVars(const EnvVars&) = delete;

        /// @brief No copy assignment operator needed.
        EnvVars& operator=(const EnvVars&) = delete;

        /// @brief Adding Environment variables to the executable
        /// @param[in] string    Environment variable string
        /// @retval -1   error
        /// @retval 0    succesful
        int32_t add_env(const char* string)
        {
            return envvar_table.add_string(string);
        }

        /// @brief Returns the the env variables of an instance
        /// @return Environment variables of an instance
        char** get_envp(){ return envvar_table.get_ptrtable(); }

        /// @brief Returns the env count  of an instance
        /// @return Number of environment variables
        uint32_t get_envcount() const { return envvar_table.get_count(); }

        /// @brief Returns the env variable based on index
        /// @param[in]  index    Index of the table
        /// @return     Returns the environment variable based on the index
        char* get_env(uint32_t index) { return envvar_table.get_string(index); }

    private:
        /// @brief effective maximum number of arguments
        ldr::StringTable<ENV_STR_MAX, ARG_ENV_SIZE> envvar_table;
    };
} /* namespace ldr */
} /* namespace exm */
#endif
