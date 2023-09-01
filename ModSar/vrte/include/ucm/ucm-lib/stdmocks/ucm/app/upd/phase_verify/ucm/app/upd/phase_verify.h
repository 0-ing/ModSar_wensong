//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocs/ucm/app/upd/phase_verify/ucm/app/upd/phase_verify.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_upd

#ifndef UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_VERIFY_H_
#define UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_VERIFY_H_

#include "ucm/lib/upd/phase.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace upd   {

class PhaseVerify final
    : public lib::upd::Phase
    , virtual protected ucm::mock::Sequence
{
public:
    explicit PhaseVerify(lib::upd::UpdateContext& ctx)
        : lib::upd::Phase("install", ctx)
    {}

    PhaseVerify(PhaseVerify     &&) = delete;
    PhaseVerify(PhaseVerify const&) = delete;

    PhaseVerify& operator=(PhaseVerify     &&) = delete;
    PhaseVerify& operator=(PhaseVerify const&) = delete;

    ~PhaseVerify() = default;

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

#endif    // UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_VERIFY_H_
