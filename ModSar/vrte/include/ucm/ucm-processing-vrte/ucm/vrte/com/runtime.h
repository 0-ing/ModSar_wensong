//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/com/ara_proxy.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_vrte_com

#ifndef UCM_AAP_PROCESSING_VRTE__UCM_VRTE_COM__RUNTIME_H_
#define UCM_AAP_PROCESSING_VRTE__UCM_VRTE_COM__RUNTIME_H_

#include <mutex>
#include <chrono>
#include <memory>

#include "ucm/vrte/com/aracom_includes.h"

/// @addtogroup bosch_vrte_ucm_vrte_com
/// @{


namespace bosch  {
namespace vrte   {
namespace ucm    {
namespace vrte   {
namespace com    {

/// @brief COM runtime handling implementation.
///

class Runtime final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_vrte_com__Runtime, CTor);
#endif

    constexpr static const char* ara_mq_app_name =
                "/UpdateConfigurationManagement";

    using runtime_type  = ::ara::Runtime;

public:
    explicit Runtime();

    Runtime(Runtime     &&) = delete;
    Runtime(Runtime const&) = delete;

    Runtime& operator=(Runtime     &&) = delete;
    Runtime& operator=(Runtime const&) = delete;

    ~Runtime() = default;

private:
    runtime_type& ara_runtime_;
};


}    // namespace com
}    // namespace vrte
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_PROCESSING_VRTE__UCM_VRTE_COM__RUNTIME_H_
