//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ISecurityPolicy.hpp
/// @brief     Security Policy interface, class definition
/// @copyright Robert Bosch GmbH  2018
/// @author    Arnaud Riess

#ifndef UTILS_ISECURITYPOLICY_HPP_INCLUDED
#define UTILS_ISECURITYPOLICY_HPP_INCLUDED

#include "utils/IMutex.hpp"
#include "utils/StdReturnType.hpp"

namespace exm
{
namespace utils
{

/// @brief Security Policy interface
class ISecurityPolicy
{
public:
    /// @brief destructor
    virtual ~ISecurityPolicy() {
    } // Not covered: Deleting destructors of pure virtual base classes can not be called.

    /// @brief Get the security policy type id by name
    /// @param fd_guard guard for safe and secure file descriptor handling
    /// @param secpolname Name of the secpol to translate
    /// @param type_id Output parameter for the type id
    /// @return StdReturnType::OK if the translation was successful. All other values: the
    /// translation was not successful. type_id is invalid.
    virtual StdReturnType
    getQNXSecpol(utils::IMutex& fd_guard, const char* secpolname, uint32_t& type_id)
        = 0;
};

} /* namespace utils */
} /* namespace exm */
#endif
