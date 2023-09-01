//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         tests/VRTE_UT/stdmocks/ucm/vrte/swc/info/ucm/vrte/swc/info.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       HBE1LUD
/// @version
/// @remarks


#ifndef UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_INFO_H_
#define UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_INFO_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/deprule.h"
#include "ucm/lib/swc/version.h"

#include "ucm/lib/swc/db/transaction.h"

#include "ara/core/optional.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace swc   {

struct InfoTypes
{
public:
    using Name         = lib::swc::swname_type;          // same as lib::ara::ARATypes::SwInfoNameType;
    using Version      = lib::swc::Version;              // differs, std::string in ARATypes
    using Error        = lib::swc::aerror_type;          // same as lib::ara::ARATypes::ApplicationErrorsType;
    using IRecord      = lib::swc::IRecord;
    using SRecord      = lib::swc::SRecord;
    using HRecord      = lib::swc::HRecord;
    using FRecord      = lib::swc::FRecord;
    using DepUnit      = lib::swc::DepUnit;
    using Transaction  = lib::swc::db::Transaction;
    using Dependencies = std::vector<lib::swc::DepRule>;
    using FRT          = FRecord::Type;
    using Path         = std::string;
    using Paths        = std::vector<Path>;
    using astate_type  = lib::swc::astate_type;          // same as lib::ara::ARATypes::SwClusterInfoStateType
    using action_type  = lib::swc::action_type;          // same as lib::ara::ARATypes::ActionType

    template<typename T> using Optional = ::ara::core::Optional<T>;

    enum class State
    {
        never_present,
        added,
        updated,
        present,
        removed,
        erased
    };
};

struct Info
    : InfoTypes
    , protected virtual mock::Sequence
{
#if defined (GOOGLE_TEST)
    friend class Test_ucm_vrte_swc_dbfsops;
#endif
public:
    static State          translate  (astate_type const&) { return pop<State>(); }
    static astate_type    translate  (State       const&) { return pop<astate_type>(); }

    static void query_status(Name const&, Transaction&, Optional<Info>&,
                                                        Optional<Info>&) {}

    static Optional<SRecord> srecord (Name        const&,
                                      Version     const&,
                                      Transaction&) { return pop<Optional<SRecord>>(); }
    static Optional<IRecord> irecord (Name        const&,
                                      Version     const&,
                                      Transaction&) { return pop<Optional<IRecord>>(); }
    IRecord require_irecord   (Name        const&,
                               Version     const&,
                               Transaction&) { return pop<IRecord>(); }

    // only move constructible
   ~Info() = default;
    Info(Info     &&) = default;
    Info(Info const&) = delete;
    Info& operator=(Info     &&) = delete;
    Info& operator=(Info const&) = delete;

    void set (State const&) {}
    void set (Error const&) {}

    /// @brief commits new files to database, but does not acknowledge
    void add_files (Path const&, Paths const&) {}

    /// @brief moves files on file system and commits to database
    void move_files (Path const& = Path{}) {}

    /// @brief removes files from file system and commits to database 
    void erase_files () {}

    bool              ok            ()    const { return pop<bool        >(); }
    DepUnit           unit          ()    const { return pop<DepUnit     >(); }
    State             state         ()    const { return pop<State       >(); }
    Error             error         ()    const { return pop<Error       >(); }
    Version           version       ()    const { return pop<Version     >(); }
    Dependencies      dependencies  ()    const { return pop<Dependencies>(); }

    Name              dirname       ()    const { return pop<Name>(); }
    Optional<IRecord> irecord       ()    const { return pop<Optional<IRecord>>(); }
    Optional<SRecord> srecord       ()    const { return pop<Optional<SRecord>>(); }
    Optional<FRecord> frecord       (FRT) const { return pop<Optional<FRecord>>(); }
    bool              pending       ()    const { return pop<bool>(); }
    bool              acknowledge   ()          { return pop<bool>(); }
    void              erase_srecord () {}

    void              add_hrecord   (action_type const&, Error const&) {}

protected:
    Info(Name         const&,
         State        const&,
         Error        const&,
         Version      const&,
         Dependencies const&,
         Transaction&) {}
};

}    // namespace swc
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_PROCESSING_VRTE_UCM_VRTE_SWC_INFO_H_
