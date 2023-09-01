//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         src/ucm/lib/swc/dbfsops.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       hbe1lud
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DBFSOPS_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DBFSOPS_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/types.h"
#include "ucm/lib/swc/db/service.h"
#include "ucm/lib/pkg/mnf/model/manifest.h"

#include <string>
#include <vector>

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class DBFSOps
        : virtual protected ucm::mock::Sequence
{
public:
    virtual ~DBFSOps() = default;

    void set_service(ucm::lib::swc::db::Service& arg)
    {
       dbs_ = &arg;
    }

    virtual lib::pkg::mnf::Manifest manifest(
            std::string const& swp,
            std::string const& dir)                      = 0;
    virtual void install(
            ucm::lib::swc::DepUnit              unit,
            std::vector<ucm::lib::swc::DepRule> rvec,
            std::string const&                  arroot,
            std::string const&                  arname)  = 0;
    virtual void remove             (ucm::lib::swc::DepUnit const&) = 0;
    virtual void revert             (ucm::lib::swc::DepUnit const&) = 0;
    virtual void check_dependencies (ucm::lib::swc::DepUnit const&) = 0;
    virtual void activate           (ucm::lib::swc::DepUnit const&) = 0;
    virtual void activate           (ucm::lib::swc::DepUnit const&,
                                     ucm::lib::swc::aerror_type)    = 0;
    virtual void rollback           (ucm::lib::swc::DepUnit const&) = 0;
    virtual void finish             (ucm::lib::swc::DepUnit const&) = 0;

protected:
    ucm::lib::swc::db::Service* dbs_ {nullptr};
};

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DBFSOPS_H_
