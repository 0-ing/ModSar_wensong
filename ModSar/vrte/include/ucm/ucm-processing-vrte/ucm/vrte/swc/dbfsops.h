//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         src/ucm/vrte/swc/dbfsops.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       hbe1lud
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_swc


#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_DBFSOPS_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_DBFSOPS_H_

#include <stdexcept>
#include <system_error>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"
#include "ucm/lib/log/logger.h"
#include "ucm/lib/swc/dbfsops.h"
#include "ucm/lib/pkg/mnf/service.h"
#include "ucm/lib/pkg/mnf/model/manifest.h"

#include "ucm/vrte/arc/tar.h"

/// @addtogroup bosch_vrte_ucm_vrte_swc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace swc   {

/// @brief Database file system handling implementation.
///

class DBFSOpsImpl final
    : public ucm::lib::swc::DBFSOps
{
#if defined (GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, CheckOverwrite_unary);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, CheckOverwrite_binary);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, archive_list);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, archive_extract);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, manifest_exist_fail);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, manifest_option_empty);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, manifest_success);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, transaction_fail);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, transaction_success);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, install_status_pending_true);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, install_next_state_not_added_updated);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, install_curr_not_ok);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, install_curr_version_equal);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, install_next_version_not_equal);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, install_not_next);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, install_success);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, remove_pending_true);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, remove_has_next);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, remove_not_present);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, remove_version_differs);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, remove_present_not_ok);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, remove_success);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, revert_pending);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, revert_not_next);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, revert_remove_version_differs);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, revert_remove_success);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, revert_install_not_added_or_updated);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, revert_install_version_differs);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, revert_install_success);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, check_dependencies_not_next);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, check_dependencies_version_differs);
    FRIEND_TEST(Test_ucm_vrte_swc_dbfsops, check_dependencies_remove_fail);
#endif
    using DBTr = ucm::lib::swc::db::Transaction;
    using Unit = ucm::lib::swc::DepUnit;

    DBTr transaction();

    void check_overwrite(
            ucm::lib::swc::FRecord const& next);
    void check_overwrite(
            ucm::lib::swc::FRecord const& next,
            ucm::lib::swc::FRecord const& prev);

    std::vector<std::string> archive_list(
            std::string const& root,
            std::string const& name);
    void archive_extract(
            std::string const& root,
            std::string const& name);

    vrte::arc::Tar          tar    {};
    lib::log::Logger        logger {};

    ucm::lib::pkg::mnf::Service& manifest_service_;
    const ucm::lib::cfg::Table& config_;

    std::string backup_root();
    std::string extract_root();

public:
    virtual ~DBFSOpsImpl() = default;

    explicit DBFSOpsImpl(ucm::lib::pkg::mnf::Service&,
                         const ucm::lib::cfg::Table&);

    ucm::lib::pkg::mnf::Manifest manifest(
            std::string const& swp,
            std::string const& dir) override;

    void install(
            ucm::lib::swc::DepUnit              unit,
            std::vector<ucm::lib::swc::DepRule> rvec,
            std::string const&                  arroot,
            std::string const&                  arname) override;

    void remove             (ucm::lib::swc::DepUnit const&) override;
    void revert             (ucm::lib::swc::DepUnit const&) override;
    void check_dependencies (ucm::lib::swc::DepUnit const&) override;
    void activate           (ucm::lib::swc::DepUnit const&) override;
    void activate           (ucm::lib::swc::DepUnit const&,
                             ucm::lib::swc::aerror_type)    override;
    void rollback           (ucm::lib::swc::DepUnit const&) override;
    void finish             (ucm::lib::swc::DepUnit const&) override;
};

}    // namespace swc
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_DBFSOPS_H_
