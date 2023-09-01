//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      LoaderDependency.hpp
/// @brief     Public header of the execution manager for Dependency class
/// @copyright Robert Bosch GmbH  2017
/// @author

#ifndef LDR_DEPENDENCY_HPP_INCLUDED
#define LDR_DEPENDENCY_HPP_INCLUDED

#include <stdint.h>
#include "ldr/LoaderConfig.hpp"
#include "ldr/Defs.hpp"

namespace exm
{
namespace ldr
{

    /// @brief Class describing a dependency
    class Dependency
    {
        public:

            /// @brief Types of dependencies.
            enum class Type: uint8_t
            {
                RUNNING = 0, ///< @brief RUNNING dependency: means that a Process will be started, only when its RUNNING dependencies reported running. 
                TERMINATED   ///< @brief TERMINATED dependency: means that a Process will be started, only when its TERMINATED dependencies are terminated. 
            };

            Dependency();

            ~Dependency();

            /// @brief No copy constructor needed.
            Dependency(const Dependency&) = delete;

            /// @brief No copy assignment operator needed.
            Dependency& operator=(const Dependency&) = delete;

            /// @brief Initialize the dependency.
            /// The name must be non empty. The type mus be different than NO_DEPENDENCY.
            /// @param id_ Name of the executbale ID.
            /// @param type_ Type of the dependency.
            /// @return Sucess:0<BR> Failure:-1
            int8_t init( const id_t id_, Dependency::Type type_ );

            /// @brief Get the dependency type 
            /// @return Returns the dependency type
            Type get_type() { return type; }

            /// @brief Get the dependency instance object 
            /// @return Returns dependency instance object 
            id_t get_id() { return id; }

        private:
            /// @brief Dependency name 
            id_t id;

            /// @brief Dependency type 
            Type type;
    };
} /* namespace ldr */
} /* namespace exm */
#endif
