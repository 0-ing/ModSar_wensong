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

#ifndef ARA_EXEC_FUNCTION_GROUP_H_
#define ARA_EXEC_FUNCTION_GROUP_H_

#include "ara/core/result.h"
#include "ara/core/string_view.h"
#include "ara/exec/exec_error_domain.h"

namespace ara
{
namespace exec
{

/**
 * @brief Class representing Function Group defined in meta-model (ARXML).
 * @note Once created based on ARXML path, it's internal value stay bounded to it for entire lifetime of an object.
 *
 * @traceid{SWS_EM_02263}@tracestatus{draft}
 * @uptrace{RS_EM_00101}
 */
class FunctionGroup final
{
public:

    /**
    * @brief Named constructor for FunctionGroup. This method shall validate/verify meta-model path passed and perform FunctionGroup object creation.
    
    * @param metaModelIdentifier stringified meta model identifier (short name path) where path separator is '/'.
    * @returns an instance of FunctionGroup, or ExecErrc error
    * @error ara::exec::ExecErrc::kMetaModelError if metaModelIdentifier passed is incorrect (e.g. FunctionGroupState identifier has been passed).
    * @error ara::exec::ExecErrc::kGeneralError if any other error occurs.
    * @threadsafety{Thread-safe}
     
    * @traceid{SWS_EM_02323}@tracestatus{draft}
    * @uptrace{RS_EM_00101}
    */
    static ara::core::Result<FunctionGroup> Create (ara::core::StringView metaModelIdentifier) noexcept;

     /**
     * @brief Default constructor.
     * @note Default constructor is deleted in favour of named constructor (Create).
     *
     * @traceid{SWS_EM_02321}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroup ()=delete;

    /// @brief Constructor
    FunctionGroup (ara::core::String shortName);

    /**
     * @brief Copy constructor
     * @note To prevent problems with resource allocations during copy operation, this class is non-copyable.
     * 
     * @traceid{SWS_EM_02322}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroup (const FunctionGroup &other)=delete;

    /**
     * @brief Move constructor.
     *
     * @traceid{SWS_EM_02328}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroup (FunctionGroup &&other) noexcept;
    
    /**
     * @brief Destructor of the FunctionGroup instance.
     *
     * @traceid{SWS_EM_02266}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    ~FunctionGroup () noexcept;

    /**
     * @brief Copy assignment operator.
     * @note To prevent problems with resource allocations during copy operation, this class is non-copyable.
     *
     * @traceid{SWS_EM_02327}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroup& operator= (const FunctionGroup &other)=delete;

    /**
     * @brief Move assignment operator.
     *
     * @traceid{SWS_EM_02329}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    FunctionGroup& operator= (FunctionGroup &&other) noexcept;

    /**
     * @brief eq operator to compare with other FunctionGroup instance.
     * @param other FunctionGroup instance to compare this one with.
     * @return true in case both FunctionGroups are representing exactly the same meta-model element, false otherwise.
     * @threadsafety{Thread-safe}
     *
     * @traceid{SWS_EM_02267}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    bool operator== (const FunctionGroup &other) const noexcept;

    /**
     * @brief uneq operator to compare with other FunctionGroup instance.
     * @param other FunctionGroup instance to compare this one with.
     * @return false in case both FunctionGroups are representing exactly the same meta-model element, true otherwise.
     * @threadsafety{Thread-safe}
     *
     * @traceid{SWS_EM_02268}@tracestatus{draft}
     * @uptrace{RS_EM_00101}
     */
    bool operator!= (const FunctionGroup &other) const noexcept;

    ara::core::String short_name;

};

} /* namespace exec */
} /* namespace ara */

#endif

