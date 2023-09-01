// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------
/**
 * @file
 */

#ifndef ARA_EXEC_FUNCTION_GROUP_STATE_H_
#define ARA_EXEC_FUNCTION_GROUP_STATE_H_

#include "ara/core/result.h"
#include "ara/core/string_view.h"
#include "ara/exec/exec_error_domain.h"

namespace ara
{
namespace exec
{

/**
 * @brief Class representing Function Group State defined in meta-model (ARXML).
 * @note Once created based on ARXML path, it's internal value stay bounded to it for entire lifetime of an object.
 *
 * @traceid{SWS_EM_02269}@tracestatus{draft}
 * @uptrace{RS_EM_00101}
 */
class FunctionGroupState final
{

public:
    /**
     * @brief Default constructor.
     * @note Default constructor is deleted in favour of named constructor (Create).
     *
     * @traceid{SWS_EM_02324}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroupState ()=delete;

    /// @brief Constructor 
    FunctionGroupState (ara::core::String short_name_fg, ara::core::String short_name_state);

    /**
     * @brief Copy constructor.
     * @note To prevent problems with resource allocations during copy operation, this class is non-copyable.
     *
     * @traceid{SWS_EM_02325}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroupState (const FunctionGroupState &other)=delete;

    /**
     * @brief Named constructor for FunctionGroupState. 
     * 
     * This method shall validate/verify meta-model path passed and perform FunctionGroupState
     * object creation.
     *
     * @param functionGroup the Function Group instance the state shall be connected with.
     * @param metaModelIdentifier stringified meta model identifier (short name path) where path separator is '/'.
     * @returns an instance of FunctionGroupState, or ExecError Domain error.
     * @error ara::exec::ExecErrc::kMetaModelError if metaModelIdentifier passed is incorrect (e.g. FunctionGroup identifier has been passed).
     * @error ara::exec::ExecErrc::kGeneralError if any other error occurs.
     * @threadsafety{Thread-safe}
     *
     * @traceid{SWS_EM_02326}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    static ara::core::Result<FunctionGroupState> Create (const FunctionGroup &functionGroup, ara::core::StringView metaModelIdentifier) noexcept;

    /**
     * @brief Move constructor
     *
     * @traceid{SWS_EM_02331}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroupState (FunctionGroupState &&other) noexcept;

    /**
     * @brief Destructor of the FunctionGroup instance.
     *
     * @traceid{SWS_EM_02272}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    ~FunctionGroupState () noexcept;

    /**
     * @brief Copy assignment operator.
     * @note To prevent problems with resource allocations during copy operation, this class is non-copyable
     *
     * @traceid{SWS_EM_02330}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroupState& operator= (const FunctionGroupState &other)=delete;

    /**
     * @brief Move assignment operator.
     *
     * @traceid{SWS_EM_02332}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroupState& operator= (FunctionGroupState &&other) noexcept;

    /**
     * @brief eq operator to compare with other FunctionGroupState instance.
     * @param other FunctionGroupState instance to compare this one with.
     * @return true in case both FunctionGroupStates are representing exactly the same meta-model element, false otherwise.
     * @threadsafety{Thread-safe}
     *
     * @traceid{SWS_EM_02273}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    bool operator== (const FunctionGroupState &other) const noexcept;
   
    /** 
     * @brief uneq operator to compare with other FunctionGroupState instance.
     * @param other FunctionGroupState instance to compare this one with.
     * @return false in case both FunctionGroupStates are representing exactly the same meta-model element, true otherwise.
     * @threadsafety{Thread-safe}
     *
     * @traceid{SWS_EM_02274}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    bool operator!= (const FunctionGroupState &other) const noexcept;

    ara::core::String short_name_fg;
    ara::core::String short_name_state;
};

} /* namespace exec */
} /* namespace ara */

#endif
