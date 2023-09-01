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

#ifndef ARA_PHM_SUPERVISEDENTITYIMPLWRAPPER_H_
#define ARA_PHM_SUPERVISEDENTITYIMPLWRAPPER_H_

#include <cstdint>
#include <memory>
#include <ara/core/instance_specifier.h>
#include <ara/core/result.h>

namespace ara
{
namespace phm
{

/// @brief Represents a Checkpoint
using Checkpoint = std::uint32_t;

/// @brief Forward Declaration for them Implementation class for SupervisedEntity
class SupervisedEntityImpl;

/// @brief Forward declaration of enumeration of local supervision status
enum class LocalSupervisionStatus: std::uint32_t;

/// @brief Forward declaration of enumeration of global supervision status
enum class GlobalSupervisionStatus: std::uint32_t;


/// @brief Wrapper of implementation class for ara::phm::SupervisedEntity class
///        This class is just a wrapper and forwards the calls from ara::phm::SupervisedEntity class 
///        to the actual implementation class, i.e., ara::phm::SupervisedEntityImpl
class SupervisedEntityImplWrapper
{
public:
    /// @brief Non-parametric constructor is not supported
    SupervisedEntityImplWrapper() = delete;

    /// @brief Constructor of SupervisedEntityImplWrapper class
    /// @param [in] f_instanceSpecifier_r  Instance specifier object with the metamodel path of 
    ///                                    the supervised entity
    explicit SupervisedEntityImplWrapper(const ara::core::InstanceSpecifier& f_instanceSpecifier_r);

    /// @brief The copy constructor for SupervisedEntityImplWrapper is not supported.
    SupervisedEntityImplWrapper(const SupervisedEntityImplWrapper&) = delete;

    /// @brief Default move constructor for SupervisedEntityImplWrapper
    /// @param [in,out] SupervisedEntityImplWrapper&&  rvalue reference of the SupervisedEntityImplWrapper object
    ///                                                which shall be moved
    SupervisedEntityImplWrapper(SupervisedEntityImplWrapper&&) noexcept = default;

    /// @brief The copy assignment operator for SupervisedEntityImplWrapper is not supported.
    SupervisedEntityImplWrapper& operator = (const SupervisedEntityImplWrapper&) & = delete;

    /// @brief Default move assignment operator for SupervisedEntityImplWrapper
    /// @param [in,out] SupervisedEntityImplWrapper&&  rvalue reference of the SupervisedEntityImplWrapper object
    ///                                                which shall be moved
    /// @return Reference of the moved SupervisedEntityImplWrapper object
    SupervisedEntityImplWrapper& operator = (SupervisedEntityImplWrapper&&) & noexcept = default;

    /// @brief Destructor of the class
    virtual ~SupervisedEntityImplWrapper() noexcept;

    /// @brief Reports an occurrence of a Checkpoint
    /// @param [in] f_checkpointId   Checkpoint identifier.
    void reportCheckpoint(ara::phm::Checkpoint f_checkpointId) const;

    /// @brief Returns the local supervision status that the supervised entity belongs to.
    /// @return A Result, containing either the local supervision status of the SE or fault specific error code.
    /// @note Supported Error codes:     
    /// ara::core::CoreErrc::kInvalidArgument : Generic error code in case of any failures
    ///                                         in the execution of the method
    /// Error specific codes shall be used once defined in PHM Autosar Specifications.
    /// @warning API NOT SUPPORTED! WILL ALWAYS RETURN kOk.
    ara::core::Result<ara::phm::LocalSupervisionStatus> getLocalSupervisionStatus(void) const;

    /// @brief Returns the status of global supervision that the supervised entity belongs to.
    /// @return A Result, containing either the global supervision status of the SE or fault specific error code.
    /// @note Supported Error codes:     
    /// ara::core::CoreErrc::kInvalidArgument : Generic error code in case of any failures
    ///                                         in the execution of the method
    /// Error specific codes shall be used once defined in PHM Autosar Specifications.
    /// @warning API NOT SUPPORTED! WILL ALWAYS RETURN kOk.
    ara::core::Result<ara::phm::GlobalSupervisionStatus> getGlobalSupervisionStatus(void) const;

private:
    /// @brief Unique pointer to the implementation class of SupervisedEntity
    std::unique_ptr<SupervisedEntityImpl> supervisedEntityImplPtr;
};

}
}

#endif
