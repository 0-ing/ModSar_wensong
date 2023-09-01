//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/stm/service/ucm/lib/stm/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2019
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_STM__SERVICE__H_
#define UCM_AAP_LIBRARY__UCM_LIB_STM__SERVICE__H_

#include "ucm/mock/sequence.h"
#include "ucm/lib/stm/error.h"
#include "ucm/lib/stm/proxy.h"
#include "ucm/lib/app/service.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace stm   {

struct Service final
    : app::Service
    , virtual protected ucm::mock::Sequence
{
    explicit Service()
        : app::Service("stm::Service")
    {}

    Service(      Service&&) = delete;
    Service(const Service &) = delete;

    Service& operator=(      Service&&) = delete;
    Service& operator=(const Service &) = delete;

    ~Service() = default;

    Error reset_machine() noexcept
    {
        return Error(pop<ErrorValue>());
    }

    Error update_enter() noexcept
    {
        return Error(pop<ErrorValue>());
    }

    Error update_leave() noexcept
    {
        return Error(pop<ErrorValue>());
    }

    Error fg_verify(const std::vector<std::string>&) noexcept
    {
        return Error(pop<ErrorValue>());
    }

    Error fg_activate(const std::vector<std::string>&) noexcept
    {
        return Error(pop<ErrorValue>());
    }

    Error fg_rollback(const std::vector<std::string>&) noexcept
    {
        return Error(pop<ErrorValue>());
    }

    Error proxy_set(std::unique_ptr<Proxy>&&) noexcept
    {
        return pop<Error>();
    }
protected:
    bool setup_nolock()    noexcept override { return true; }

    bool startoff_nolock() noexcept
    {
        return pop<bool>();
    }

    bool shutdown_nolock() noexcept
    {
        return pop<bool>();
    }
};

}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_STM__SERVICE__H_
