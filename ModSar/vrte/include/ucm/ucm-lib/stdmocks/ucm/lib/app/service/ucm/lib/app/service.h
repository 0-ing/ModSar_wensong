//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/app/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_APP__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_APP__SERVICE_H_

#include <mutex>
#include <string>

#include "ucm/lib/cfg/table.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

class Service : virtual protected ucm::mock::Sequence
{
protected:
    explicit Service(std::string name)
        : name_{std::move(name)}
    {}

    Service(Service     &&) = delete;
    Service(Service const&) = delete;

    Service& operator=(Service     &&) = delete;
    Service& operator=(Service const&) = delete;

public:
    virtual ~Service() = default;

    bool setup() noexcept { return pop<bool>(); }

    bool startoff() noexcept { return pop<bool>(); }

    bool shutdown() noexcept { return pop<bool>(); }

    const std::string& name() const noexcept { return name_; }

    void config(const cfg::Table* table) noexcept { config_ = table; }

protected:
    const cfg::Table* config_{nullptr};
    mutable std::mutex mutex_{};

    virtual bool setup_nolock()    noexcept = 0;
    virtual bool startoff_nolock() noexcept = 0;
    virtual bool shutdown_nolock() noexcept = 0;

    bool startoff_flag() const noexcept { return pop<bool>(); }
    bool shutdown_flag() const noexcept { return pop<bool>(); }

    const std::string& logname() const noexcept { return name_; }

private:
    std::string name_;
};
}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_APP__SERVICE_H_
