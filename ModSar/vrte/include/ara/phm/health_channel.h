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

#ifndef ARA_PHM_HEALTH_CHANNEL_H_
#define ARA_PHM_HEALTH_CHANNEL_H_

#include <memory>
#include <utility>
#include <cstdint>
#include <type_traits>
#include <ara/core/instance_specifier.h>
#include <ara/core/core_error_domain.h>
#include <ara/core/result.h>

namespace ara
{
namespace phm
{

/// @brief Represents a Health Status
using HealthStatus = std::uint32_t;

/// @brief HealthChannel Class
/// @par **Uptrace** [SWS_PHM_01122]
/// @deprecated The interface class HealthChannel would be deprecated from future Autosar specification and is 
/// therefore non-functional.
template <typename EnumT>
class HealthChannel
{
public:
   /// @brief Creation of a health channel.
   /// @par **Uptrace** [SWS_PHM_00457]
   /// @param [in] instance Instance specifier of the health channel
   /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
   explicit HealthChannel(const ara::core::InstanceSpecifier& instance) 
      __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

   /// @brief The copy constructor for HealthChannel shall not be used.
   /// @par **Uptrace** [SWS_PHM_01222]
   HealthChannel(const HealthChannel& channel) = delete;
   
   /// @brief Move constructor for HealthChannel
   /// @par **Uptrace** [SWS_PHM_01224]   
   /// @param [in,out] channel The HealthChannel object to be moved
   /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
   HealthChannel(HealthChannel &&channel) noexcept 
      __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

   /// @brief The copy assignment operator for HealthChannel shall not be used.
   /// @par **Uptrace** [SWS_PHM_01223]
   /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
   HealthChannel& operator = (const HealthChannel& channel) = delete;

   /// @brief Move assignment operator for HealthChannel
   /// @par **Uptrace** [SWS_PHM_01225]   
   /// @param [in,out] channel The HealthChannel object to be moved
   /// @return The moved HealthChannel object
   /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
   HealthChannel& operator = (HealthChannel &&channel) noexcept 
      __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

   /// @brief Destructor of a HealthChannel
   /// @par **Uptrace** [SWS_PHM_01221]
   /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
   virtual ~HealthChannel() noexcept;
  
   /// @brief Reports a Health Status
   /// @par **Uptrace** [SWS_PHM_01128]
   /// @param [in] healthStatusId Health status identifier.
   /// @return A Result, being either empty or containing a fault specific error code.
   /// @note Supported Error codes:     
   /// ara::core::CoreErrc::kInvalidArgument : Generic error code in case of any failures
   ///                                         in the execution of the method
   /// Error specific codes shall be used once defined in PHM Autosar Specifications. 
   /// @deprecated The method would be deprecated from future Autosar specification and is therefore non-functional.
   ara::core::Result<void> ReportHealthStatus(EnumT healthStatusId) 
      __attribute__ ((deprecated("The method is dummy and will be deprecated from future Autosar specification")));

private:

   /// @brief Assert if HealthChannel class is constructed with an enumeration type
   /// @par **Uptrace** [SWS_PHM_01122]
   static_assert(std::is_enum<EnumT>::value, "HealthChannel class must be constructed with template type "
                                              "which is an enumeration class!");

   /// @brief Underlying data type of the used template argument
   using underlyingHealthStatusIdType = typename std::underlying_type<EnumT>::type;

   /// @brief Assert if enumeration used during the construction of HealthChannel class 
   ///        is of the type std::uint32_t
   /// @par **Uptrace** [SWS_PHM_01118]
   static_assert(std::is_same<underlyingHealthStatusIdType, ara::phm::HealthStatus>::value, 
                  "The enumeration class used during the construction of HealthChannel class must be of "
                  "type 'std::uint32_t'!");  
};

template <typename EnumT>
HealthChannel<EnumT>::HealthChannel(const ara::core::InstanceSpecifier& instance)
{
   (void)instance;
}

template <typename EnumT>
HealthChannel<EnumT>::HealthChannel(HealthChannel &&channel) noexcept
{
      (void)channel;
}

template <typename EnumT>
HealthChannel<EnumT>& HealthChannel<EnumT>::operator = (HealthChannel &&channel) noexcept
{
   (void)channel;
   return *this;
}

template <typename EnumT>
HealthChannel<EnumT>::~HealthChannel() noexcept
{   
}

template <typename EnumT>
ara::core::Result<void> HealthChannel<EnumT>::ReportHealthStatus(EnumT healthStatusId)
{
   ara::core::Result<void> resultOfReportHealthStatus;
   (void)healthStatusId;

   return resultOfReportHealthStatus;
}

}
}
#endif
