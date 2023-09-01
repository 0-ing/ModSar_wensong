//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CONTEXT_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CONTEXT_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/buf/model.h"
#include "ucm/lib/sec/provider.h"
#include "ucm/lib/utl/object_locker.h"

/// @addtogroup bosch_vrte_ucm_app_pkg_bin
/// @{


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {


/// @class Context
/// @ingroup bosch_vrte_ucm_app_pkg_bin
/// @brief Context implementation.

class Context : public lib::utl::ObjectLocker
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_app_pkg_bin__Context, TEST__CTor);
#endif

public:
    using Buffer  = lib::buf::Model;

    explicit Context(lib::sec::Provider& sec_provider)
        : sec_provider_{sec_provider}
    {}

    Context(Context     &&) = delete;
    Context(Context const&) = delete;

    Context& operator=(Context     &&) = delete;
    Context& operator=(Context const&) = delete;

    virtual ~Context() = default;

    /// @brief Return a reference to the Block buffer.
    virtual Buffer& data_buffer() noexcept = 0;

    /// @brief Return a reference to the authentication tag buffer.
    virtual Buffer& auth_buffer() noexcept = 0;

    lib::sec::Provider& sec_provider() noexcept;

protected:
    /// @brief Reference to UCM wide security provider.
    lib::sec::Provider& sec_provider_;
};

inline lib::sec::Provider& Context::sec_provider() noexcept
{
    return sec_provider_;
}

}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CONTEXT_H_
