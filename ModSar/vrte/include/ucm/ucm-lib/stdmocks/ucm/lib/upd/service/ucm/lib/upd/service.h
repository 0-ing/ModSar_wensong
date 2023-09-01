//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocs/ucm/lib/upd/service/ucm/lib/upd/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__SERVICE_H_

#include <mutex>
#include <memory>
#include <functional>

#include "ucm/error.h"
#include "ucm/lib/types.h"
#include "ucm/lib/app/service.h"
#include "ucm/lib/upd/phase_factory.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Service final
    : public app::Service
    , virtual protected ucm::mock::Sequence
{
public:
    explicit Service()
        : app::Service("upd::Service")
    {}

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    void register_factory(std::unique_ptr<PhaseFactory>&&) {}

    std::shared_ptr<Phase> create_phase(const Phase::Type&,
                                        const Phase::Target&,
                                        const Phase::Device&,
                                        UpdateContext&)
    {
        return pop<std::shared_ptr<Phase>>();
    }

protected:
    bool setup_nolock()    noexcept override { return true; }
    bool startoff_nolock() noexcept override { return true; }
    bool shutdown_nolock() noexcept override { return true; }
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__SERVICE_H_
