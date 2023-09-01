//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Defs.hpp
/// @brief     Header file for the typedefs
/// @copyright Robert Bosch GmbH  2017
/// @author

#ifndef LDR_DEFS_HPP_INCLUDED
#define LDR_DEFS_HPP_INCLUDED

#include <stdint.h>

namespace exm
{
namespace ldr
{
    typedef int32_t id_t;                    ///< @brief type to hold exe and instance id 
    static constexpr id_t INVALID_ID = -1;   ///< @brief if id_t type is not valid or < 0 INVALID_ID should be returned 
} /* namespace ldr */
} /* namespace exm */
#endif /*! End of DEFS_HPP */
