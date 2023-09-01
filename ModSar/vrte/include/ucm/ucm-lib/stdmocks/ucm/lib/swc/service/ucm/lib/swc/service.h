//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/swc/service/ucm/lib/swc/service.h
/// @brief        SwC processing service.
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_swc

#ifndef UCM_AAP_LIBRARY__UCM_LIB_SWC__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_SWC__SERVICE_H_

#include <array>
#include <vector>
#include <memory>

#include "ucm/lib/app/service.h"
#include "ucm/lib/swc/dbfsops.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class Service final
    : public app::Service
    , virtual protected ucm::mock::Sequence
{
public:
    explicit Service()
        : app::Service("swc::Service")
    {}

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    DBFSOps& dbfsops_get() noexcept { return pop<DBFSOps&>(); }

    void dbfsops_set(std::unique_ptr<DBFSOps>&&) {}

protected:
    bool setup_nolock()    noexcept override { return pop<bool>(); }
    bool startoff_nolock() noexcept override { return pop<bool>(); }
    bool shutdown_nolock() noexcept override { return pop<bool>(); }
};

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_SWC__SERVICE_H_
