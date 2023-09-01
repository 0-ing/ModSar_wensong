//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/ppl/service.h
/// @brief        Processing pipeline service.
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_lib_ppl

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PPL__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PPL__SERVICE_H_

#include <array>
#include <vector>
#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/cfg/table.h"
#include "ucm/lib/app/service.h"
#include "ucm/lib/sys/service.h"
#include "ucm/lib/ppl/pipelines_manager.h"

/// @addtogroup bosch_vrte_ucm_lib_swc
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace ppl   {

/// @class Service service.h ucm/lib/ppl/service.h
/// @ingroup bosch_vrte_ucm_lib_ppl
/// @brief Facade class for the pipeline processing.
///
class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_ppl__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_ppl__Service, SetupNolock);
    FRIEND_TEST(Test__ucm_lib_ppl__Service, StartoffNolock);
    FRIEND_TEST(Test__ucm_lib_ppl__Service, ShutdownNolock);
    FRIEND_TEST(Test__ucm_lib_ppl__Service, PipelinesManager);
#endif

public:
    explicit Service(sys::Service& sys_service);

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    PipelinesManager& ppl_manager() noexcept;

protected:
    virtual bool setup_nolock()    noexcept override;
    virtual bool startoff_nolock() noexcept override;
    virtual bool shutdown_nolock() noexcept override;

private:
    sys::Service& sys_service_;
    std::unique_ptr<PipelinesManager> manager_{};
};

inline PipelinesManager& Service::ppl_manager() noexcept
{
    return *manager_;
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PPL__SERVICE_H_
