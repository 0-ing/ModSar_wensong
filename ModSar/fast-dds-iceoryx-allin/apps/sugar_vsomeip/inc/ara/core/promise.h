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

/// @file
/// @brief Interface to class ara::core::Promise
///
/// ara::core::Future is a composition of basic features of std::future
/// and methods borrowed from the C++ proposal N3857.
///
/// ara::core::Promise is the corresponding promise that returns an ara::core::Future.
//====================================================================================

#ifndef ARA_CORE_PROMISE_H_
#define ARA_CORE_PROMISE_H_

#include <exception>
#include <future>
#include <memory>
#include <mutex>
#include <system_error>
#include <utility>

#include "ara/core/error_code.h"
#include "ara/core/result.h"
#include "ara/core/future.h"
#include "ara/core/internal/state.h"

namespace ara {
namespace core {

/**
 * @brief ara::core specific variant of std::promise class
 *
 * @tparam T  the type of value
 * @tparam E  the type of error
 *
 * @traceid{SWS_CORE_00340}
 */
template <typename T, typename E = ErrorCode>
class Promise final {
    using R = Result<T, E>;
    using Lock = std::unique_lock<std::mutex>;

public:
    /// Alias type for T
    using ValueType = T;

    /**
     * @brief Default constructor
     *
     * This function behaves the same as the corresponding std::promise function.
     *
     * @traceid{SWS_CORE_00341}
     */
    Promise() : extra_state_(std::make_shared<internal::State<T, E>>()) {}

    /**
     * @brief Destructor for Promise objects
     *
     * This function behaves the same as the corresponding std::promise function.
     *
     * @traceid{SWS_CORE_00349}
     */
    ~Promise() {}

    /**
     * @brief Copy constructor shall be disabled.
     *
     * @traceid{SWS_CORE_00350}
     */
    Promise(Promise const&) = delete;

    /**
     * @brief Copy assignment operator shall be disabled.
     *
     * @traceid{SWS_CORE_00351}
     */
    Promise& operator=(Promise const&) = delete;

    /**
     * @brief Move constructor
     *
     * This function shall behave the same as the corresponding std::promise function.
     *
     * @param other  the other instance
     *
     * @traceid{SWS_CORE_00342}
     */
    Promise(Promise&& other) noexcept
        : lock_(other.mutex_)
        , delegate_promise_(std::move(other.delegate_promise_))
        , extra_state_(std::move(other.extra_state_)) {

        lock_.unlock();
    }

    /**
     * @brief Move assignment
     *
     * This function shall behave the same as the corresponding std::promise function.
     *
     * @param other  the other instance
     * @returns *this
     *
     * @traceid{SWS_CORE_00343}
     */
    Promise& operator=(Promise&& other) noexcept {
        if (this != &other) {
            Lock lhsLock(mutex_, std::defer_lock);
            Lock rhsLock(other.mutex_, std::defer_lock);
            std::lock(lhsLock, rhsLock);
            delegate_promise_ = std::move(other.delegate_promise_);
            extra_state_ = std::move(other.extra_state_);
        }
        return *this;
    }

    /**
     * @brief Swap the contents of this instance with another one's.
     *
     * This function shall behave the same as the corresponding std::promise function.
     *
     * @param other  the other instance
     *
     * @traceid{SWS_CORE_00352}
     */
    void swap(Promise& other) noexcept {
        Lock lhsLock(mutex_, std::defer_lock);
        Lock rhsLock(other.mutex_, std::defer_lock);
        std::lock(lhsLock, rhsLock);

        using std::swap;
        swap(delegate_promise_, other.delegate_promise_);
        swap(extra_state_, other.extra_state_);
    }
    /**
     * @brief Returns an associated Future for type T.
     *
     * The returned Future is set as soon as this Promise receives the result or an exception. This method must only be
     * called once as it is not allowed to have multiple Futures per Promise.
     *
     * @returns a Future for type T
     *
     * @traceid{SWS_CORE_00344}
     */
    Future<T, E> get_future() { return Future<T, E>(delegate_promise_.get_future(), extra_state_); }
    /**
     * @brief Move an error into the shared state and make the state ready.
     *
     * @param error  the error to store
     *
     * @traceid{SWS_CORE_00353}
     */
    // on one promise, SetError after set_exception will throw exception
    void SetError(E&& err) {
        Lock lock(mutex_);
        R r = R::FromError(std::move(err));
        delegate_promise_.set_value(r);
        extra_state_->FireContinuation();
    }

    /**
     * @brief Copy an error into the shared state and make the state ready.
     *
     * @param error  the error to store
     *
     * @traceid{SWS_CORE_00354}
     */
    // on one promise, SetError after set_exception will throw exception
    void SetError(E const& err) {
        Lock lock(mutex_);
        R r = R::FromError(err);
        delegate_promise_.set_value(r);
        extra_state_->FireContinuation();
    }

    /**
     * @brief Sets an exception.
     *
     * Calling Get() on the associated Future will rethrow the exception in the context the Future's method was
     * called
     * in.
     *
     * @param p exception_ptr to set
     *
     * @note This method is DEPRECATED. The exception is defined by the error code.
     */
    void set_exception(std::exception_ptr p) {
        Lock lock(mutex_);
        delegate_promise_.set_exception(p);
        extra_state_->FireContinuation();
    }

    /**
     * @brief Move the result into the future.
     *
     * @param value the value to store
     *
     * @traceid{SWS_CORE_00346}
     */
    void set_value(T&& value) {
        R r = std::move(value);
        Lock lock(mutex_);
        delegate_promise_.set_value(r);
        extra_state_->FireContinuation();
    }

    /**
     * @brief Copy result into the future.
     *
     * @param value the value to store
     *
     * @traceid{SWS_CORE_00345}
     */
    void set_value(T const& value) {
        R r = value;
        Lock lock(mutex_);
        delegate_promise_.set_value(r);
        extra_state_->FireContinuation();
    }

private:
    std::mutex mutex_;
    Lock lock_;
    std::promise<R> delegate_promise_;
    std::shared_ptr<internal::State<T, E>> extra_state_;
};

/**
 * @brief Explicit specialization of Promise for void
 * @tparam E  the type of error
 *
 * @traceid{SWS_CORE_06340}
 */
template <typename E>
class Promise<void, E> final {
    using R = Result<void, E>;

    using Lock = std::unique_lock<std::mutex>;

public:
    /// @copydoc Promise::ValueType
    using ValueType = void;

    /// @copydoc Promise::Promise
    /// @traceid{SWS_CORE_06341}
    Promise() : extra_state_(std::make_shared<internal::State<void, E>>()) {}

    /// @copydoc Promise::~Promise
    /// @traceid{SWS_CORE_06349}
    ~Promise() {}

    /// @copydoc Promise::Promise(const Promise&)
    /// @traceid{SWS_CORE_06350}
    Promise(Promise const&) = delete;

    /// @copydoc Promise::operator=(const Promise&)
    /// @traceid{SWS_CORE_06351}
    Promise& operator=(Promise const&) = delete;

    /**
     *
     * @copydoc Promise::Promise(Promise&&)
     * @traceid{SWS_CORE_06342}
     */
    Promise(Promise&& other) noexcept
        : delegate_promise_(std::move(other.delegate_promise_))
        , extra_state_(std::move(other.extra_state_))
        , lock_(other.mutex_) {
        lock_.unlock();
    }

    /**
     * @copydoc Promise::operator=(Promise&&)
     * @traceid{SWS_CORE_06343}
     */
    Promise& operator=(Promise&& other) noexcept {
        if (this != &other) {
            Lock lhsLock(mutex_, std::defer_lock);
            Lock rhsLock(other.mutex_, std::defer_lock);
            std::lock(lhsLock, rhsLock);

            delegate_promise_ = std::move(other.delegate_promise_);
            extra_state_ = std::move(other.extra_state_);
        }
        return *this;
    }

    /// @copydoc Promise::swap
    /// @traceid{SWS_CORE_06352}
    void swap(Promise& other) noexcept {
        Lock lhsLock(mutex_, std::defer_lock);
        Lock rhsLock(other.mutex_, std::defer_lock);
        std::lock(lhsLock, rhsLock);

        using std::swap;
        swap(delegate_promise_, other.delegate_promise_);
        swap(extra_state_, other.extra_state_);
    }

    /**
     * @copydoc Promise::get_future
     * @traceid{SWS_CORE_06344}
     */
    Future<void, E> get_future() { return Future<void, E>(delegate_promise_.get_future(), extra_state_); }

    /// @brief Make the shared state ready.
    ///
    /// @traceid{SWS_CORE_06345}
    void set_value() {
        Lock lock(mutex_);
        delegate_promise_.set_value(R::FromValue());
        extra_state_->FireContinuation();
    }

    /**
     * @copydoc Promise::SetError(E&&)
     * @traceid{SWS_CORE_06353}
     * on one promise, SetError after set_exception will throw exception
     */
    void SetError(E&& err) {
        R r = R::FromError(std::move(err));
        Lock lock(mutex_);
        delegate_promise_.set_value(r);
        extra_state_->FireContinuation();
    }

    /**
     * @copydoc Promise::SetError(const E&)
     * traceid{SWS_CORE_06354}
     * on one promise, SetError after set_exception will throw exception
     */
    void SetError(E const& err) {
        R r = R::FromError(err);
        Lock lock(mutex_);
        delegate_promise_.set_value(r);
        extra_state_->FireContinuation();
    }

    /**
     * @copydoc Promise::set_exception
     */
    void set_exception(std::exception_ptr p) {
        Lock lock(mutex_);
        delegate_promise_.set_exception(p);
        extra_state_->FireContinuation();
    }

private:
    std::promise<R> delegate_promise_;
    std::shared_ptr<internal::State<void, E>> extra_state_;
    std::mutex mutex_;
    Lock lock_;
};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_PROMISE_H_
