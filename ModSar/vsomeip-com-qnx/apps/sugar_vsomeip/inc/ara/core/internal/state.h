//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file state.h
/// @brief Maintains the action on callback.
//==============================================================================

#ifndef ARA_CORE_INTERNAL_STATE_H_
#define ARA_CORE_INTERNAL_STATE_H_

#include <memory>
#include <mutex>
#include <utility>

#include "ara/core/internal/unique_function.h"

namespace ara {
namespace core {

/* Forward declaration */
template <typename, typename>
class Future;

namespace internal {
/**
 * @brief Class State maintains the action (Set, Fire or Execute) on callback
 *
 * @private
 */

template <typename T, typename E = ara::core::ErrorCode>
class State : public std::enable_shared_from_this<State<T, E>> {
public:
    State() {}

    ~State() {}

    /**
     * @brief Executes the stored continuation.
     */
    void FireContinuation() {
        if (HasContinuation()) {
            unique_continuation_(get_future());
        }
    }

    /**
     * @brief Sets the continuation.
     *
     * @param func The continuation to be set.
     * @param predecessor_future The Future object to be passed as argument to continuation.
     */
    template <typename Func, class Predecessor>
    void SetContinuation(Func&& func, Predecessor& predecessor_future) {
        unique_continuation_ = std::move(func);
        delegate_future = std::move(predecessor_future.delegate_future_);
    }

    std::mutex mutex_;

private:
    /**
     * @brief Returns if a continuation exists.
     *
     * @return true if a continuation exists, false otherwise.
     */
    bool HasContinuation() const { return static_cast<bool>(unique_continuation_); }

    ara::core::Future<T, E> get_future() {
        return ara::core::Future<T, E>(std::move(delegate_future), this->shared_from_this());
    }

    unique_function<void(ara::core::Future<T, E>)> unique_continuation_;
    std::future<ara::core::Result<T, E>> delegate_future;
};

}  // namespace internal
}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_INTERNAL_STATE_H_
