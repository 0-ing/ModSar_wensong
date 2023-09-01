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

/// @file future.h
/// @brief Interface to class ara::core::Future
///
/// ara::core::Future is a composition of basic features of std::future
/// and methods borrowed from the C++ proposal N3857.
//==================================================================================

#ifndef ARA_CORE_FUTURE_H_
#define ARA_CORE_FUTURE_H_

#include <chrono>
#include <future>
#include <system_error>
#include <cassert>
#include <utility>
#include <memory>

#include "ara/core/error_code.h"
#include "ara/core/result.h"
#include "ara/core/core_error_domain.h"
#include "ara/core/exception.h"
#include "ara/core/future_error_domain.h"
#include "ara/core/internal/state.h"

namespace ara {
namespace core {

/* Forward declaration */
template <typename, typename>
class Promise;

/// @brief Specifies the state of a Future as returned by wait_for() and wait_until().
///
/// These definitions are equivalent to the ones from std::future_status. However, no
/// item equivalent to std::future_status::deferred is available here.
///
/// The numerical values of the enum items are implementation-defined.
///
/// @traceid{SWS_CORE_00361}
enum class future_status : uint8_t {
    kReady = 1, ///< the shared state is ready
    kTimeout,   ///< the shared state did not become ready before the specified timeout has passed
};

inline std::ostream& operator<<(std::ostream& out, FutureException const& ex) {
    return (out << "FutureException: " << ex.Error() << " (" << ex.what() << ")");
}

/// @brief Provides ara::core specific Future operations to collect the results of an asynchronous call.
///
/// @tparam T  the type of values
/// @tparam E  the type of errors
///
/// Much of its functionality is delegated to std::future and all methods that resemble std::future are guaranteed to
/// behave the same.
///
/// If the valid() member function of an instance returns true, all other methods are guaranteed to work on that
/// instance. Otherwise, they may fail with or without an exception. A thrown exception will be of type
/// std::future_error.
///
/// Having an invalid future will usually happen when the future was moved from using the move constructor or move
/// assignment.
///
/// @traceid{SWS_CORE_00321}
template <typename T, typename E = ErrorCode>
class Future final {
    using R = Result<T, E>;
    using Lock = std::unique_lock<std::mutex>;

public:
    /// Alias type for T
    using ValueType = T;
    /// Alias type for the Promise type collaborating with this Future type
    using PromiseType = Promise<T, E>;
    /// Alias type for the future_status type
    using Status = future_status;

    template <typename, typename>
    friend class Future;

    /// @brief Default constructor
    ///
    /// @traceid{SWS_CORE_00322}
    Future() noexcept = default;

    /// @brief Move construct from another instance.
    ///
    /// @param other  the other instance
    ///
    /// @traceid{SWS_CORE_00323}
    Future(Future&& other) noexcept
        : delegate_future_(std::move(other.delegate_future_))
        , extra_state_(std::move(other.extra_state_))
        , lock_(other.mutex_) {
        lock_.unlock();
    }

    /// @brief Move assign from another instance.
    ///
    /// @param other  the other instance
    /// @returns *this
    ///
    /// @traceid{SWS_CORE_00325}
    Future& operator=(Future&& other) noexcept {
        if (this != &other) {
            Lock lhsLock(mutex_, std::defer_lock);
            Lock rhsLock(other.mutex_, std::defer_lock);
            std::lock(lhsLock, rhsLock);

            delegate_future_ = std::move(other.delegate_future_);
            extra_state_ = std::move(other.extra_state_);
        }
        return *this;
    }

    /// @brief Destructor for Future objects
    ///
    /// @traceid{SWS_CORE_00333}
    ~Future() noexcept = default;

    /// @brief Copy constructor shall be disabled.
    ///
    /// @traceid{SWS_CORE_00334}
    Future(Future const&) = delete;

    /// @brief Copy assignment operator shall be disabled.
    ///
    /// @traceid{SWS_CORE_00335}
    Future& operator=(Future const&) = delete;

    // Stop defining noexcept in order to let other exception be propageted to upper levels and fix some crashes
    /// @brief Get the result.
    ///
    /// Similar to get(), this call blocks until the value or an error is available.
    /// However, this call will never throw an exception.
    ///
    /// @returns a Result with either a value or an error
    /// @error Domain:error  the error that has been put into the corresponding Promise via Promise::SetError
    /// @note Adding [[nodiscard]] to issue complier warnings if the return value of this function is ignored
    ///       is not supported by c++14
    ///
    /// @traceid{SWS_CORE_00336}
    Result<T, E> GetResult() noexcept {
#ifndef ARA_NO_EXCEPTIONS
        try {
            return delegate_future_.get();
        } catch (std::future_error const& ex) {
            std::error_code const& ec = ex.code();
            future_errc err;
            if (ec == std::future_errc::broken_promise) {
                err = future_errc::broken_promise;
            } else if (ec == std::future_errc::future_already_retrieved) {
                err = future_errc::future_already_retrieved;
            } else if (ec == std::future_errc::promise_already_satisfied) {
                err = future_errc::promise_already_satisfied;
            } else if (ec == std::future_errc::no_state) {
                err = future_errc::no_state;
            } else {
                // Should rather use a vendor/demonstrator-specific ErrorDomain here?
                return R::FromError(CoreErrc::kInvalidArgument);
            }
            return R::FromError(err);
        } catch (std::exception& e) {
            // catching exception from delegate_future_.get()
            std::cerr << "Exception in ara::core::Future<T,E>::GetResult(): " << e.what() << '\n';
            future_errc err = future_errc::broken_promise;
            return R::FromError(err);
        }
#else
        // TODO: Somehow query the future object whether it contains an exception,
        // and if so, translate it into a Result<...>
        // This does not seem possible with C++14's std::future, because it lacks boost::future's
        // has_exception() method. Unfortunately, boost::future cannot be compiled with
        // -fno-exceptions, so that one is out as well.
        return delegate_future_.get();
#endif
    }

#ifndef ARA_NO_EXCEPTIONS

    /// @brief Get the value.
    ///
    /// This call blocks until the result or an exception is available.
    ///
    /// This function does not participate in overload resolution when the compiler toolchain
    /// does not support C++ exceptions.
    ///
    /// @returns value of type T
    /// @error Domain:error  the error that has been put into the corresponding Promise via Promise::SetError
    ///
    /// @traceid{SWS_CORE_00326}
    T get() { return GetResult().ValueOrThrow(); }
#endif

    /// @brief Checks if the Future is valid, i.e. if it has a shared state.
    ///
    /// @returns true if the Future is usable, false otherwise
    ///
    /// @traceid{SWS_CORE_00327}
    bool valid() const noexcept { return delegate_future_.valid(); }

    /// @brief Wait for a value or an error to be available.
    ///
    /// After this method returns, get() is guaranteed to not block and is_ready() will return true.
    ///
    /// @traceid{SWS_CORE_00328}
    void wait() const { delegate_future_.wait(); }

    /// @brief Wait for the given period, or until a value or an error is available.
    ///
    /// If the Future becomes ready or the timeout is reached, the method returns.
    ///
    /// @param timeoutDuration  maximal duration to wait for
    /// @returns status that indicates whether the timeout hit or if a value is available
    ///          0 is returned in case of std::future_status::deferred - to eliminate -Wreturn-value
    ///          compiler warnings. It is the responsibility of the caller to validate non-zero return
    ///          values, and log an error if this function returns 0.
    /// TODO: Check R20-11 for support of ara::core::future_status::kDeferred. If not supported, log
    ///       error in the default case by using future_errc::no_state (defined in FutureErrorDomain)
    ///
    /// @traceid{SWS_CORE_00329}
    template <typename Rep, typename Period>
    future_status wait_for(std::chrono::duration<Rep, Period> const& timeout_duration) const {
        switch (delegate_future_.wait_for(timeout_duration)) {
            case std::future_status::ready:
                return future_status::kReady;
            case std::future_status::timeout:
                return future_status::kTimeout;
            default:
                assert(!"this std::future_status should not occur in our setup");
                return static_cast<future_status>(0);
        }
    }

    /// @brief Wait until the given time, or until a value or an error is available.
    ///
    /// If the Future becomes ready or the time is reached, the method returns.
    ///
    /// @param deadline latest point in time to wait
    /// @returns status that indicates whether the time was reached or if a value is available.
    ///          0 is returned in case of std::future_status::deferred - to eliminate -Wreturn-value
    ///          compiler warnings. It is the responsibility of the caller to validate non-zero return
    ///          values, and log an error if this function returns 0.
    /// TODO: Check R20-11 for support of ara::core::future_status::kDeferred. If not supported, log
    ///       error in the default case by using future_errc::no_state (defined in FutureErrorDomain)
    ///
    /// @traceid{SWS_CORE_00330}
    template <typename Clock, typename Duration>
    future_status wait_until(std::chrono::time_point<Clock, Duration> const& deadline) const {
        switch (delegate_future_.wait_until(deadline)) {
            case std::future_status::ready:
                return future_status::kReady;
            case std::future_status::timeout:
                return future_status::kTimeout;
            default:
                assert(!"this std::future_status should not occur in our setup");
                return static_cast<future_status>(0);
        }
    }

    /// @brief Trait that detects whether a type is a Future<...>
    template <typename U>
    struct is_future : std::false_type { };

    template <typename U, typename G>
    struct is_future<Future<U, G>> : std::true_type { };

    /// @brief Trait that detects whether a type is a Result<...>
    template <typename U>
    struct is_result : std::false_type { };

    template <typename U, typename G>
    struct is_result<Result<U, G>> : std::true_type { };

    template <typename F>
    using CallableReturnsResult = std::enable_if_t<is_result<std::result_of_t<std::decay_t<F>(Future<T, E>)>>::value>;

    template <typename F>
    using CallableReturnsFuture = std::enable_if_t<is_future<std::result_of_t<std::decay_t<F>(Future<T, E>)>>::value>;

    template <typename F>
    using CallableReturnsValueType
        = std::enable_if_t<!is_future<std::result_of_t<std::decay_t<F>(Future<T, E>)>>::value
                           && !is_result<std::result_of_t<std::decay_t<F>(Future<T, E>)>>::value
                           && !std::is_void<std::result_of_t<std::decay_t<F>(Future<T, E>)>>::value>;

    template <typename F>
    using CallableReturnsVoid = std::enable_if_t<std::is_void<std::result_of_t<std::decay_t<F>(Future<T, E>)>>::value>;

    /// Alias type for T
    using value_type = T;
    /// Alias type for E
    using error_type = E;

private:
    template <class Successor>
    void handle_future_error(Successor& successor_promise_, const std::future_error& ex) {
        std::error_code const& ec = ex.code();
        future_errc err;
        switch (ec.value()) {
            case static_cast<int>(std::future_errc::broken_promise):
                err = future_errc::broken_promise;
                break;
            case static_cast<int>(std::future_errc::future_already_retrieved):
                err = future_errc::future_already_retrieved;
                break;
            case static_cast<int>(std::future_errc::promise_already_satisfied):
                err = future_errc::promise_already_satisfied;
                break;
            case static_cast<int>(std::future_errc::no_state):
                err = future_errc::no_state;
                break;
            default:
                successor_promise_.SetError(CoreErrc::kInvalidArgument);
                return;
        }
        successor_promise_.SetError(err);
    }

    template <class Successor>
    void handle_exception(Successor& successor_promise_, const std::exception& ex) {
        std::cerr << "Exception in continuation attached to then(): " << ex.what() << '\n';
        future_errc err = future_errc::broken_promise;
        successor_promise_.SetError(err);
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<!std::is_void<
                  typename std::result_of_t<std::decay_t<F>(Future<T, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_future(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            using U = std::result_of_t<std::decay_t<F>(Future<T, E>)>;

            using T3 = typename U::value_type;
            using E3 = typename U::error_type;

            // callback returns another future: inner_future, when inner_future is done, next_future can be done
            Future<T3, E3> inner_future;
            inner_future = std::forward<F>(func_)(std::move(predecessor_future_));

            if (!inner_future.valid()) {
                successor_promise_.SetError(ara::core::future_errc::broken_promise);
                return;
            }

            std::unique_lock<std::mutex> inner_lock(inner_future.extra_state_->mutex_);

            auto inner_continuation
                = [outer_promise = std::move(successor_promise_)](Future<T3, E3> inner_future) mutable {
                      auto result = inner_future.GetResult();
                      if (result.HasValue()) {
                          outer_promise.set_value(result.Value());
                      } else {
                          outer_promise.SetError(result.Error());
                      }
                  };

            if (inner_future.is_ready()) {
                inner_lock.unlock();
                inner_continuation(std::move(inner_future));
            } else {
                inner_future.extra_state_->SetContinuation(std::move(inner_continuation), inner_future);
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<
                  std::is_void<typename std::result_of_t<std::decay_t<F>(Future<T, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_future(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            using U = std::result_of_t<std::decay_t<F>(Future<T, E>)>;

            using T3 = typename U::value_type;
            using E3 = typename U::error_type;

            // callback returns another future: inner_future, when inner_future is done, next_future can be done
            Future<T3, E3> inner_future;
            inner_future = std::forward<F>(func_)(std::move(predecessor_future_));

            if (!inner_future.valid()) {
                successor_promise_.SetError(ara::core::future_errc::broken_promise);
                return;
            }

            std::unique_lock<std::mutex> inner_lock(inner_future.extra_state_->mutex_);

            auto inner_continuation
                = [outer_promise = std::move(successor_promise_)](Future<T3, E3> inner_future) mutable {
                      auto result = inner_future.GetResult();
                      if (result.HasValue()) {
                          outer_promise.set_value();
                      } else {
                          outer_promise.SetError(result.Error());
                      }
                  };

            if (inner_future.is_ready()) {
                inner_lock.unlock();
                inner_continuation(std::move(inner_future));
            } else {
                inner_future.extra_state_->SetContinuation(std::move(inner_continuation), inner_future);
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<!std::is_void<
                  typename std::result_of_t<std::decay_t<F>(Future<T, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_result(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            auto result = std::forward<F>(func_)(std::move(predecessor_future_));
            if (result.HasValue()) {
                successor_promise_.set_value(result.Value());
            } else {
                successor_promise_.SetError(result.Error());
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<
                  std::is_void<typename std::result_of_t<std::decay_t<F>(Future<T, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_result(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            auto result = std::forward<F>(func_)(std::move(predecessor_future_));
            if (result.HasValue()) {
                successor_promise_.set_value();
            } else {
                successor_promise_.SetError(result.Error());
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F, class Successor, class Predecessor>
    void
    fulfill_promise_valuetype(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            auto result = std::forward<F>(func_)(std::move(predecessor_future_));
            successor_promise_.set_value(result);
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F, class Successor, class Predecessor>
    void fulfill_promise_void(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            std::forward<F>(func_)(std::move(predecessor_future_));
            successor_promise_.set_value();
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

public:
    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_00331}
    template <typename F, typename = CallableReturnsFuture<F>>
    auto then(F&& func) -> std::result_of_t<std::decay_t<F>(Future<T, E>)> {
        Lock lock(extra_state_->mutex_);

        using U = std::result_of_t<std::decay_t<F>(Future<T, E>)>;

        using T2 = typename U::value_type;
        using E2 = typename U::error_type;

        Promise<T2, E2> next_promise;
        auto next_future = next_promise.get_future();

        Future<T, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<T, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_future(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_00331}
    template <typename F, typename = CallableReturnsResult<F>>
    auto then(F&& func) -> Future<typename std::result_of_t<std::decay_t<F>(Future<T, E>)>::value_type,
                                  typename std::result_of_t<std::decay_t<F>(Future<T, E>)>::error_type> {
        Lock lock(extra_state_->mutex_);

        using U = std::result_of_t<std::decay_t<F>(Future<T, E>)>;

        using T2 = typename U::value_type;
        using E2 = typename U::error_type;

        Promise<T2, E2> next_promise;
        auto next_future = next_promise.get_future();

        Future<T, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<T, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_result(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_00331}
    template <typename F, typename = CallableReturnsValueType<F>>
    auto then(F&& func) -> Future<std::result_of_t<std::decay_t<F>(Future<T, E>)>, E> {
        Lock lock(extra_state_->mutex_);

        using U = std::result_of_t<std::decay_t<F>(Future<T, E>)>;

        Promise<U, E> next_promise;
        auto next_future = next_promise.get_future();

        Future<T, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<T, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_valuetype(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_00331}
    template <typename F, typename = CallableReturnsVoid<F>>
    auto then(F&& func) -> Future<void, E> {
        Lock lock(extra_state_->mutex_);

        Promise<void, E> next_promise;
        auto next_future = next_promise.get_future();

        Future<T, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<T, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_void(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @brief Return whether the asynchronous operation has finished.
    ///
    /// If is_ready() returns true, get() and the wait calls are guaranteed to not block.
    ///
    /// @returns true if the Future contains a value or an error, false otherwise
    ///
    /// @traceid{SWS_CORE_00332}
    bool is_ready() const {
        return std::future_status::ready == delegate_future_.wait_for(std::chrono::seconds::zero());
    }

private:
    /// @brief Constructs a Future from a given std::future and a pointer to the extra state.
    ///
    /// @param delegate_future std::future instance
    /// @param extra_state state that is shared with the Promise
    Future(std::future<R>&& delegate_future, std::shared_ptr<internal::State<T, E>> extra_state)
        : delegate_future_(std::move(delegate_future)), extra_state_(extra_state) { }

    std::future<R> delegate_future_;
    std::shared_ptr<internal::State<T, E>> extra_state_;
    std::mutex mutex_;
    Lock lock_;
    template <typename, typename>
    friend class Promise;
    friend class internal::State<T, E>;
};

/// @brief Specialization of class Future for "void" values
/// @tparam E  the type of error
///
/// @traceid{SWS_CORE_06221}
template <typename E>
class Future<void, E> final {
    using R = Result<void, E>;

    using Lock = std::unique_lock<std::mutex>;

public:
    /// Alias type for T
    using ValueType = void;
    /// Alias type for the Promise type collaborating with this Future type
    using PromiseType = Promise<void, E>;
    /// Alias type for the future_status type
    using Status = future_status;

    template <typename, typename>
    friend class Future;

    /// @traceid{SWS_CORE_06222}
    /// @copydoc Future::Future
    Future() noexcept = default;

    /// @traceid{SWS_CORE_06233}
    /// @copydoc Future::~Future
    ~Future() noexcept = default;

    /// @traceid{SWS_CORE_06234}
    /// @copydoc Future::Future(const Future&)
    Future(Future const& other) = delete;

    /// @traceid{SWS_CORE_06235}
    /// @copydoc Future::operator=(const Future&)
    Future& operator=(Future const&) = delete;

    /// @traceid{SWS_CORE_06223}
    /// @copydoc Future::Future(Future&&)
    Future(Future&& other) noexcept
        : lock_(other.mutex_)
        , delegate_future_(std::move(other.delegate_future_))
        , extra_state_(std::move(other.extra_state_)) {
        lock_.unlock();
    }

    /// @traceid{SWS_CORE_06225}
    /// @copydoc Future::operator=(Future&&)
    Future& operator=(Future&& other) noexcept {
        if (this != &other) {
            Lock lhsLock(mutex_, std::defer_lock);
            Lock rhsLock(other.mutex_, std::defer_lock);
            std::lock(lhsLock, rhsLock);

            delegate_future_ = std::move(other.delegate_future_);
            extra_state_ = std::move(other.extra_state_);
        }
        return *this;
    }

#ifndef ARA_NO_EXCEPTIONS
    /// @traceid{SWS_CORE_06226}
    /// @copydoc Future::get
    void get() { return GetResult().ValueOrThrow(); }
#endif

    /// @traceid{SWS_CORE_06236}
    /// @copydoc Future::GetResult
    Result<void, E> GetResult() noexcept {
#ifndef ARA_NO_EXCEPTIONS
        try {
            return delegate_future_.get();
        } catch (std::future_error const& ex) {
            std::error_code const& ec = ex.code();
            future_errc err;
            if (ec == std::future_errc::broken_promise) {
                err = future_errc::broken_promise;
            } else if (ec == std::future_errc::future_already_retrieved) {
                err = future_errc::future_already_retrieved;
            } else if (ec == std::future_errc::promise_already_satisfied) {
                err = future_errc::promise_already_satisfied;
            } else if (ec == std::future_errc::no_state) {
                err = future_errc::no_state;
            } else {
                // Should rather use a vendor/demonstrator-specific ErrorDomain here?
                return R::FromError(CoreErrc::kInvalidArgument);
            }
            return R::FromError(err);
        } catch (std::exception& e) {
            // catching exception from delegate_future_.get()
            std::cerr << "Exception in ara::core::Future<void,E>::GetResult(): " << e.what() << '\n';
            future_errc err = future_errc::broken_promise;
            return R::FromError(err);
        }
#else
        return delegate_future_.get();
#endif
    }

    /// @traceid{SWS_CORE_06227}
    /// @copydoc Future::valid
    bool valid() const noexcept { return delegate_future_.valid(); }

    /// @traceid{SWS_CORE_06228}
    /// @copydoc Future::wait
    void wait() const { delegate_future_.wait(); }

    /// @traceid{SWS_CORE_06229}
    /// @copydoc Future::wait_for
    template <typename Rep, typename Period>
    future_status wait_for(std::chrono::duration<Rep, Period> const& timeoutDuration) const {
        switch (delegate_future_.wait_for(timeoutDuration)) {
            case std::future_status::ready:
                return future_status::kReady;
            case std::future_status::timeout:
                return future_status::kTimeout;
            default:
                assert(!"this std::future_status should not occur in our setup");
                return static_cast<future_status>(0);
        }
    }

    /// @traceid{SWS_CORE_06230}
    /// @copydoc Future::wait_until
    template <typename Clock, typename Duration>
    future_status wait_until(std::chrono::time_point<Clock, Duration> const& deadline) const {
        switch (delegate_future_.wait_until(deadline)) {
            case std::future_status::ready:
                return future_status::kReady;
            case std::future_status::timeout:
                return future_status::kTimeout;
            default:
                assert(!"this std::future_status should not occur in our setup");
                return static_cast<future_status>(0);
        }
    }

    /// @brief Trait that detects whether a type is a Future<...>
    template <typename U>
    struct is_future : std::false_type { };

    template <typename U, typename G>
    struct is_future<Future<U, G>> : std::true_type { };

    /// @brief Trait that detects whether a type is a Result<...>
    template <typename U>
    struct is_result : std::false_type { };

    template <typename U, typename G>
    struct is_result<Result<U, G>> : std::true_type { };

    template <typename F>
    using CallableReturnsResult
        = std::enable_if_t<is_result<std::result_of_t<std::decay_t<F>(Future<void, E>)>>::value>;

    template <typename F>
    using CallableReturnsFuture
        = std::enable_if_t<is_future<std::result_of_t<std::decay_t<F>(Future<void, E>)>>::value>;

    template <typename F>
    using CallableReturnsValueType
        = std::enable_if_t<!is_future<std::result_of_t<std::decay_t<F>(Future<void, E>)>>::value
                           && !is_result<std::result_of_t<std::decay_t<F>(Future<void, E>)>>::value
                           && !std::is_void<std::result_of_t<std::decay_t<F>(Future<void, E>)>>::value>;

    template <typename F>
    using CallableReturnsVoid
        = std::enable_if_t<std::is_void<std::result_of_t<std::decay_t<F>(Future<void, E>)>>::value>;

    /// Alias type for void
    using value_type = void;
    /// Alias type for E
    using error_type = E;

private:
    template <class Successor>
    void handle_future_error(Successor& successor_promise_, const std::future_error& ex) {
        std::error_code const& ec = ex.code();
        future_errc err;
        switch (ec.value()) {
            case static_cast<int>(std::future_errc::broken_promise):
                err = future_errc::broken_promise;
                break;
            case static_cast<int>(std::future_errc::future_already_retrieved):
                err = future_errc::future_already_retrieved;
                break;
            case static_cast<int>(std::future_errc::promise_already_satisfied):
                err = future_errc::promise_already_satisfied;
                break;
            case static_cast<int>(std::future_errc::no_state):
                err = future_errc::no_state;
                break;
            default:
                successor_promise_.SetError(CoreErrc::kInvalidArgument);
                return;
        }
        successor_promise_.SetError(err);
    }

    template <class Successor>
    void handle_exception(Successor& successor_promise_, const std::exception& ex) {
        std::cerr << "Exception in continuation attached to then(): " << ex.what() << '\n';
        future_errc err = future_errc::broken_promise;
        successor_promise_.SetError(err);
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<!std::is_void<
                  typename std::result_of_t<std::decay_t<F>(Future<void, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_future(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            using U = std::result_of_t<std::decay_t<F>(Future<void, E>)>;

            using T3 = typename U::value_type;
            using E3 = typename U::error_type;

            // callback returns another future: inner_future, when inner_future is done, next_future can be done
            Future<T3, E3> inner_future;
            inner_future = std::forward<F>(func_)(std::move(predecessor_future_));

            if (!inner_future.valid()) {
                successor_promise_.SetError(ara::core::future_errc::broken_promise);
                return;
            }

            std::unique_lock<std::mutex> inner_lock(inner_future.extra_state_->mutex_);

            auto inner_continuation
                = [outer_promise = std::move(successor_promise_)](Future<T3, E3> inner_future) mutable {
                      auto result = inner_future.GetResult();
                      if (result.HasValue()) {
                          outer_promise.set_value(result.Value());
                      } else {
                          outer_promise.SetError(result.Error());
                      }
                  };

            if (inner_future.is_ready()) {
                inner_lock.unlock();
                inner_continuation(std::move(inner_future));
            } else {
                inner_future.extra_state_->SetContinuation(std::move(inner_continuation), inner_future);
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<std::is_void<
                  typename std::result_of_t<std::decay_t<F>(Future<void, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_future(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            using U = std::result_of_t<std::decay_t<F>(Future<void, E>)>;

            using T3 = typename U::value_type;
            using E3 = typename U::error_type;

            // callback returns another future: inner_future, when inner_future is done, next_future can be done
            Future<T3, E3> inner_future;
            inner_future = std::forward<F>(func_)(std::move(predecessor_future_));

            if (!inner_future.valid()) {
                successor_promise_.SetError(ara::core::future_errc::broken_promise);
                return;
            }

            std::unique_lock<std::mutex> inner_lock(inner_future.extra_state_->mutex_);

            auto inner_continuation
                = [outer_promise = std::move(successor_promise_)](Future<T3, E3> inner_future) mutable {
                      auto result = inner_future.GetResult();
                      if (result.HasValue()) {
                          outer_promise.set_value();
                      } else {
                          outer_promise.SetError(result.Error());
                      }
                  };

            if (inner_future.is_ready()) {
                inner_lock.unlock();
                inner_continuation(std::move(inner_future));
            } else {
                inner_future.extra_state_->SetContinuation(std::move(inner_continuation), inner_future);
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<!std::is_void<
                  typename std::result_of_t<std::decay_t<F>(Future<void, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_result(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            auto result = std::forward<F>(func_)(std::move(predecessor_future_));
            if (result.HasValue()) {
                successor_promise_.set_value(result.Value());
            } else {
                successor_promise_.SetError(result.Error());
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F,
              class Successor,
              class Predecessor,
              typename std::enable_if_t<std::is_void<
                  typename std::result_of_t<std::decay_t<F>(Future<void, E>)>::value_type>::value>* = nullptr>
    void fulfill_promise_result(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            auto result = std::forward<F>(func_)(std::move(predecessor_future_));
            if (result.HasValue()) {
                successor_promise_.set_value();
            } else {
                successor_promise_.SetError(result.Error());
            }
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F, class Successor, class Predecessor>
    void
    fulfill_promise_valuetype(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            auto result = std::forward<F>(func_)(std::move(predecessor_future_));
            successor_promise_.set_value(result);
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

    template <typename F, class Successor, class Predecessor>
    void fulfill_promise_void(F&& func_, Successor& successor_promise_, Future<Predecessor, E>& predecessor_future_) {
        try {
            std::forward<F>(func_)(std::move(predecessor_future_));
            successor_promise_.set_value();
        } catch (std::future_error const& ex) {
            handle_future_error(successor_promise_, ex);
        } catch (std::exception const& e) {
            handle_exception(successor_promise_, e);
        }
    }

public:
    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_06231}
    template <typename F, typename = CallableReturnsFuture<F>>
    auto then(F&& func) -> std::result_of_t<std::decay_t<F>(Future<void, E>)> {
        Lock lock(extra_state_->mutex_);

        using U = std::result_of_t<std::decay_t<F>(Future<void, E>)>;

        using T2 = typename U::value_type;
        using E2 = typename U::error_type;

        Promise<T2, E2> next_promise;
        auto next_future = next_promise.get_future();

        Future<void, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<void, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_future(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_06231}
    template <typename F, typename = CallableReturnsResult<F>>
    auto then(F&& func) -> Future<typename std::result_of_t<std::decay_t<F>(Future<void, E>)>::value_type,
                                  typename std::result_of_t<std::decay_t<F>(Future<void, E>)>::error_type> {
        Lock lock(extra_state_->mutex_);

        using U = std::result_of_t<std::decay_t<F>(Future<void, E>)>;

        using T2 = typename U::value_type;
        using E2 = typename U::error_type;

        Promise<T2, E2> next_promise;
        auto next_future = next_promise.get_future();

        Future<void, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<void, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_result(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_06231}
    template <typename F, typename = CallableReturnsValueType<F>>
    auto then(F&& func) -> Future<std::result_of_t<std::decay_t<F>(Future<void, E>)>, E> {
        Lock lock(extra_state_->mutex_);

        using U = std::result_of_t<std::decay_t<F>(Future<void, E>)>;

        Promise<U, E> next_promise;
        auto next_future = next_promise.get_future();

        Future<void, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<void, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_valuetype(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @brief Register a callable that gets called when the Future becomes ready.
    ///
    /// When @a func is called, it is guaranteed that get() will not block.
    ///
    /// @a func may be called in the context of this call or in the context of Promise::set_value()
    /// or Promise::SetError() or somewhere else.
    ///
    /// The return type of @a then depends on the return type of @a func (aka continuation).
    ///
    /// @param func  a callable to register to get the Future result or an exception
    /// @returns a new Future instance for the result of the continuation
    ///
    /// @traceid{SWS_CORE_06231}
    template <typename F, typename = CallableReturnsVoid<F>>
    auto then(F&& func) -> Future<void, E> {
        Lock lock(extra_state_->mutex_);

        Promise<void, E> next_promise;
        auto next_future = next_promise.get_future();

        Future<void, E>& predecessor_future = *this;

        // creates a continuation which fulfills the promise
        auto continuation = [promise = std::move(next_promise),
                             func(std::forward<F>(func))](Future<void, E> predecessor_future) mutable {
            predecessor_future.fulfill_promise_void(func, promise, predecessor_future);
        };

        if (predecessor_future.is_ready()) {
            // the state is ready, invoke the continuation immediately
            // unlock here so that Future passed to the continuation below doesn't block in .get()
            lock.unlock();
            continuation(std::move(predecessor_future));
        } else {
            // the state is not yet ready, continuation is stored
            // continuation is invoked in the context of Promise::set_value() or Promise::SetError()
            extra_state_->SetContinuation(std::move(continuation), predecessor_future);
        }

        return next_future;
    }

    /// @traceid{SWS_CORE_06232}
    /// @copydoc Future::is_ready
    bool is_ready() const {
        return std::future_status::ready == delegate_future_.wait_for(std::chrono::seconds::zero());
    }

private:
    Future(std::future<R>&& delegate_future, std::shared_ptr<internal::State<void, E>> extra_state)
        : delegate_future_(std::move(delegate_future)), extra_state_(extra_state) { }

    std::mutex mutex_;
    Lock lock_; // this Lock is only necessary for the move constructor
    std::future<R> delegate_future_;
    std::shared_ptr<internal::State<void, E>> extra_state_;
    template <typename, typename>
    friend class Promise;
    friend class internal::State<void, E>;
};
} // namespace core
} // namespace ara

#endif // ARA_CORE_FUTURE_H_
