//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file steady_clock.h
/// @brief A class representing an AUTOSAR Steady Clock, This clock is most suitable for measuring intervals
//==================================================================================================================

#ifndef ARA_CORE_STEADY_CLOCK_H_
#define ARA_CORE_STEADY_CLOCK_H_

#include <chrono>
#include <cstdint>

namespace ara {
namespace core {

/// @brief This clock represents a monotonic clock.
///
/// The time points of this clock cannot decrease as physical time moves forward and the time between ticks of this
/// clock is constant.
///
/// @traceid{SWS_CORE_06401}
/// @traceid{SWS_CORE_11800}
class SteadyClock final {
public:
    /// @traceid{SWS_CORE_06412}
    using rep = std::int64_t;

    /// @traceid{SWS_CORE_06413}
    using period = std::nano;

    /// @traceid{SWS_CORE_06411}
    using duration = std::chrono::duration<rep, period>;

    /// @traceid{SWS_CORE_06414}
    using time_point = std::chrono::time_point<SteadyClock, duration>;

    /// @traceid{SWS_CORE_06431}
    static constexpr bool is_steady = true;

    /// @traceid{SWS_CORE_06432}
    static time_point now() noexcept {
        duration dur(std::chrono::steady_clock::now().time_since_epoch());
        time_point tp(dur);
        return tp;
    }
};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_STEADY_CLOCK_H_
