//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/sec/proxy/ucm/lib/sec/proxy.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_SEC__PROXY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_SEC__PROXY_H_

#include <string>
#include <cstdint>

#include "ucm/mock/sequence.h"
#include "ucm/lib/sec/types.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace sec   {

class Proxy
{
public:
    virtual ~Proxy() = default;

    virtual bool startoff() noexcept = 0;

    virtual bool shutdown() noexcept = 0;

    virtual bool app_action(const AppAction&, const std::string&) noexcept = 0;

protected:
    explicit Proxy() = default;

    Proxy(      Proxy&&) = default;
    Proxy(const Proxy &) = default;

    Proxy& operator=(Proxy      &&) = default;
    Proxy& operator=(Proxy const &) = default;
};

}    // namespace sec
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_SEC__PROXY_H_
