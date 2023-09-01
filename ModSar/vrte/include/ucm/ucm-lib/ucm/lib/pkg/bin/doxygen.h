//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/bin/doxygen.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__DOXYGEN_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__DOXYGEN_H_

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {

/// @addtogroup bosch_vrte_ucm_lib_pkg_bin
/// @{

/// @defgroup bosch_vrte_ucm_lib_pkg_bin__ut UT scripts for the component.
/// @ingroup  bosch_vrte_ucm_lib_pkg_bin


/// @page bosch_vrte_ucm_lib_pkg_bin_README Binary software package processing
///
/// The binary software package (SWP) processing and composition API covers all
/// the functionality required to handle a binary software package.\n
/// The design of this component provides the following functionality:
/// - Allows for concurrent operations.
/// - Provides mechanisms for processing a software package from a file.
/// - Provides mechanisms for processing a software package from a stream.
/// - Provides an optional sample implementation of SWP composer.
/// - Supports for multiple variations of the accepted binary SWP format.
/// - Works with the internal UCM memory buffers for flexibility.
/// - The memory pressure on the system is reduced to minimum.
///
/// The binary SWP processing and composition API exposes several API classes
/// which model its behaviour.
/// - @ref bosch::vrte::ucm::lib::pkg::bin::Handle "Handle"
///   @copybrief bosch::vrte::ucm::lib::pkg::bin::Handle
/// - @ref bosch::vrte::ucm::lib::pkg::bin::SWP_Process "SWP processor"
///   @copybrief bosch::vrte::ucm::lib::pkg::bin::SWP_Process
/// - Optional @ref bosch::vrte::ucm::lib::pkg::bin::SWP_Compose "SWP composer"
///   @copybrief bosch::vrte::ucm::lib::pkg::bin::SWP_Compose
///

/// @namespace bosch::vrte::lib::pkg::bin
/// @brief Binary software package processing
namespace bin {
/// @namespace bosch::vrte::lib::pkg::bin::test
/// @brief Binary software package processing - UT
namespace test {}
}

}   // namespace pkg
}   // namespace lib
}   // namespace ucm
}   // namespace vrte
}   // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__DOXYGEN_H_
