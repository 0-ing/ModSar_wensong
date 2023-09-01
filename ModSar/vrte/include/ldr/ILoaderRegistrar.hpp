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
/// @file   ILoaderRegistrar.hpp
/// @brief  Definition of class ILoaderRegistrar
//=============================================================================

#ifndef _ILOADERREGISTRAR_HPP_
#define _ILOADERREGISTRAR_HPP_

#include "ldr/InstanceIf.hpp"
#include "utils/FuncGroupStateId.hpp"
#include "utils/FuncGroupId.hpp"
#include "utils/ResourceGroupId.hpp"
#include "utils/IMutex.hpp"
#include "utils/String.hpp"

namespace exm {
namespace ldr {


/// @brief interface to be called from configuration code
class ILoaderRegistrar {
public:
    /// @brief virtual destructor
    virtual ~ILoaderRegistrar() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.

    /// @brief create a new function group or retrieve it if exists
    /// @param[in] FG_name name of the function group
    /// @return id of the function group
    virtual FuncGroupId FuncGroup_GetOrCreate(const char* FG_name) = 0;

    /// @brief remove an already existing function group
    /// @param[in] FG_name name of the function group
    /// @return StdReturnType::OK on success StdReturnType::GNENERAL_ERROR on failures
    virtual StdReturnType FuncGroup_Remove(const char* FG_name) = 0;

    /// @brief create a new function group or retrieve it if exists
    /// @param[in] fgid = function group id
    /// @param[in] FGState_name = state name
    /// @return function group state id
    virtual FuncGroupStateId FuncGroupState_GetOrCreate(const char* FGState_name, FuncGroupId fgid) = 0;
    
    /// @brief Get the Function Group Id
    /// @param[in]   functionGroup           Pointer to the Function Group
    /// @return  FuncGroupId                 Function Group Id
    virtual FuncGroupId GetFuncGroupId(const char* const functionGroup) = 0;

    /// @brief Get the Function Group State Id
    /// @param[in] funcGroupId            Function Group Id
    /// @param[in] funcGroupState         Pointer to Function Group State
    /// @return  FuncGroupStateId         Function Group State Id
    virtual FuncGroupStateId GetFuncGroupStateId(FuncGroupId funcGroupId, const char* const funcGroupState) = 0;

    /// @brief create a new resource group or retrieve it if exists
    /// @param[in] ResGrp_name = Resource Group name
    /// @return Resource Group id
    virtual ResourceGroupId ResourceGroup_GetOrCreate(const char* ResGrp_name) = 0;

    /// @brief Sets budget for the resource group
    /// @param[in] rgid = Resource Group Id
    /// @param[in] min_guarantee = minimum guaranteed percentage of cpu time requested
    /// @param[in] max_budget  = max budget(percentage of the CPU ) requested
    /// @return StdReturnType::OK on success, StdReturnType::GNENERAL_ERROR during error scenarios
    virtual StdReturnType  ResourceGroup_SetBudget(ResourceGroupId rgid, uint8_t min_guarantee,
                           uint8_t max_budget) = 0 ;

    /// @brief Set Resource Group Global window size
    /// @param[in] windowSize = Resource Group window size in ms
    /// @return  StdReturnType::OK on success StdReturnType::GNENERAL_ERROR on failures
    virtual StdReturnType ResourceGroup_SetWindowSize(uint16_t windowSize) = 0;

    /// @brief DEPRECATED: create a new executable instance
    ///
    /// Instead use the overloaded version with paraemeters: getNewInstance(name_, path_)
    /// @return pointer to the newly created instance
    virtual InstanceIf* getNewInstance() = 0;

    /// @brief create a new executable instance
    /// @param[in] name_ = Name of the Process
    /// @param[in] path_ = Path to the executable
    /// @return pointer to the newly created instance
    virtual InstanceIf* getNewInstance(const char* name_, const char* path_) = 0;

    /// @brief register the instance
    /// @param[in]  inst = Instance name
    /// @retval -1   error
    /// @retval 0    succesful
    virtual int32_t registerInstance( ldr::InstanceIf *inst ) = 0;

    /// @brief unregister the instance
    /// @param[in]  inst = Instance name
    /// @retval -1   error
    /// @retval 0    succesful
    virtual int32_t unregisterInstance( ldr::InstanceIf *inst ) = 0;

    /// @brief  Get a file descriptor lock variable
    ///         This can be used to perform operations on file descriptors in a safe manner.
    /// @return file descriptor lock variable
    virtual utils::IMutex& getFdGuard() = 0;

    /// @brief Access an already created app instance by its name.
    /// @return The app instance with the given name.
    /// @retval nullptr is returned if an app instance with the given name does not exist.
    /// @retval any other value, success
    virtual ldr::InstanceIf* GetAppInstanceByName(const char* name) = 0;

    /// @brief Access an already created app instance by its id.
    /// @return The app instance with the given id.
    /// @retval nullptr is returned if an app instance with the given id does not exist.
    /// @retval any other value, success
    virtual ldr::InstanceIf* GetAppInstanceById(const ldr::id_t id) = 0;
};

} /* namespace */
} /* namespace */

#endif /* header include protection */
