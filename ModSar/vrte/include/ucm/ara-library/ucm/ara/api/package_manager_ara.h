//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// \Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// \file         ucm/ara/api/package_manager_ara.h
/// \brief
/// \copyright    Robert Bosch GmbH 2020
/// \author       Vesselin Mladenov
/// \version
/// \remarks

#ifndef UCM_AAP_PKGMANAGER_ARA_API_PACKAGE_MANAGER_ARA_H_
#define UCM_AAP_PKGMANAGER_ARA_API_PACKAGE_MANAGER_ARA_H_

#include <memory>
#include <functional>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/types.h"
#include "ucm/lib/cfg/table.h"
#include "ucm/lib/stm/ucm_state.h"
#include "ucm/lib/stm/service.h"
#include "ucm/lib/swc/db/service.h"
#include "ucm/lib/utl/upgrade_lock.h"
#include "ucm/lib/upd/transactions_manager.h"

/// @addtogroup bosch_vrte_ucm_ara_api
/// @{
namespace bosch {
namespace vrte  {
namespace ucm   {
namespace ara   {
namespace api   {

using ARATypes = ucm::lib::ara::ARATypes; /// Use ARA types

/// @class PackageManagerAra
/// @ingroup bosch_vrte_ucm_ara_api
/// @brief Internal package manager API's of UCM.
///
class PackageManagerAra
{

/// Friend class for unit tests.
#if defined(GOOGLE_TEST)
    friend class Test_ucm_ara_api_package_manager;
    friend class Test_ucm_ara_api_package_manager_ara;
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, revert_processing_not_next_upgrade);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, revert_processing_cancel_failed);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, revert_processing_cancel_success_idle);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, revert_processing_cancel_success_not_idle);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, revert_ready_nothing_to_revert);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, revert_ready_revert_ok);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, revert_ready_revert_failure);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, rollback_verifying);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, rollback_activated_nothing_to_rollback);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, rollback_activated_failure);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, all_ok);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, verify_activated_success);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, verify_activated_failure1);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, verify_activated_failure2);
    FRIEND_TEST(Test_ucm_ara_api_package_manager_ara, stm_update_leave);
#endif

public:

    /// \brief Transaction group
    /// \return Id type of transaction group
    constexpr static const auto transaction_group() noexcept
    { return id_type(0); }

    /// Explicit constructor
    explicit PackageManagerAra(
            const ucm::lib::cfg::Table&,
            ucm::lib::swc::db::Service&,
            ucm::lib::stm::UCM_State&,
            ucm::lib::stm::Service&,
            ucm::lib::upd::TransactionsManager&);

    /// Copy Semantics
    PackageManagerAra(const PackageManagerAra&) = delete;

    /// Copy Semantics
    PackageManagerAra& operator=(const PackageManagerAra&) = delete;

    /// Move Semantics
    PackageManagerAra(PackageManagerAra&&) = delete;

    /// Move Semantics
    PackageManagerAra& operator=(PackageManagerAra&&) = delete;

    /// Virtual default destructor
    virtual ~PackageManagerAra() = default;


    /// \brief Start the transfer of a Software Package.
    ///
    /// \param [IN] size Size of the expected Software Package
    /// \return new TransferIdType
    /// \note the size is size of the Manifest.
    ///
    /// \details The size of the Software Package to be transferred to UCM must be
    /// provided. UCM will generate a Transfer ID for subsequent calls to
    /// TransferData, TransferExit, ProcessSwPackage, DeleteTransfer,
    /// GetLog and SetLogLevel.
    ARATypes::TransferIdType
        TransferStart(
            const std::uint64_t& size);


    /// \brief Block-wise transfer of an artifact to UCM.
    /// This can be an installation package or an image file
    /// \param [IN] id transfer id of artifact in sequence
    /// \param [IN] data Data
    /// \param [IN] length Length of data
    /// \param [IN] blockCounter counter to check for lost blocks
    /// \return Error state
    ARATypes::ApplicationErrorsType
        TransferData(
                const ARATypes::TransferIdType& id,
                const ARATypes::ByteVectorType& data,
                const std::uint64_t blockCounter);


    /// \brief Indicate end of file transfer.
    /// \param [IN] id transfer id of artifact in sequence
    /// \return Error state
    ARATypes::ApplicationErrorsType
        TransferExit(
            const ARATypes::TransferIdType& id);


    /// \brief Delete a transfered Software Package
    /// \param [IN] id number of artifact in sequence
    /// \retval Error state
    ARATypes::ApplicationErrorsType
        DeleteTransfer(
            const ARATypes::TransferIdType id);


    /// \brief Install update package (in passive location) as "transaction::install"
    /// \param [IN] id number of artifact in sequence
    /// \param [IN] CRC32 safty check value
    /// \param [IN] signature security check value
    /// \return Error state
    ARATypes::ApplicationErrorsType
        ProcessSwPackage(
            const ARATypes::TransferIdType& id);


    /// \brief Revert the changes done by processing (ProcessSwPackage)
    /// of one or several software packages.
    ARATypes::ApplicationErrorsType
        RevertProcessedSwPackages();


    /// @brief Return progress of the currently processed Software Package.
    /// @param[in] id The Transfer ID of the Software Package
    /// @param[in] progress Reference to progress information
    /// @return Application Errors -Transfer ID is invalid.
    ARATypes::ApplicationErrorsType
        GetSwProcessProgress(
            const ARATypes::TransferIdType& id,
            std::uint8_t& progress);


    /// \brief Aborts an ongoing processing of a Software Package.
    /// \return Error state
    ARATypes::ApplicationErrorsType
        Cancel(
            const ARATypes::TransferIdType& Id);


    /// \brief Activates the processed components.
    /// \return Error state
    ARATypes::ApplicationErrorsType
        Activate(
            const ARATypes::ActivateOptionType& Action);


    /// \brief Rollback the system to the state before the packages were processed.
    /// \return Error state
    ARATypes::ApplicationErrorsType
        Rollback();

    /// \brief Method for clean up.
    /// \return Error state
    ///
    /// \details This method finishes the processing for the current set of
    /// processed Software Packages.It does a cleanup of all data of the
    /// processing including the sources of the Software Packages.
    ARATypes::ApplicationErrorsType
        Finish();


    /// \brief This method sets the log level for a package.
    /// \param [IN] id number of artifact in sequence
    /// \param [IN] logLevel verbosity of log
    /// \return Error state
    ARATypes::ApplicationErrorsType
        SetLogLevel(
            const ARATypes::TransferIdType& id,
            const ARATypes::LogLevelType& logLevel);


    /// \brief Getter method to poll for the log messages of the current Session.
    /// \param [IN] id number of artifact in sequence
    /// \param [OUT] Log Log data
    /// \return Error state
    ARATypes::ApplicationErrorsType
        GetLog(
            const ARATypes::TransferIdType& id,
            ARATypes::LogType& Log);

    /// \brief Getter method to retrieve all actions that have been performed by UCM.
    /// \param [OUT] History log
    void
        GetHistory(
            ARATypes::GetHistoryVectorType& History);

    /// \brief The method returns a list of the SoftwareClusters in kPresent state
    /// \return List of installed SoftwareClusters that are in state kPresent.
    ARATypes::SwClusterInfoVectorType
        GetSwClusterInfo();

    /// \brief Get change info of software clusters.
    /// \return List of SoftwareClusters that are in state kAdded,kUpdated or kRemoved.
    ///
    /// \details This method returns a list pending changes to the set of
    /// SoftwareClusters on the adaptive platform. The returned list includes
    /// all SoftwareClusters that are to be added, updated or removed.
    /// The list of changes is extended in the course of processing
    /// Software Packages.
    ARATypes::SwClusterInfoVectorType
        GetSwClusterChangeInfo();


    /// \brief This method returns the Software Packages that available in UCM.
    /// \return List of Software Packages.
    ARATypes::SwPackageInfoVectorType
        GetSwPackages();

    /// \brief Get the current status.
    /// \return Current Status of UCM
    ARATypes::PackageManagerStatusType
        CurrentStatus();

    /// \brief Get the id of the UCM subordinate.
    /// \return Id of the UCM subordinate
    std::string
        GetId();

    /// \brief Get the UCM state.
    /// \return State of the UCM
    ucm::lib::stm::UCM_State& ucm_state() noexcept;

private:

    enum class State : unsigned /// UCM states
    {
        kInvalid,                        // Invalid state
        kIdle,                           // Idle state
        kReady,                          // Ready state
        kActivated,                      // Activated state
        kActivating,                     // Activating state
        kVerifying,                      // Verifying state
        kProcessing,                     // Processing state
        kCleaningup,                     // Cleaningup state
        kRolledback,                     // Rolledback state
        kRollingback,                    // Rollingback state
    };

    // group all_of with error type result
    bool all_ok(
            ARATypes::ApplicationErrorsType&,
            ucm::lib::upd::TransactionGroup&,
            ARATypes::ApplicationErrorsType (ucm::lib::upd::Transaction::*)(),
            ucm::lib::upd::Transaction::State);

    // revert when in processing state, i.e. cancel 
    bool revert_processing(
            ucm::lib::utl::UpgradeLock&,
            std::shared_ptr<ucm::lib::upd::TransactionGroup>&,
            ARATypes::ApplicationErrorsType&);

    // revert when in ready state
    bool revert_ready(
            ucm::lib::utl::UpgradeLock&,
            std::shared_ptr<ucm::lib::upd::TransactionGroup>&,
            ARATypes::ApplicationErrorsType&);

    // rollback when in verifying state, i.e. cancel 
    bool rollback_verifying(
            ucm::lib::utl::UpgradeLock&,
            std::shared_ptr<ucm::lib::upd::TransactionGroup>&,
            ARATypes::ApplicationErrorsType&);

    // rollback when in activated state
    bool rollback_transactions(
                    ucm::lib::utl::UpgradeLock&,
                    std::shared_ptr<ucm::lib::upd::TransactionGroup>&,
                    ARATypes::ApplicationErrorsType&);

    bool rollback_activated(
            ucm::lib::utl::UpgradeLock&,
            std::shared_ptr<ucm::lib::upd::TransactionGroup>&,
            ARATypes::ApplicationErrorsType&);

    /// @brief Verify the activated SwCs changes.
    ///
    /// @param lock Reference to the session lock.
    /// @param group The transaction group owning the affected transactions.
    /// @param error Reference to ARA error to store the result.
    /// @returns true on success, false otherwise
    bool verify_activated(
            ucm::lib::utl::UpgradeLock& lock,
            std::shared_ptr<ucm::lib::upd::TransactionGroup>& group,
            ARATypes::ApplicationErrorsType& error);

    /// @brief Prepare an FG list and send it to STM::PrepareUpdate.
    ///
    /// @param lock Reference to the session lock.
    /// @param group The transaction group owning the affected transactions.
    /// @param error Reference to ARA error to store the result.
    /// @returns true on success, false otherwise
    bool activate_processed(
            ucm::lib::utl::UpgradeLock& lock,
            std::shared_ptr<ucm::lib::upd::TransactionGroup>& group,
            ARATypes::ApplicationErrorsType& error);

    ucm::lib::utl::UpgradeMutex mutex_ {};
    State                      state_  {State::kInvalid};

    const ucm::lib::cfg::Table& config_; /// Configuration table
    ucm::lib::swc::db::Service& swcdbs_; /// SW database handling
    ucm::lib::stm::UCM_State& ucm_state_; /// UCM state
    ucm::lib::stm::Service& stm_service_; /// Object for STM handling
    ucm::lib::upd::TransactionsManager& tmanager_; /// Object for transaction manager

    std::shared_ptr<ucm::lib::upd::Transaction>
        get_transaction(ARATypes::TransferIdType const&) noexcept;

    std::shared_ptr<ucm::lib::upd::TransactionGroup>
        get_group() noexcept;

    bool remove_from_store(ARATypes::TransferIdType const&) noexcept;

    /// Sets state_ and STM state under a temporary unique lock.
    void set_state(ucm::lib::utl::UpgradeLock&, State);

    ARATypes::ApplicationErrorsType stm_update_enter() noexcept;
    ARATypes::ApplicationErrorsType stm_update_leave() noexcept;
};

}    // namespace api
}    // namespace ara
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PKGMANAGER_ARA_API_PACKAGE_MANAGER_ARA_H_
