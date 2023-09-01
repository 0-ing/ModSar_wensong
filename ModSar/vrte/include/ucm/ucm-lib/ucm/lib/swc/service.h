//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/swc/service.h
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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/app/service.h"
#include "ucm/lib/swc/dbfsops.h"

/// @addtogroup bosch_vrte_ucm_lib_swc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

/// @class Service service.h ucm/lib/swc/service.h
/// @ingroup bosch_vrte_ucm_lib_swc
/// @brief Facade class for the SwC processing.
///
class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_swc__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_swc__Service, SetupNolock);
    FRIEND_TEST(Test__ucm_lib_swc__Service, StartoffNolock);
    FRIEND_TEST(Test__ucm_lib_swc__Service, ShutdownNolock);
#endif

    using Base = app::Service;

public:
    explicit Service();

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    DBFSOps& dbfsops_get() noexcept;

    void dbfsops_set(std::unique_ptr<DBFSOps>&& dbfsops);

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    std::unique_ptr<DBFSOps> dbfsops_{};
};

inline DBFSOps& Service::dbfsops_get() noexcept
{
    return *dbfsops_;
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_SWC__SERVICE_H_
