//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// \copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//=============================================================================

#ifndef ARA_PHM_SUPERVISED_ENTITY_H_
#define ARA_PHM_SUPERVISED_ENTITY_H_

#include <cstdint>
#include <memory>
#include <utility>
#include <type_traits>
#include <ara/core/instance_specifier.h>
#include <ara/core/core_error_domain.h>
#include <ara/core/result.h>
#include "ara/phm/SupervisedEntityImplWrapper.h"

namespace ara
{
namespace phm
{

/// @brief Enumeration of local supervision status
/// @par **Uptrace** [SWS_PHM_01136]
enum class LocalSupervisionStatus : std::uint32_t
{
    /// @brief Supervision is not active.
    kDeactivated,
    /// @brief Supervision is active and no failure is present.
    kOK,
    /// @brief A failure was detected but still within tolerance/debouncing.
    kFailed,
    /// @brief A failure was detected and qualified.
    kExpired
};

/// @brief Enumeration of global supervision status
/// @par **Uptrace** [SWS_PHM_01137]
enum class GlobalSupervisionStatus : std::uint32_t
{
    /// @brief Supervision is not active.
    kDeactivated,
    /// @brief All relevant local supervisions are in status KOK or KDeavtivated.
    kOK,
    /// @brief At least one local supervision is in status kFailled but none in status KExpired.
    kFailed,
    /// @brief At least one local supervision is in status kExpired but the number of
    ///        Supervision Cycles since reaching kExpired has not exceeded the tolerance.
    kExpired,
    /// @brief At least one local supervision is in status kExpired and the number of
    ///        Supervision Cycles since reaching kExpired has exceeded the tolerance.
    kStopped
};

/// @brief SupervisedEntity Class
/// @par **Uptrace** [SWS_PHM_01132]
template <typename EnumT>
class SupervisedEntity
{
public:
    /// @brief Creation of a SupervisedEntity.
    /// @par **Uptrace** [SWS_PHM_01123]
    /// @param [in] instance  Instance specifier of the supervised entity   
    explicit SupervisedEntity(const ara::core::InstanceSpecifier& instance);

    /// @brief The copy constructor for SupervisedEntity shall not be used.
    /// @par **Uptrace** [SWS_PHM_01212]
    SupervisedEntity(const SupervisedEntity &se) = delete;

    /// @brief Move constructor for SupervisedEntity
    /// @par **Uptrace** [SWS_PHM_01214]
    /// @param [in,out] se  The SupervisedEntity object to be moved
    SupervisedEntity(SupervisedEntity &&se) noexcept;

    /// @brief The copy assignment operator for SupervisedEntity shall not be used.
    /// @par **Uptrace** [SWS_PHM_01213]
    SupervisedEntity& operator = (const SupervisedEntity &se) = delete;

    /// @brief Move assignment operator for SupervisedEntity
    /// @par **Uptrace** [SWS_PHM_01215]
    /// @param [in,out] se  The SupervisedEntity object to be moved
    /// @return The moved SupervisedEntity object
    SupervisedEntity& operator = (SupervisedEntity &&se) noexcept;

    /// @brief Destructor of a SupervisedEntity
    /// @par **Uptrace** [SWS_PHM_01211]
    virtual ~SupervisedEntity() noexcept;

    /// @brief Reports an occurrence of a Checkpoint
    /// @par **Uptrace** [SWS_PHM_01127]
    /// @param [in] checkpointId  Checkpoint identifier.
    void ReportCheckpoint(EnumT checkpointId) noexcept;

    /// @brief Returns the local supervision status that the supervised entity belongs to.
    /// @par **Uptrace** [SWS_PHM_01134]
    /// @return A Result, containing either the local supervision status of the SE or fault specific error code.
    /// @note Supported Error codes:     
    /// ara::core::CoreErrc::kInvalidArgument : Generic error code in case of any failures
    ///                                         in the execution of the method
    /// Error specific codes shall be used once defined in PHM Autosar Specifications.
    /// @warning API NOT SUPPORTED! WILL ALWAYS RETURN kOk.
    ara::core::Result<LocalSupervisionStatus> GetLocalSupervisionStatus() const;

    /// @brief Returns the status of global supervision that the supervised entity belongs to.
    /// @par **Uptrace** [SWS_PHM_01135]
    /// @return A Result, containing either the global supervision status of the SE or fault specific error code.
    /// @note Supported Error codes:     
    /// ara::core::CoreErrc::kInvalidArgument : Generic error code in case of any failures
    ///                                         in the execution of the method
    /// Error specific codes shall be used once defined in PHM Autosar Specifications.
    /// @warning API NOT SUPPORTED! WILL ALWAYS RETURN kOk.
    ara::core::Result<GlobalSupervisionStatus> GetGlobalSupervisionStatus() const;

private:
    /// @brief Unique pointer to the wrapper of implementation class of SupervisedEntity
    std::unique_ptr<SupervisedEntityImplWrapper> supervisedEntityImplWrapperPtr;

    /// @brief Assert if SupervisedEntity class is constructed with an enumeration type
    /// @par **Uptrace** [SWS_PHM_01132]
    static_assert(std::is_enum<EnumT>::value, "SupervisedEntity class must be constructed with template type "
                                              "which is an enumeration class!");

    /// @brief Underlying data type of the used template argument
    using underlyingCheckpointIdType = typename std::underlying_type<EnumT>::type;

    /// @brief Assert if enumeration used during the construction of SupervisedEntity class 
    ///        is of the type std::uint32_t
    /// @par **Uptrace** [SWS_PHM_00424]
    static_assert(std::is_same<underlyingCheckpointIdType, ara::phm::Checkpoint>::value, 
                  "The enumeration class used during the construction of SupervisedEntity class must be of "
                  "type 'std::uint32_t'!");
};

template <typename EnumT>
SupervisedEntity<EnumT>::SupervisedEntity(const ara::core::InstanceSpecifier& instance):
    supervisedEntityImplWrapperPtr(std::unique_ptr<SupervisedEntityImplWrapper>(
                                        new(std::nothrow) SupervisedEntityImplWrapper(instance)))
{
    if(supervisedEntityImplWrapperPtr.get() == nullptr)
    {
        // TODO: Log the event using a logger method which doesn't depend on the "new" operator
    }
}

template <typename EnumT>
SupervisedEntity<EnumT>::SupervisedEntity(SupervisedEntity &&se) noexcept:
    supervisedEntityImplWrapperPtr(std::move(se.supervisedEntityImplWrapperPtr))
{
    
}

template <typename EnumT>
SupervisedEntity<EnumT>& SupervisedEntity<EnumT>::operator = (SupervisedEntity &&se) noexcept
{
    if(this != &se)
    {
        if(supervisedEntityImplWrapperPtr.get() != nullptr)
        {
            supervisedEntityImplWrapperPtr.reset(nullptr);
        }

        supervisedEntityImplWrapperPtr = std::move(se.supervisedEntityImplWrapperPtr);
    }

    return *this;
}

template <typename EnumT>
SupervisedEntity<EnumT>::~SupervisedEntity() noexcept
{

}

template <typename EnumT>
void SupervisedEntity<EnumT>::ReportCheckpoint(EnumT checkpointId) noexcept
{
    if(supervisedEntityImplWrapperPtr.get() != nullptr)
    {
        supervisedEntityImplWrapperPtr->reportCheckpoint(static_cast<ara::phm::Checkpoint>(checkpointId));
    }
}

template <typename EnumT>
ara::core::Result<ara::phm::LocalSupervisionStatus> SupervisedEntity<EnumT>::GetLocalSupervisionStatus() const
{
    ara::core::Result<ara::phm::LocalSupervisionStatus>
                        resultOfGetLocalSupervisionStatus(ara::phm::LocalSupervisionStatus::kDeactivated);

    if(supervisedEntityImplWrapperPtr.get() != nullptr)
    {
        resultOfGetLocalSupervisionStatus = supervisedEntityImplWrapperPtr->getLocalSupervisionStatus();
    }
    else
    {
        resultOfGetLocalSupervisionStatus.EmplaceError(ara::core::CoreErrc::kInvalidArgument);
    }

    return resultOfGetLocalSupervisionStatus;
}

template <typename EnumT>
ara::core::Result<ara::phm::GlobalSupervisionStatus> SupervisedEntity<EnumT>::GetGlobalSupervisionStatus() const
{
    ara::core::Result<ara::phm::GlobalSupervisionStatus>
                        resultOfGetGlobalSupervisionStatus(ara::phm::GlobalSupervisionStatus::kOK);

    if(supervisedEntityImplWrapperPtr.get() != nullptr)
    {
        resultOfGetGlobalSupervisionStatus = supervisedEntityImplWrapperPtr->getGlobalSupervisionStatus();                                                
    }
    else
    {
        resultOfGetGlobalSupervisionStatus.EmplaceError(ara::core::CoreErrc::kInvalidArgument);
    }

    return resultOfGetGlobalSupervisionStatus;
}

}
}
#endif
