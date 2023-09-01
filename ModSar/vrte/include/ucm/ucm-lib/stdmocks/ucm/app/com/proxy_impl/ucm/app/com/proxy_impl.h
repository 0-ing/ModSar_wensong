//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/com/proxy_impl/ucm/app/com/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_com

#ifndef UCM_AAP_LIBRARY__UCM_APP_COM__PROXY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_COM__PROXY_IMPL_H_

#include "ucm/lib/com/proxy.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace com   {

class ProxyImpl final
    : public lib::com::Proxy
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
};


}    // namespace com
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_COM__PROXY_IMPL_H_
