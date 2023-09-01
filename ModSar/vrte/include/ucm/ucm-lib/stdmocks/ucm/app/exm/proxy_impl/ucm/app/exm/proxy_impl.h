//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/exm/proxy_impl/ucm/app/exm/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_exm

#ifndef UCM_AAP_LIBRARY__UCM_APP_EXM__PROXY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_EXM__PROXY_IMPL_H_

#include <string>
#include <cstdint>

#include "ucm/lib/exm/proxy.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace exm   {
    
class ProxyImpl
        : public lib::exm::Proxy
        , virtual protected ucm::mock::Sequence
{
public:
    virtual ~ProxyImpl() = default;

    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = default;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = default;

    bool startoff() noexcept override
    { return pop<bool>(); }

    bool shutdown() noexcept override
    { return pop<bool>(); }

    bool app_action(const lib::exm::AppAction&, const std::string&) noexcept
    { return pop<bool>(); }
};

}    // namespace exm
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_EXM__PROXY_IMPL_H_
