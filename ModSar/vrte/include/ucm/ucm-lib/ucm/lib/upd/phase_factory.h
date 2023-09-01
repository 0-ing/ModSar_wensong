//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/phase_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__PHASE_FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__PHASE_FACTORY_H_

#include <mutex>
#include <memory>
#include <utility>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/upd/phase.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {


class PhaseFactory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd__PhaseFactory, CTor);
#endif

public:
    virtual ~PhaseFactory() = default;

    virtual bool is_supported(const Phase::Type&,
                              const Phase::Target&,
                              const Phase::Device&) noexcept = 0;

    std::shared_ptr<Phase>
    create(const Phase::Type&,
           const Phase::Target&,
           const Phase::Device&,
           UpdateContext& ucontext);

protected:
    mutable std::mutex mutex_{};

    explicit PhaseFactory() noexcept = default;

    PhaseFactory(PhaseFactory     &&) = delete;
    PhaseFactory(PhaseFactory const&) = delete;

    PhaseFactory& operator=(PhaseFactory     &&) = delete;
    PhaseFactory& operator=(PhaseFactory const&) = delete;

    virtual std::shared_ptr<Phase>
    create_impl(const Phase::Type&,
                const Phase::Target&,
                const Phase::Device&,
                UpdateContext& ucontext) = 0;
};


}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UPD__PHASE_FACTORY_H_
