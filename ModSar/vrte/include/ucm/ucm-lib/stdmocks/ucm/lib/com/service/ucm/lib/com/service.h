//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/com/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_COM__SERVICE__H_
#define UCM_AAP_LIBRARY__UCM_LIB_COM__SERVICE__H_

#include <mutex>
#include <memory>

#include "ucm/mock/sequence.h"

#include "ucm/types.h"
#include "ucm/error.h"
#include "ucm/lib/types.h"
#include "ucm/lib/com/proxy.h"
#include "ucm/lib/app/service.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace com   {

class Service final
    : public app::Service
    , virtual protected ucm::mock::Sequence
{
public:
    explicit Service()
        : app::Service("com::Service")
    {}

    Service(      Service&&) = delete;
    Service(const Service &) = delete;

    Service& operator=(      Service&&) = delete;
    Service& operator=(const Service &) = delete;

    ~Service() = default;

    Error proxy_set(std::unique_ptr<Proxy>&&) noexcept
    { return pop<Error>(); }

protected:
    bool setup_nolock()    noexcept override { return true; }
    bool startoff_nolock() noexcept override { return true; }
    bool shutdown_nolock() noexcept override { return true; }
};

}    // namespace com
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif    // UCM_AAP_LIBRARY__UCM_LIB_COM__SERVICE__H_
