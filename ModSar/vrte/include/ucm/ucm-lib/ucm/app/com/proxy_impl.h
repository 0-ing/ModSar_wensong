//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/com/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_com

#ifndef UCM_AAP_LIBRARY__UCM_APP_COM__PROXY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_COM__PROXY_IMPL_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/com/proxy.h"

/// @addtogroup bosch_vrte_ucm_app_com
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace com   {

/// @class ProxyImpl
/// @ingroup bosch_vrte_ucm_app_com
/// @brief Provide default com proxy implementation.
/// All methods return success (i.e. either true or no error)

class ProxyImpl final : public lib::com::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_stm__ProxyImpl, CTor);
#endif
public:
    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = default;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = default;

    virtual ~ProxyImpl() = default;

    /// @brief Start the service.
    virtual bool startoff() noexcept override;

    /// @brief Stop the service.
    virtual bool shutdown() noexcept override;
};


}    // namespace com
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_COM__PROXY_IMPL_H_
