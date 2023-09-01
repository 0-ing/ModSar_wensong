//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/utl/observer.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_UTL__OBSERVER_H_
#define UCM_AAP_LIBRARY_UCM_LIB_UTL__OBSERVER_H_

#include <set>
#include <mutex>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

template<typename T>
class ObserverClient
        : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl__ObserverClient, CTor);
#endif
public:
    ObserverClient(ObserverClient     &&) = default;
    ObserverClient(ObserverClient const&) = default;

    ObserverClient& operator=(ObserverClient     &&) = default;
    ObserverClient& operator=(ObserverClient const&) = default;

    virtual ~ObserverClient() = default;

    virtual void update(const T& state) noexcept = 0;

protected:
    explicit ObserverClient() = default;
};

template<typename T>
class ObserverSubject
        : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl__ObserverSubject, CTor);
    FRIEND_TEST(Test_ucm_lib_utl__ObserverSubject, Add);
    FRIEND_TEST(Test_ucm_lib_utl__ObserverSubject, Del);
    FRIEND_TEST(Test_ucm_lib_utl__ObserverSubject, Set);
#endif
public:
    explicit ObserverSubject(T&& value)
            noexcept(std::is_nothrow_move_constructible<T>::value)
        : value_(std::move(value))
    {}

    explicit ObserverSubject(const T& value)
            noexcept(std::is_nothrow_copy_constructible<T>::value)
        : value_{value}
    {}

    ObserverSubject(ObserverSubject     &&) = delete;
    ObserverSubject(ObserverSubject const&) = delete;

    ObserverSubject& operator=(ObserverSubject     &&) = delete;
    ObserverSubject& operator=(ObserverSubject const&) = delete;

    virtual ~ObserverSubject() = default;

    void add(ObserverClient<T> *obs)
    {
        pop<void>();
    }

    void del(ObserverClient<T> *obs)
    {
        pop<void>();
    }

    template<class U,
        std::enable_if_t<
            std::is_same<U, T>::value ||
            std::is_move_constructible<U>::value, bool> = true>
    void set(U&& value)
    {
        pop<void>();
    }

    template<class U,
        std::enable_if_t<
            std::is_same<U, T>::value ||
            std::is_copy_constructible<U>::value, bool> = true>
    void set(const U& value)
    {
        pop<void>();
    }

    const T get() const noexcept
    {
       return pop<const T>();
    }

protected:
    T value_{};
    mutable std::mutex mutex_{};

    template<class U,
        std::enable_if_t<
            std::is_same<U, T>::value ||
            std::is_move_constructible<U>::value, bool> = true>
    void set_nolock(U&& value)
    {
        pop<void>();
    }

    template<class U,
        std::enable_if_t<
            std::is_same<U, T>::value ||
            std::is_copy_constructible<U>::value, bool> = true>
    void set_nolock(const U& value)
    {
        pop<void>();
    }

private:
    std::set<ObserverClient<T> *> clients_{};

    void notify() noexcept
    {
        pop<void>();
    }
};

}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif /* UCM_AAP_LIBRARY_UCM_LIB_UTL__OBSERVER_H_ */
