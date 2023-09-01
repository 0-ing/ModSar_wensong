//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/monitor_event.h
/// @brief
/// @copyright    Robert Bosch GmbH 2018
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__LIB_APP__MONITOR_EVENT_H_
#define UCM_AAP_LIBRARY__LIB_APP__MONITOR_EVENT_H_

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

class MonitorEvent
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_app_MonitorEvent, CTor);
#endif

public:
    enum class Type : unsigned
    {
        kNone,
        kShutdown,
        kLastEnum
    };

    MonitorEvent(MonitorEvent&&) = delete;
    MonitorEvent& operator=(MonitorEvent&&) = delete;

    MonitorEvent(const MonitorEvent&) = delete;
    MonitorEvent& operator=(const MonitorEvent&) = delete;

    explicit MonitorEvent(Type type)
        : type_(type)
    {}

    ~MonitorEvent() = default;

    inline Type type() const noexcept;

private:
    Type type_{Type::kNone};
};

inline MonitorEvent::Type MonitorEvent::type() const noexcept
{
    return type_;
}

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__LIB_APP__MONITOR_EVENT_H_
