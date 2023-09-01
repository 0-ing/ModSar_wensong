//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file initialization.h
/// @brief global initialization and shutdown functions that initialize resp. deinitialize data structures and threads
/// of the AUTOSAR Runtime for Adaptive Applications.
//==========================================================================================================

#ifndef ARA_CORE_INITIALIZATION_H_
#define ARA_CORE_INITIALIZATION_H_

#include "ara/core/string.h"
#include "ara/core/result.h"
#include "ara/core/set.h"

// Shared objects that shall be initialized/deinitialized are supposed to offer functions with the following signatures:
// extern "C" void ara_core_fcinit(
//      ara::core::Map<ara::core::String, bool> *loaded,
//      ara::core::Result<ara::core::InitializationStatus> *result);
// extern "C" void ara_core_fcdeinit(
//      ara::core::Result<ara::core::InitializationStatus> *result);

namespace ara {
namespace core {

enum InitializationStatus { DONE, DEP_NEEDED };

/// @brief An enumeration with errors that can occur within the ara::core Initialization
///
/// These error codes do not belong to an error domain
enum CoreInitErrc : ErrorDomain::SupportDataType {
    kInitializationFuncError = 2000,       ///< error in so initialization function
    kInitDependencyResolutionError = 2001, ///< error while resolving dependencies (i.e. circular dependencies)
    kInitDlIterateCallbackError = 2002,    ///< error while searching for init functions (dl_iterate_phdr)
    kInitDeinitNotFound = 2003,            ///< found only init, but not deinit symbol
};

using InitializationFunc
    = void (*)(ara::core::Set<ara::core::String>*, ara::core::Result<ara::core::InitializationStatus>*);
using DeinitializationFunc = void (*)(ara::core::Result<void>*);

/**
 * @brief Initializes data structures and threads of the AUTOSAR Adaptive
 *        Runtime for Applications.
 *
 * Prior to this call, no interaction with the ARA is possible.
 * This call must be made inside of main(), i.e., in a place where it is
 * guaranteed that static memory initialization has completed.
 * Depending on the individual functional cluster specification, the
 * calling application may have to provide additional configuration data
 * (e.g., set an Application ID for Logging) or make additional initialization
 * calls (e.g., start a FindService in ara::com) before other API calls to the respective functional cluster can be
 * made. Such calls must be made *after* the call to Initialize(). Calls to ARA APIs made before static initialization
 * has completed lead to undefined behavior. Calls made after static initialization has completed but before
 * Initialize() was called will be rejected by the functional cluster
 * implementation with an error or, if no error to be reported is defined,
 * lead to undefined behavior.
 *
 * @returns A Result object that indicates whether the AUTOSAR Adaptive
 *         Runtime for Applications was successfully
 *         initialized. Note that this is the only way for the
 *         ARA to report an error that is guaranteed to be available, e.g.,
 *         in case ara::log failed to correctly initialize. The user is not
 *         expected to be able to recover from such an error. However, the
 *         user may have a project-specific way of recording errors during
 *         initialization without ara::log.
 *
 * @traceid{SWS_CORE_10001}
 */
Result<void> Initialize() noexcept;

/**
 * @brief Destroy all data structures and threads of the AUTOSAR Adaptive
 *        Runtime for Applications.
 *
 * After this call, no interaction with the ARA is possible.
 * This call must be made inside of main(), i.e., in a place where it is
 * guaranteed that the static initialization has completed and destruction
 * of statically initialized data has not yet started.
 * Calls made to ARA APIs after a call to ara::core::Deinitialize() but before destruction of statically initialized
 * data will be rejected with an error or, if no error is defined, lead to undefined behavior. Calls made to ARA APIs
 * after the destruction of statically initialized data will lead to undefined behavior.
 *
 * @returns A Result object that indicates whether the ARA was successfully
 *         destroyed. Typical error cases to be reported here are that the
 *         user is still holding some resource inside the ARA.
 *         Note that this Result is the only way for the
 *         ARA to report an error that is guaranteed to be available, e.g.,
 *         in case ara::log has already been de-initialized. The user is not
 *         expected to be able to recover from such an error. However, the
 *         user may have a project-specific way of recording errors during
 *         deinitialization without ara::log.
 *
 * @traceid{SWS_CORE_10002}
 */
Result<void> Deinitialize() noexcept;

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_INITIALIZATION_H_
