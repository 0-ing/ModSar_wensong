//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file   Loader.hpp
/// @brief  Declaration of api getLoaderControl()
//=============================================================================

#ifndef _LDR_LOADER_HPP_
#define _LDR_LOADER_HPP_

#include "ldr/ILoaderControl.hpp"

namespace exm {
namespace ldr {

/// @brief get reference to global loader object
/// @return ILoaderControl Reference to global loader object
extern ILoaderControl& getLoaderControl();

} /* namespace */
} /* namespace */

#endif /* header include protection */
