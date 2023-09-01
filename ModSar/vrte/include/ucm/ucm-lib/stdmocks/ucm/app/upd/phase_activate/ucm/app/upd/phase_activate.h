//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocs/ucm/app/upd/phase_activate/ucm/app/upd/phase_activate.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_upd

#ifndef UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_ACTIVATE_H_
#define UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_ACTIVATE_H_

#include "ucm/lib/upd/phase.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace upd   {

class PhaseActivate final
    : public lib::upd::Phase
    , virtual protected ucm::mock::Sequence
{
public:
    explicit PhaseActivate(lib::upd::UpdateContext& ctx)
        : lib::upd::Phase("activate", ctx)
    {}

    PhaseActivate(PhaseActivate     &&) = delete;
    PhaseActivate(PhaseActivate const&) = delete;

    PhaseActivate& operator=(PhaseActivate     &&) = delete;
    PhaseActivate& operator=(PhaseActivate const&) = delete;

    ~PhaseActivate() = default;

    ara_error_type setup() noexcept override
    { return pop<ara_error_type>(); }

    ara_error_type verify() noexcept override
    { return pop<ara_error_type>(); }

    ara_error_type perform() noexcept override
    { return pop<ara_error_type>(); }

    ara_error_type after_failure() noexcept override
    { return pop<ara_error_type>(); }

    ara_error_type after_success() noexcept override
    { return pop<ara_error_type>(); }
};

}    // namespace upd
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_ACTIVATE_H_
