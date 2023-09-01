//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/pkg/bin/serviceucm/lib/pkg/bin/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks


#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SERVICE_H_

#include <memory>

#include "ucm/lib/app/service.h"
#include "ucm/lib/sec/provider.h"
#include "ucm/lib/pkg/bin/error.h"
#include "ucm/lib/pkg/bin/handle.h"
#include "ucm/lib/pkg/bin/factory.h"


#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace bin   {

class Service final
    : public app::Service
    , virtual protected ucm::mock::Sequence
{
public:
    explicit Service(sec::Provider&)
        : app::Service("SWP")
    {}

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

    ~Service() = default;

    /// @brief Reset the authentication tag instance.
    Error process_tag_init() noexcept
    { return Error(0); }

    /// @brief Feed data to the authentication tag instance.
    Error process_feed(const void*, size_t, size_t&) noexcept
    { return Error(0); }

    /// @brief Feed data to the authentication tag instance.
    Error process_tag_load(const std::string&) noexcept
    { return Error(0); }

    /// @brief Check if the authentication tag need more data.
    ///
    /// @return true, if the authentication tag buffer is ready.
    /// @return false, if the authentication tag buffer is NOT ready.
    static bool process_tag_ready(const Error&) noexcept
    { return true; }

    /// @brief Check if the authentication tag has an error condition.
    ///
    /// @return true, if the authentication tag has no error condition.
    /// @return false, if the authentication tag has error condition.
    static bool process_tag_check(const Error&) noexcept
    { return true; }

    std::unique_ptr<SWP_Process>
    swp_process(const std::string&, const std::string&)
    { return nullptr; }

    std::unique_ptr<SWP_Compose>
    swp_compose(const std::string&, uint32_t, uint32_t)
    { return nullptr; }

    /// @brief Register a swpackage processing Factory.
    /// The method should be called only during the modules <b>setup</b> phase
    /// as there is no concurrent access protection in place.
    /// @param[in] factory A unique pointer to the base class of the Factory.
    void register_factory(std::unique_ptr<Factory>&&) {}

protected:
    bool setup_nolock()    noexcept override { return true; }
    bool startoff_nolock() noexcept override { return true; }
    bool shutdown_nolock() noexcept override { return true; }
};


}    // namespace bin
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_BIN__SERVICE_H_
