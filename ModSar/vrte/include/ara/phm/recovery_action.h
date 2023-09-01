//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// \copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//=============================================================================

#ifndef ARA_PHM_RECOVERY_ACTION_H_
#define ARA_PHM_RECOVERY_ACTION_H_

#include <cstdint>
#include <memory>
#include <ara/core/instance_specifier.h>
#include <ara/exec/execution_error_event.h>
#include "ara/phm/supervised_entity.h"

namespace ara
{
namespace phm
{

/// @brief Forward declaration of implementation class of RecoveryAction
class RecoveryActionImpl;

/// @brief Enumeration of type of supervision. Scoped Enumeration of uint32_t
/// @par **Uptrace** [SWS_PHM_01138]
enum class TypeOfSupervision : std::uint32_t
{
    /// @brief Supervision is of type AliveSupervision
    AliveSupervision = 0,
    /// @brief Supervision is of type DeadlineSupervision
    DeadlineSupervision = 1,
    /// @brief Supervision is of type LogicalSupervision
    LogicalSupervision = 2
};

/// @brief RecoveryAction abstract class
/// @par **Uptrace** [SWS_PHM_01140]
class RecoveryAction
{
public:
    /// @brief Creation of an RecoveryAction
    /// @par **Uptrace** [SWS_PHM_01141]
    /// @param [in] instance  Instance specifier to the PPortPrototype of a Phm RecoveryActionInterface
    /// @warning For a given instance specifier to Phm RecoveryActionInterface, only one instance of
    /// the RecoveryAction class shall be available at a given point of time, otherwise,
    /// it might lead to undefined behavior!
    explicit RecoveryAction(const ara::core::InstanceSpecifier &instance);

    /// @brief Move constructor for RecoveryAction
    /// @par **Uptrace** [SWS_PHM_01149]
    /// @param [in,out] ra  The RecoveryAction object to be moved
    RecoveryAction(RecoveryAction &&ra) noexcept;

    /// @brief The copy constructor for RecoveryAction shall not be used
    /// @par **Uptrace** [SWS_PHM_01150]
    RecoveryAction(const RecoveryAction &) = delete;

    /// @brief Move assignment operator for RecoveryAction
    /// @par **Uptrace** [SWS_PHM_01151]
    /// @param [in,out] ra  The RecoveryAction object to be moved
    /// @return The moved RecoveryAction object
    /// @warning The move constructor shall not be called on two instances which were constructed using the same
    /// instance specifier. If called, it might lead to undefined behavior!
    RecoveryAction& operator = (RecoveryAction &&ra) noexcept;

    /// @brief The copy assignment operator for RecoveryAction shall not be used
    /// @par **Uptrace** [SWS_PHM_01152]
    RecoveryAction& operator = (const RecoveryAction &) = delete;

    /// @brief Destructor for RecoveryAction
    /// @par **Uptrace** [SWS_PHM_01145]
    virtual ~RecoveryAction() noexcept;

    /// @brief RecoveryHandler to be invoked by PHM.
    ///        The handler invocation needs to be enabled before by a call of RecoveryAction::Offer.
    /// @par **Uptrace** [SWS_PHM_01142]
    /// @param [in] executionError  Information on detected error, shall give further
    ///                             information for error recovery.
    /// @param [in] supervision     The type of local supervision which failed
    virtual void RecoveryHandler(const ara::exec::ExecutionErrorEvent &executionError,
                                 TypeOfSupervision supervision) = 0;

    /// @brief Enables potential invocations of RecoveryHandler.
    /// @par **Uptrace** [SWS_PHM_01143]
    /// @return  A Result, being either empty or containing any of the errors defined below.
    /// Errors: 
    /// ara::phm::PhmErrc::kOfferFailed : Returned if service could not be offered due to failure of communication with 
    ///                                   PHM daemon
    ara::core::Result<void> Offer(void);

    /// @brief Disables invocations of RecoveryHandler.
    /// @par **Uptrace** [SWS_PHM_01144]
    void StopOffer(void);

    /// @brief Returns the status of global supervision that the supervised entity belongs to.
    /// @par **Uptrace** [SWS_PHM_01146]
    /// @return  A result containing the current Global Supervision Status. In case of an error, it contains any of the
    /// errors defined below.
    /// Errors:
    /// ara::phm::PhmErrc::kServiceNotAvailable : Returned if the service is not availabe, e.g. due to
    ///                                           broken communication with PHM daemon.
    /// @warning The API is not fully functional as it doesn't support all global supervision status, 
    /// it just supports the states 'kOK' and 'kStopped':
    /// After the RecoveryHandler method was called before, the state returned by this method will be 'kStopped'
    /// and in any other cases, it will return 'kOK'
    ara::core::Result<GlobalSupervisionStatus> GetGlobalSupervisionStatus() const;

private:
    /// @brief A unique pointer to the implementation class
    std::unique_ptr<RecoveryActionImpl> recoveryActionImplPtr;

    /// @brief Boolean flag to indicate if the RecoveryHandler service was already offered
    bool isRecoveryHandlerServiceOffered;
};

}
}

#endif
