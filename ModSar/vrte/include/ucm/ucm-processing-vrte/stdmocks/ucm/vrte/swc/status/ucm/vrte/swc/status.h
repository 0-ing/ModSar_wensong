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


#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_STATUS_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_STATUS_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/vrte/swc/info.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace swc   {

class Status final
    : public InfoTypes
    , protected virtual mock::Sequence
{
public:
    Status(Name const&, Transaction&) {}

    // only move constructible
   ~Status() = default;
    Status(Status     &&) = default;
    Status(Status const&) = delete;
    Status& operator=(Status     &&) = delete;
    Status& operator=(Status const&) = delete;

    Optional<IRecord> irecord(Version const&) { return pop<Optional<IRecord>>(); }
    Optional<SRecord> srecord(Version const&) { return pop<Optional<SRecord>>(); }

    void add_irecord(Version const&, Dependencies const&) {}
    void add_srecord(Version const&, State        const&, Error const&) {}

    Optional<Info>&     curr         () { return pop<Optional<Info>&>(); }
    Optional<Info>&     next         () { return pop<Optional<Info>&>(); }
    void                commit       () {}
    bool                pending      () { return pop<bool>(); }
    void                query_state  () {}
    std::vector<Status> other_status () { return pop<std::vector<Status>&&>(); }

private:
};

}    // namespace swc
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_STATUS_H_
