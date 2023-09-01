//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/com/proxy.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_COM__PROXY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_COM__PROXY_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

/// @defgroup bosch_vrte_ucm_lib_com__Proxy__ut COM proxy API
/// @ingroup bosch_vrte_ucm_lib_com__ut
/// @{

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace com   {

/// @brief Provide an API for interaction with COM instance.
class Proxy
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_stm__Proxy, CTor);
#endif
protected:
    explicit Proxy() = default;

    Proxy(Proxy     &&) = default;
    Proxy(Proxy const&) = default;

    Proxy& operator=(Proxy     &&) = default;
    Proxy& operator=(Proxy const&) = default;

public:
    virtual ~Proxy() = default;

    /// @brief Start the service.
    virtual bool startoff() noexcept = 0;

    /// @brief Stop the service.
    virtual bool shutdown() noexcept = 0;
};


}    // namespace com
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_COM__PROXY_H_
