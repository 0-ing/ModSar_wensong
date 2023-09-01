//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/ppl/service/ucm/lib/ppl/service.h
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
public:
    explicit Service(sys::Service&)
        : app::Service("ppl::Service")
    {}

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    PipelinesManager& ppl_manager() noexcept;

protected:
    bool setup_nolock()    noexcept override { return true; }
    bool startoff_nolock() noexcept override { return true; }
    bool shutdown_nolock() noexcept override { return true; }

private:
    std::unique_ptr<PipelinesManager> manager_{};
};

inline PipelinesManager& Service::ppl_manager() noexcept
{
    return pop<PipelinesManager&>();
}

}    // namespace ppl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PPL__SERVICE_H_
