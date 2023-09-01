//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/sec/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_sec

#ifndef UCM_AAP_LIBRARY__UCM_APP_SEC__PROXY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_SEC__PROXY_IMPL_H_

#include <string>
#include <cstdint>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/sec/proxy.h"

/// @addtogroup bosch_vrte_ucm_app_sec
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace sec   {


/// @class ProxyImpl
/// @ingroup bosch_vrte_ucm_app_sec
/// @brief Default security proxy implementation.
///

class ProxyImpl : public lib::sec::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_sec__Proxy, CTor);
#endif

public:
    virtual ~ProxyImpl() = default;

    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = default;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = default;

    bool
    startoff() noexcept override;

    bool
    shutdown() noexcept override;

    bool
    app_action(const lib::sec::AppAction&, const std::string&)
    noexcept override;
};

}    // namespace sec
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_SEC__PROXY_IMPL_H_
