//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         ucm/lib/swc/db/status.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       HBE1LUD
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_swc


#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_STATUS_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_STATUS_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/vrte/swc/info.h"

/// @addtogroup bosch_vrte_ucm_vrte_swc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace swc   {

/// @brief SWC status handling implementation.
///

class Status final
    : public InfoTypes
{
#if defined (GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_vrte_swc_status, add_srecord_runtime_error);
    FRIEND_TEST(Test_ucm_vrte_swc_status, commit);
    FRIEND_TEST(Test_ucm_vrte_swc_status, pending);
    FRIEND_TEST(Test_ucm_vrte_swc_status, other_status_empty);
    FRIEND_TEST(Test_ucm_vrte_swc_status, other_status);
    FRIEND_TEST(Test_ucm_vrte_swc_status, irecord);
    FRIEND_TEST(Test_ucm_vrte_swc_status, add_irecord);
#endif
public:
    Status(Name const&, Transaction&);

    // only move constructible
   ~Status() = default;
    Status(Status     &&) = default;
    Status(Status const&) = delete;
    Status& operator=(Status     &&) = delete;
    Status& operator=(Status const&) = delete;

    Optional<IRecord> irecord(Version const&);
    Optional<SRecord> srecord(Version const&);

    void add_irecord(Version const&, Dependencies const&);
    void add_srecord(Version const&, State        const&, Error const&);

    Optional<Info>&     curr         ();
    Optional<Info>&     next         ();
    void                commit       ();
    bool                pending      ();
    void                query_state  ();
    std::vector<Status> other_status ();

private:
    Name           name_;
    Optional<Info> curr_;
    Optional<Info> next_;
    Transaction&   trans_;
};

inline Status::Optional<Info>& Status::curr()
{
    return curr_;
}


inline Status::Optional<Info>& Status::next()
{
    return next_;
}


}    // namespace swc
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_STATUS_H_
