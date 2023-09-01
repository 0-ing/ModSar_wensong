//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/service.h
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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/error.h"
#include "ucm/lib/types.h"
#include "ucm/lib/app/service.h"
#include "ucm/lib/upd/phase_factory.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class Service final : public app::Service
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_upd__Service, CTor);
    FRIEND_TEST(Test__ucm_lib_upd__Service, SelectFactory);
    FRIEND_TEST(Test__ucm_lib_upd__Service, RegisterFactory);
#endif

public:
    explicit Service();

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    void register_factory(std::unique_ptr<PhaseFactory>&&);

    std::shared_ptr<Phase> create_phase(const Phase::Type&,
                                        const Phase::Target&,
                                        const Phase::Device&,
                                        UpdateContext& updctx);

protected:
    bool setup_nolock()    noexcept override;
    bool startoff_nolock() noexcept override;
    bool shutdown_nolock() noexcept override;

private:
    /// @brief An array to hold the phase factories.
    ///
    /// The array is limited to UCMS_MODULES_NUMBER as it is only logical
    std::array<std::unique_ptr<PhaseFactory>, UCMS_MODULES_NUMBER> factories_{};

    /// @brief A helper method to select the appropriate Factory.
    ///
    /// @return A reference to a factory in the factories_ array
    /// @throws std::runtime_error if no factory can be selected.
    PhaseFactory& select_factory(const Phase::Type&,
                                 const Phase::Target&,
                                 const Phase::Device&);
};

}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_UPD__SERVICE_H_
