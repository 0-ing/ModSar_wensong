//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file         tests/VRTE_UT/mock/enable.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Hans Berghaell
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCK_ENABLE_H
#define TESTS_VRTE_UT_MOCK_ENABLE_H

#include <atomic>
#include <cstdint>
#include <exception>
#include <set>
#include <stdarg.h>
#include <type_traits>


//=============================================================================

#define UCM_MOCK_WEAK __attribute__((weak))

// enable mock for this scope

#define UCM_MOCK(...) bosch::vrte::ucm::mock::Mock mock_rai_var; \
    bosch::vrte::ucm::mock::Mock::wrap( __VA_ARGS__ )

// non-void return value declaration

#define UCM_MOCK_DECL(FNAME) \
UCM_MOCK_WEAK; \
decltype(FNAME) __real_##FNAME; \
extern bosch::vrte::ucm::mock::Mock::RetVal<decltype(FNAME)> __mock_##FNAME##_rv;

// void return function declaration

#define UCM_MOCK_DECLV(FNAME) \
UCM_MOCK_WEAK; \
decltype(FNAME) __real_##FNAME;

// non-void nullary function implementation

#define UCM_MOCK_IMPL0(RETVAL, FNAME) \
{ \
    if (bosch::vrte::ucm::mock::Mock::mock( FNAME )) \
        return __mock_##FNAME##_rv; \
    return __real_##FNAME(); \
} \
bosch::vrte::ucm::mock::Mock::RetVal<decltype(FNAME)> __mock_##FNAME##_rv = RETVAL;

// non-void non-nullary function implementation

#define UCM_MOCK_IMPL(RETVAL, FNAME, ...) \
{ \
    if (bosch::vrte::ucm::mock::Mock::mock( FNAME )) \
        return __mock_##FNAME##_rv; \
    return __real_##FNAME( __VA_ARGS__ ); \
} \
bosch::vrte::ucm::mock::Mock::RetVal<decltype(FNAME)> __mock_##FNAME##_rv = RETVAL;

// non-void variadic function implementations (i.e. has va_list alternative)

#define UCM_MOCK_IMPL1VA(RETVAL, FNAME, ARG0) \
{ \
    if (bosch::vrte::ucm::mock::Mock::mock( FNAME )) \
        return __mock_##FNAME##_rv; \
    va_list args; \
    va_start(args, ARG0); \
    return __real_v##FNAME( ARG0, args ); \
} \
bosch::vrte::ucm::mock::Mock::RetVal<decltype(FNAME)> __mock_##FNAME##_rv = RETVAL;

#define UCM_MOCK_IMPL2VA(RETVAL, FNAME, ARG0, ARG1) \
{ \
    if (bosch::vrte::ucm::mock::Mock::mock( FNAME )) \
        return __mock_##FNAME##_rv; \
    va_list args; \
    va_start(args, ARG1); \
    return __real_v##FNAME( ARG0, ARG1 , args ); \
} \
bosch::vrte::ucm::mock::Mock::RetVal<decltype(FNAME)> __mock_##FNAME##_rv = RETVAL;

#define UCM_MOCK_IMPL3VA(RETVAL, FNAME, ARG0, ARG1, ARG2) \
{ \
    if (bosch::vrte::ucm::mock::Mock::mock( FNAME )) \
        return __mock_##FNAME##_rv; \
    va_list args; \
    va_start(args, ARG2); \
    return __real_v##FNAME( ARG0, ARG1, ARG2, args ); \
} \
bosch::vrte::ucm::mock::Mock::RetVal<decltype(FNAME)> __mock_##FNAME##_rv = RETVAL;

// void return nullary implementation

#define UCM_MOCK_IMPLV0(FNAME) \
{ \
    if (not bosch::vrte::ucm::mock::Mock::mock( FNAME )) \
        __real_##FNAME(); \
}

// void return non-nullary implementation

#define UCM_MOCK_IMPLV(FNAME, ...) \
{ \
    if (not bosch::vrte::ucm::mock::Mock::mock( FNAME )) \
        __real_##FNAME( __VA_ARGS__ ); \
}

//=============================================================================

namespace bosch   {
namespace vrte    {
namespace ucm     {
namespace mock    {

//=============================================================================

struct Mock final
{
    template<typename> struct RetVal_;
    template<typename R, typename... U> struct RetVal_ <R(&)(U...    )> : RetVal_ <R(U...)> {};
    template<typename R, typename... U> struct RetVal_ <R(*)(U...    )> : RetVal_ <R(U...)> {};
    template<typename R, typename... U> struct RetVal_ <R   (U...    )> { using type = R; };
    template<typename R, typename... U> struct RetVal_ <R   (U...,...)> { using type = R; };
    template<typename U> using RetVal = typename RetVal_<U>::type;

    Mock();
   ~Mock();

    static std::atomic<bool>& mock();
    static std::atomic<bool>& strict();

    template <typename U> static bool mock(U&& u)
    {
        if (not mock())
            return false;
        if (is_real(static_cast<U&&>(u)))
            return false;
        if (is_wrap(static_cast<U&&>(u)))
            return true;
        if (strict())
            std::terminate();
        return false;
    }

    // real

    static std::set<std::uintptr_t>& reals();

    template<typename H> static bool is_real(H&& h)
    {
        return reals().count(reinterpret_cast<std::uintptr_t>(&h));
    }

    static void real();

    template<typename H, typename... T> static void real(H&& h, T&&... t)
    {
        if (is_wrap(static_cast<H&&>(h)))
            unwrap(h);
        reals().emplace(reinterpret_cast<std::uintptr_t>(&h));
        real(static_cast<T&&>(t)...);
    }

    static void unreal();

    template<typename H, typename... T> static void unreal(H&& h, T&&... t)
    {
        reals().erase(reinterpret_cast<std::uintptr_t>(&h));
        unreal(static_cast<T&&>(t)...);
    }

    // wrap

    static std::set<std::uintptr_t>& wraps();

    template<typename H> static bool is_wrap(H&& h)
    {
        return wraps().count(reinterpret_cast<std::uintptr_t>(&h));
    }

    static void wrap();

    template<typename H, typename... T> static void wrap(H&& h, T&&... t)
    {
        if (is_real(static_cast<H&&>(h)))
            unreal(h);
        wraps().emplace(reinterpret_cast<std::uintptr_t>(&h));
        wrap(static_cast<T&&>(t)...);
    }

    static void unwrap();

    template<typename H, typename... T> static void unwrap(H&& h, T&&... t)
    {
        wraps().erase(reinterpret_cast<std::uintptr_t>(&h));
        unwrap(static_cast<T&&>(t)...);
    }
};

//=============================================================================

// legacy definitions

namespace syscall {


struct MockedSyscall
{
    MockedSyscall(int *flag, bool onoff)
        : val_sauv_{*flag}
        , ptr_sauv_(flag)
      {
          *ptr_sauv_ = onoff ? 1 : 0;
          std::atomic_thread_fence(std::memory_order_release);
      }

      MockedSyscall(int *flag, int *flag_ex, bool onoff)
          : val_sauv_{*flag}
          , ptr_sauv_(flag)
          , val_sauv_ex_{*flag_ex}
          , ptr_sauv_ex_{flag_ex}
        {
            *ptr_sauv_ = onoff ? 1 : 0;
            *ptr_sauv_ex_ = onoff ? 1 : 0;
            std::atomic_thread_fence(std::memory_order_release);
        }

        // copy semantics
        MockedSyscall(const MockedSyscall&) = delete;
        MockedSyscall& operator=(const MockedSyscall&) = delete;

        // move semantic
        MockedSyscall(MockedSyscall&&) = delete;
        MockedSyscall& operator=(MockedSyscall&&) = delete;

        ~MockedSyscall()
        {
            std::atomic_thread_fence(std::memory_order_acquire);
            *ptr_sauv_ = val_sauv_;
            if (*ptr_sauv_ex_)
                *ptr_sauv_ex_ = val_sauv_ex_;
        }

        int  val_sauv_;
        int *ptr_sauv_;
        int  val_sauv_ex_{0};
        int *ptr_sauv_ex_{nullptr};
};

#define UCM_MOCK_SYSCALL_ENABLE(symbol) \
    ::bosch::vrte::ucm::mock::syscall::MockedSyscall \
        ucm_mock_syscall_symbol_##symbol (&__mock_##symbol##_on, true)

#define UCM_MOCK_SYSCALL_DISABLE(symbol) \
    ::bosch::vrte::ucm::mock::syscall::MockedSyscall \
        ucm_mock_syscall_symbol_##symbol (&__mock_##symbol##_on, false)

#define UCM_MOCK_SYSCALL_ENABLE_EX(symbol) \
    ::bosch::vrte::ucm::mock::syscall::MockedSyscall \
        ucm_mock_syscall_symbol_##symbol (&__mock_##symbol##_on, &__mock_##symbol##_ex, true)

#define UCM_MOCK_SYSCALL_DISABLE_EX(symbol) \
    ::bosch::vrte::ucm::mock::syscall::MockedSyscall \
        ucm_mock_syscall_symbol_##symbol (&__mock_##symbol##_on, &__mock_##symbol##_ex, false)


} // namespace syscall

//=============================================================================

} // namespace mock
} // namespace ucm
} // namespace vrte
} // namespace bosch

#endif // TESTS_VRTE_UT_MOCK_ENABLE_H
