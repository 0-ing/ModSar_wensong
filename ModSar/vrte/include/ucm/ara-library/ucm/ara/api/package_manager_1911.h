//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/ara/api/package_manager_1911.h
/// @brief        UCM Autosar Service Interfaces
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_API_PACKAGE_MANAGER_1911_H_
#define UCM_AAP_PKGMANAGER_ARA_API_PACKAGE_MANAGER_1911_H_

#include <array>
#include <memory>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/ara/lib/araconv.h"
#include "ucm/ara/api/state_observer.h"
#include "ucm/ara/api/aracom_includes.h"
#include "ucm/ara/api/package_manager_ara.h"

/// @addtogroup bosch_vrte_ucm_ara_api
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace ara   {
namespace api   {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

/// @class PackageManager1911
/// @ingroup bosch_vrte_ucm_ara_api
/// @brief This is the interface for accessing public interfaces of the UCM over
/// ARA::COM.
///
/// Provides methods and fields for performing update.
///
class PackageManager1911 :
        public ::ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton
{
/// Friend class for unit tests.
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, TransferData);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, TransferExit);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, TransferStart);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, CurrentStatus);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, ProcessSwPackage);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, Activate);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, Finish);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, Cancel);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, Rollback);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, GetSwClusterChangeInfo);
    FRIEND_TEST(Test_ucm_ara_api_PackageManager1911, GetSwClusterInfo);
#endif
     
    constexpr static const char* ara_instance_id = "1"; /// Instance ID
    
    
    constexpr static const char* ara_mq_app_name =     
            "/UpdateConfigurationManagement"; /// Application name 
            
    /// Class PackageManager1911 inherits from
    /// ::ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton
    using skeleton_t =
            ::ara::ucm::pkgmgr::skeleton::PackageManagementSkeleton;

public:
    /// Explicit constructor 
    explicit PackageManager1911(std::unique_ptr<PackageManagerAra>&&);
    
    /// Copy Semantics
    PackageManager1911(PackageManager1911       &&) = delete;
    /// Copy Semantics
    PackageManager1911(PackageManager1911   const&) = delete;
    
    /// Move semantics
    PackageManager1911& operator=(PackageManager1911        &&) = delete;
    /// Move semantics
    PackageManager1911& operator=(PackageManager1911    const&) = delete;

    /// Virtual destructor
    virtual ~PackageManager1911();
    
    /// \brief Method to offer services over ARA:COM
    void startoff_services();
    
    ///\brief Method to stop offering services over ARA:COM
    void shutdown_services();
    
    /// \brief Start the transfer of a Software Package.
    ///
    /// \param [IN] size Size of the expected Software Package
    /// \return New TransferIdType
    /// \note the size is size of the Manifest.
    ///
    /// \details The size of the Software Package to be transferred to UCM must be
    /// provided. UCM will generate a Transfer ID for subsequent calls to
    /// TransferData, TransferExit, ProcessSwPackage, DeleteTransfer,
    /// GetLog and SetLogLevel.
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputTransferStart>
    TransferStart(const uint64_t input0) override;

    /// \brief Block-wise transfer of an artifact to UCM.
    /// This can be an installation package or an image file
    /// \param [IN] id transfer id of artifact in sequence
    /// \param [IN] data Data
    /// \param [IN] length Length of data
    /// \param [IN] blockCounter counter to check for lost blocks
    /// \return Error state
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputTransferData>
    TransferData(const TransferIdType input0,
                 const ByteVectorType input1,
                 const uint64_t input2) override;
                 
    /// \brief Indicate end of file transfer.
    /// \param [IN] id transfer id of artifact in sequence
    /// \return Error state
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputTransferExit>
    TransferExit(const TransferIdType input0) override;
    
    /// \brief Install update package (in passive location) as "transaction::install"
    /// \param [IN] id number of artifact in sequence
    /// \param [IN] CRC32 safty check value
    /// \param [IN] signature security check value
    /// \return Error state
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputProcessSwPackage>
    ProcessSwPackage(const TransferIdType input0) override;

    /// \brief Get the id of the UCM subordinate.
    /// \return Id of the UCM subordinate
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetId>
    GetId() override;

    /// \brief Activates the processed components.
    /// \return Error state
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputActivate>
    Activate() override;

    /// \brief Method for clean up.
    /// \return Error state
    ///
    /// \details This method finishes the processing for the current set of
    /// processed Software Packages.It does a cleanup of all data of the 
    /// processing including the sources of the Software Packages.
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputFinish>
    Finish() override;
    
    /// \brief Aborts an ongoing processing of a Software Package.
    /// \return Error state
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputCancel>
    Cancel(const TransferIdType input0) override;

    /// \brief Rollback the system to the state before the packages were processed.
    /// \return Error state
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputRollback>
    Rollback() override;

    /// \brief Get change info of software clusters.
    /// \return List of SoftwareClusters that are in state kAdded,kUpdated or kRemoved.
    ///
    /// \details This method returns a list pending changes to the set of
    /// SoftwareClusters on the adaptive platform. The returned list includes
    /// all SoftwareClusters that are to be added, updated or removed.
    /// The list of changes is extended in the course of processing
    /// Software Packages.
    virtual ::ara::core::Future<
    ::ara::ucm::pkgmgr::OutputGetSwClusterChangeInfo>
    GetSwClusterChangeInfo() override;

    /// \brief The method returns a list of the SoftwareClusters in kPresent state
    /// \return List of installed SoftwareClusters that are in state kPresent.
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetSwClusterInfo>
    GetSwClusterInfo() override;

    /// \brief This method returns the Software Packages that available in UCM.
    /// \return List of Software Packages.
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetSwPackages>
    GetSwPackages() override;

    /// \brief Revert the changes done by processing (ProcessSwPackage)
    /// of one or several software packages.
    virtual ::ara::core::Future<
    ::ara::ucm::pkgmgr::OutputRevertProcessedSwPackages>
    RevertProcessedSwPackages() override;
    
    /// \brief Delete a transfered Software Package
    /// \param [IN] Id number of artifact in sequence
    /// \retval Error state
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputDeleteTransfer>
    DeleteTransfer(const TransferIdType input0) override;

    /// @brief Return progress of the currently processed Software Package.
    /// @param[in] input0 The Transfer ID of the Software Package
    /// @return The progress of the current package processing 0x00 ... 0x64.
    /// 0xFF for No information available.
    virtual ::ara::core::Future<::ara::ucm::pkgmgr::OutputGetSwProcessProgress>
    GetSwProcessProgress(const TransferIdType input0) override;

private:
    StateObserver state_observer_{}; /// FSM interface
    std::unique_ptr<PackageManagerAra> pkgmgr_; /// 

    void notify_current_status(const StateObserver::state_type& state) noexcept;
    
    /// \brief Method to get the curret status of UCM 
    /// \retval Current status
    ::ara::core::Future<PackageManagerStatusType> get_current_status();
};

}    // namespace api
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#pragma GCC diagnostic push

/// @}

#endif    // UCM_AAP_PKGMANAGER_ARA_API_PACKAGE_MANAGER_1911_H_
