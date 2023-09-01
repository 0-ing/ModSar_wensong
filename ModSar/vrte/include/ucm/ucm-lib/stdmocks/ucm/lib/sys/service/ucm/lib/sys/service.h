//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/ucm/lib/sys/service/ucm/lib/sys/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_SYS__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_SYS__SERVICE_H_

#include <string>
#include <memory>
#include <cstdint>

#include "ucm/error.h"
#include "ucm/lib/app/service.h"
#include "ucm/lib/utl/thread_factory.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sys   {

class Service final
    : public app::Service
    , virtual protected ucm::mock::Sequence
{
public:
    explicit Service()
        : app::Service("sys::Service")
    {}

    Service(      Service&&) = default;
    Service(const Service &) = default;

    Service& operator=(Service      &&) = default;
    Service& operator=(Service const &) = default;

    ~Service() = default;

    utl::ThreadFactory& thread_factory_get()
    {
        return pop<utl::ThreadFactory&>();
    }

    Error factory_set(std::unique_ptr<utl::ThreadFactory>&&) noexcept
    {
        return pop<Error>();
    }

protected:
    bool setup_nolock()    noexcept override { return true; }
    bool startoff_nolock() noexcept override { return true; }
    bool shutdown_nolock() noexcept override { return true; }
};

}    // namespace sys
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_SYS__SERVICE_H_
