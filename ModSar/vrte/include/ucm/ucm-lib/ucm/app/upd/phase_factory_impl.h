//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/upd/phase_factory_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_FACTORY_IMPL_H_

#include <mutex>
#include <memory>
#include <utility>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/upd/phase_factory.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace upd   {


class PhaseFactoryImpl final : public lib::upd::PhaseFactory
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_upd__PhaseFactoryImpl, CreateImpl);
    FRIEND_TEST(Test__ucm_app_upd__PhaseFactoryImpl, IsSupported);
#endif

public:
    explicit PhaseFactoryImpl() = default;

    PhaseFactoryImpl(PhaseFactoryImpl     &&) = delete;
    PhaseFactoryImpl(PhaseFactoryImpl const&) = delete;

    PhaseFactoryImpl& operator=(PhaseFactoryImpl     &&) = delete;
    PhaseFactoryImpl& operator=(PhaseFactoryImpl const&) = delete;

    ~PhaseFactoryImpl() = default;

    bool is_supported(const lib::upd::Phase::Type&,
                      const lib::upd::Phase::Target&,
                      const lib::upd::Phase::Device&) noexcept override;

protected:

    std::shared_ptr<lib::upd::Phase>
    create_impl(const lib::upd::Phase::Type& type,
                const lib::upd::Phase::Target& target,
                const lib::upd::Phase::Device& device,
                lib::upd::UpdateContext& ucontext) override;
};


}    // namespace upd
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_APP_UPD__PHASE_FACTORY_IMPL_H_
