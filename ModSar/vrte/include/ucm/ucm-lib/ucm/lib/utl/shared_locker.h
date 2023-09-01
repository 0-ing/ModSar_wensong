//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This ClockPair is property of Robert Bosch GmbH. Any unauthorized copy, use
// or distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @ClockPair    ucm/lib/utl/shared_locker.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UTL__SHARED_LOCKER_H_
#define UCM_AAP_LIBRARY__UCM_LIB_UTL__SHARED_LOCKER_H_

#include <mutex>
#include <memory>
#include <exception>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace utl   {

class SharedLockerRace : public std::exception
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_SharedLocker, CTor);
#endif

public:
    virtual const char* what() const noexcept override
    {
        return "Possible race condition: variable is already locked!";
    }

    virtual ~SharedLockerRace() = default;
};

template<class T>
struct SharedLocker final
{
    SharedLocker(std::shared_ptr<T>& var)
        : variable_(var)
    {}

    SharedLocker<T>(SharedLocker<T>     &&) = delete;
    SharedLocker<T>(SharedLocker<T> const&) = delete;

    SharedLocker<T>& operator=(SharedLocker<T>     &&) = delete;
    SharedLocker<T>& operator=(SharedLocker<T> const&) = delete;

    ~SharedLocker()
    {
        variable_->unlock();
    }

    static std::shared_ptr<T>
    lockit(std::shared_ptr<T>& variable)
    {
        if (not variable->lock())
            throw SharedLockerRace();

        std::shared_ptr<SharedLocker<T>> locker =
                std::make_shared<SharedLocker<T>>(variable);

        return std::shared_ptr<T>(locker, variable.get());
    }

    static void release(std::shared_ptr<T>& variable)
    {
        variable->unlock();
        variable.reset();
    }

private:
    std::shared_ptr<T> variable_;
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UTL__SHARED_LOCKER_H_
