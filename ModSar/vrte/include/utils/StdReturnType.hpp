//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      StdReturnType.hpp
/// @brief     Type Definition: StdReturnType
/// @copyright Robert Bosch GmbH  2018
/// @author    Jyothi Kuntegowda

#ifndef UTILS_STDRETURNTYPE_HPP_INCLUDED
#define UTILS_STDRETURNTYPE_HPP_INCLUDED

#include <stdint.h>

namespace exm
{

/// @brief    Representation of Standard Return Type
enum class StdReturnType : uint8_t
{
    OK = 0,                 ///<  Return Success
    GENERAL_ERROR,          ///<  Return General Error
    FATAL_ERROR,            ///<  Fatal error occurred
    TIMEOUT,                ///<  Return Timeout
    INSUFFICIENT_RESOURCES, ///<  Resource not available
    INVALID_ARGUMENTS,      ///<  Some argument is invalid
    INVALID_STATE,          ///<  Some state is invalid
    NOT_APPLICABLE          ///<  Returned parameters can be ignored
};

} // namespace exm

#endif
