//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/stm/stm_proxy.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_APP_STM__STM_PROXY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_STM__STM_PROXY_IMPL_H_

#include "ucm/mock/sequence.h"
#include "ucm/lib/stm/stm_proxy.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace stm   {

struct STM_ProxyImpl
        : public lib::stm::STM_ProxyImpl
        , virtual protected ucm::mock::Sequence
{
    explicit STM_ProxyImpl() = default;

    STM_ProxyImpl(STM_ProxyImpl     &&) = default;
    STM_ProxyImpl(STM_ProxyImpl const&) = default;

    STM_ProxyImpl& operator=(STM_ProxyImpl     &&) = default;
    STM_ProxyImpl& operator=(STM_ProxyImpl const&) = default;

    virtual ~STM_ProxyImpl() = default;

    virtual bool startoff() noexcept override
    {
        return pop<bool>();
    }

    virtual bool shutdown() noexcept override
    {
        return pop<bool>();
    }

    virtual Error update_enter() noexcept override
    {
        return Error(pop<lib::stm::ErrorValue>());
    }

    virtual Error update_leave() noexcept override
    {
        return Error(pop<lib::stm::ErrorValue>());
    }

    virtual Error reset_machine() noexcept override
    {
        return Error(pop<lib::stm::ErrorValue>());
    }

    virtual Error fg_verify(const std::vector<FG_Ident>&) noexcept override
    {
        return Error(pop<lib::stm::ErrorValue>());
    }

    virtual Error fg_activate(const std::vector<FG_Ident>&) noexcept override
    {
        return Error(pop<lib::stm::ErrorValue>());
    }

    virtual Error fg_rollback(const std::vector<FG_Ident>&) noexcept override
    {
        return Error(pop<lib::stm::ErrorValue>());
    }
};


}    // namespace stm
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_APP_STM__STM_PROXY_IMPL_H_
