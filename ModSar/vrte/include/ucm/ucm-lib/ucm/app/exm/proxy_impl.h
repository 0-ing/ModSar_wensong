//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/exm/proxy_impl.h
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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/exm/proxy.h"

/// @addtogroup bosch_vrte_ucm_app_exm
/// @{
    
namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace exm   {
    
/// @class ProxyImpl
/// @ingroup bosch_vrte_ucm_app_exm
/// @brief Provide default exm proxy implementation.
/// All methods return success (i.e. either true or no error)

class ProxyImpl : public lib::exm::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_exm__Proxy, CTor);
#endif

public:
    virtual ~ProxyImpl() = default;

    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = default;
    ProxyImpl(ProxyImpl const&) = default;

    ProxyImpl& operator=(ProxyImpl     &&) = default;
    ProxyImpl& operator=(ProxyImpl const&) = default;
    
    /// @brief Start the service.
    virtual bool
    startoff() noexcept override;
     
    /// @brief Stop the service.
    virtual bool
    shutdown() noexcept override;

    virtual bool
    app_action(const lib::exm::AppAction&, const std::string&)
    noexcept override;
};

}    // namespace exm
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_APP_EXM__PROXY_IMPL_H_
