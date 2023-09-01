//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/doxygen.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB__DOXYGEN_H_
#define UCM_AAP_LIBRARY__UCM_LIB__DOXYGEN_H_

namespace bosch {
namespace vrte  {
namespace ucm   {

/// @addtogroup bosch_vrte_ucm_lib
/// @{
///
/// @page UCM Core API library
///
/// The UCM Core API library defines a set of components which are used
/// across the implementation. They either implement a common for UCM
/// functionality or define API which define the required for UCM to operate
/// behaviour.
/// It is only possible to modify aspects of UCM behaviour (variation points) by
/// implementing the components defined by the APIs in the core library.

/// @namespace bosch::vrte::ucm::lib
/// @brief UCM Core API library
namespace lib {

/// @defgroup bosch_vrte_ucm_lib_app UCM application modules and life-cycle
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_arc Archive processing service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_buf Flexible buffers
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_cfg Configuration Management
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_com Communication service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_dev Memory layout and device drivers API
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_exm EXM service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_log Logging service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_pkg Software Package processing API
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_ppl Processing pipeline service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_sec UCM Security service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_stm STM service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_swc Software cluster management service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_sys OS interface component
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_upd Package update service
/// @ingroup  bosch_vrte_ucm_lib

/// @defgroup bosch_vrte_ucm_lib_utl Utility components
/// @ingroup  bosch_vrte_ucm_lib
///

}

/// @}

}   // namespace ucm
}   // namespace vrte
}   // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB__DOXYGEN_H_
