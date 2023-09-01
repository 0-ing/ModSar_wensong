//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// \copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//=============================================================================

#ifndef ARA_PHM_HEALTH_CHANNEL_ACTION_H_
#define ARA_PHM_HEALTH_CHANNEL_ACTION_H_

#include <cstdint>
#include <ara/core/instance_specifier.h>


namespace ara
{
namespace phm
{

/// @brief HealthChannelAction abstract class
/// @par **Uptrace** [SWS_PHM_01139]
/// @tparam EnumT   Enumeration class type which represents the collection of configured health channel IDs
/// @deprecated The interface class HealthChannelAction would be deprecated from future Autosar specification and is 
/// therefore non-functional.
template <typename EnumT>
class HealthChannelAction
{
public:
    /// @brief Creation of a HealthChannelAction
    /// @par **Uptrace** [SWS_PHM_01231]
    /// @param [in] instance  Instance specifier to the PPortPrototype of a Phm HealthChannelActionInterface
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    explicit HealthChannelAction(const ara::core::InstanceSpecifier &instance) 
        __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

    /// @brief Move constructor for HealthChannelAction
    /// @par **Uptrace** [SWS_PHM_01233]
    /// @param [in] hca  The HealthChannelAction object to be moved
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    HealthChannelAction(HealthChannelAction &&hca) noexcept
        __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

    /// @brief The copy constructor for HealthChannelAction shall not be used
    /// @par **Uptrace** [SWS_PHM_01234]
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    HealthChannelAction(const HealthChannelAction &) = delete;

    /// @brief Move assignment operator for HealthChannelAction
    /// @par **Uptrace** [SWS_PHM_01235]
    /// @param [in] hca  The HealthChannelAction object to be moved
    /// @return The moved HealthChannelAction object
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    HealthChannelAction& operator = (HealthChannelAction &&hca) noexcept
        __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

    /// @brief The copy assignment operator for HealthChannelAction shall not be used
    /// @par **Uptrace** [SWS_PHM_01236]
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    HealthChannelAction& operator = (const HealthChannelAction &) = delete;

    /// @brief Destructor for HealthChannelAction
    /// @par **Uptrace** [SWS_PHM_01232]
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    virtual ~HealthChannelAction() noexcept;

    /// @brief RecoveryHandler to be invoked by PHM.
    ///        The handler invocation needs to be enabled before by a call of HealthChannelAction::Offer.
    /// @par **Uptrace** [SWS_PHM_01237]
    /// @param [in] healthStatusId  The identifier representing the Health Status. The mapping is implementation 
    ///                             specific.
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    virtual void RecoveryHandler(EnumT healthStatusId) 
        __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification"))) = 0;

    /// @brief Enables potential invocations of RecoveryHandler.
    /// @par **Uptrace** [SWS_PHM_01238]
    /// @return  A Result, being either empty or containing a fault specific error code.
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    ara::core::Result<void> Offer(void) 
        __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

    /// @brief Disables invocations of RecoveryHandler.
    /// @par **Uptrace** [SWS_PHM_01239]
    /// @warning The implementation is dummy and it doesn't have any functionality behind it!
    /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
    void StopOffer(void) 
        __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));
};

template <typename EnumT>
HealthChannelAction<EnumT>::HealthChannelAction(const ara::core::InstanceSpecifier &instance)
{
    static_cast<void>(instance);
}

template <typename EnumT>
HealthChannelAction<EnumT>::HealthChannelAction(HealthChannelAction &&hca) noexcept
{
    static_cast<void>(hca);
}

template <typename EnumT>
HealthChannelAction<EnumT>& HealthChannelAction<EnumT>::operator = (HealthChannelAction &&hca) noexcept
{
    static_cast<void>(hca);
    return *this;
}

template <typename EnumT>
HealthChannelAction<EnumT>::~HealthChannelAction() noexcept
{
    StopOffer();
}

template <typename EnumT>
ara::core::Result<void> HealthChannelAction<EnumT>::Offer()
{
    ara::core::Result<void> resultOfOffer;
    return resultOfOffer;
}

template <typename EnumT>
void HealthChannelAction<EnumT>::StopOffer()
{

}

}
}

#endif
