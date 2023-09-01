//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/stm/proxy_impl/ucm/app/stm/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_stm

#ifndef UCM_AAP_LIBRARY__UCM_APP_STM__PROXY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_STM__PROXY_IMPL_H_

#include <string>

#include "ucm/lib/stm/proxy.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace stm   {

class ProxyImpl
        : public lib::stm::Proxy
        , virtual protected ucm::mock::Sequence
{
public:
    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = default;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = default;

    virtual ~ProxyImpl() = default;

    bool startoff() noexcept override
    { return pop<bool>(); }

    bool shutdown() noexcept override
    { return pop<bool>(); }

    Error reset_machine() noexcept override
    { return pop<Error>(); }

    Error update_enter() noexcept override
    { return pop<Error>(); }

    Error update_leave() noexcept override
    { return pop<Error>(); }

    Error fg_verify(const std::vector<lib::stm::FG_Ident>&) noexcept
    { return pop<Error>(); }

    Error fg_activate(const std::vector<lib::stm::FG_Ident>&) noexcept
    { return pop<Error>(); }

    Error fg_rollback(const std::vector<lib::stm::FG_Ident>&) noexcept
    { return pop<Error>(); }
};


}    // namespace stm
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_STM__PROXY_IMPL_H_
