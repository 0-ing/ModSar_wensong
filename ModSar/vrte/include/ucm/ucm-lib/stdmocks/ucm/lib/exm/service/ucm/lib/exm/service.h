//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/exm/service/ucm/lib/exm/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_EXM__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_EXM__SERVICE_H_

#include <string>
#include <memory>
#include <cstdint>

#include "ucm/lib/exm/types.h"
#include "ucm/lib/exm/proxy.h"
#include "ucm/lib/app/service.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace exm   {

class Service
    : public app::Service
    , virtual protected ucm::mock::Sequence
{
public:
    explicit Service()
        : app::Service("exm::Service")
    {}

    Service(      Service&&) = default;
    Service(const Service &) = default;

    Service& operator=(Service      &&) = default;
    Service& operator=(Service const &) = default;

    ~Service() = default;

    Error proxy_set(std::unique_ptr<Proxy>&&) noexcept
    { return pop<Error>(); }

    bool app_action(const AppAction&, const std::string&) noexcept
    { return pop<bool>(); }

protected:
    bool setup_nolock()    noexcept override { return pop<bool>(); }
    bool startoff_nolock() noexcept override { return pop<bool>(); }
    bool shutdown_nolock() noexcept override { return pop<bool>(); }
};

}    // namespace exm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__SERVICE__H_
