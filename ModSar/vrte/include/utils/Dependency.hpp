//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Dependency.hpp
/// @brief     Define Dependency class and DependecyType
/// @author    Avnish Kasbi

#ifndef UTILS_DEPENDENCY_HPP_INCLUDED
#define UTILS_DEPENDENCY_HPP_INCLUDED

#include "PrimaryConfig.hpp"

namespace exm
{
namespace utils
{

/// @brief Enum Class to define the states of a dependency
enum class DependencyType : uint8_t
{
    RUNNING = 0, ///< Dependency that Application in Running state
    TERMINATED   ///< Dependency that Application in Terminated state
};


/// @brief Application Dependency class
template<typename AttrType>
class Dependency
{
public:
    Dependency() = delete;

    /// @brief Constructor
    /// @param[in]  app_    Application Instance ID
    /// @param[in]  type_   Dependency type
    Dependency(AttrType app_, DependencyType type_)
        : app(app_), type(type_) {}

    ///@brief Application Attribute type
    AttrType app;
    ///@brief Dependency type
    DependencyType type;
};

} // namespace utils
} // namespace exm

#endif // UTILS_DEPENDENCY_HPP_INCLUDED
