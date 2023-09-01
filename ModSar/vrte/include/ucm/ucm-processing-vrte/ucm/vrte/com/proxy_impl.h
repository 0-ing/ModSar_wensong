//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/com/proxy_impl.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_com

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_COM__PROXY_IMPL_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_COM__PROXY_IMPL_H_

#include <memory>
#include <vector>


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/com/proxy.h"
#include "ucm/vrte/com/runtime.h"

/// @addtogroup bosch_vrte_ucm_vrte_com
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace vrte  {
namespace com   {

/// @brief COM proxy implementation.
///

class ProxyImpl final : public lib::com::Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_com__ProxyImpl, CTor);
#endif
public:
    explicit ProxyImpl() = default;

    ProxyImpl(ProxyImpl     &&) = delete;
    ProxyImpl(ProxyImpl const&) = delete;

    ProxyImpl& operator=(ProxyImpl     &&) = delete;
    ProxyImpl& operator=(ProxyImpl const&) = delete;

    virtual ~ProxyImpl() = default;

    /// @brief Start the service.
    /// @param [IN] None
    /// @return Return TRUE
    bool startoff() noexcept override;

    /// @brief Stop the service.
    /// @param [IN] None
    /// @return Return TRUE
    bool shutdown() noexcept override;

private:
    Runtime instance_{};
};


}    // namespace com
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_COM__PROXY_IMPL_H_
