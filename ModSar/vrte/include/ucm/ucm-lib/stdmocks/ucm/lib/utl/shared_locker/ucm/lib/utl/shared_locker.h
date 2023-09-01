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

#ifndef UCM_AAP_LIBRARY_LIB_UTL_SHARED_LOCKER_H_
#define UCM_AAP_LIBRARY_LIB_UTL_SHARED_LOCKER_H_

#include <mutex>
#include <memory>
#include <exception>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace utl {

class SharedLockerRace
        : public std::exception
        , protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_utl_SharedLocker, CTor);
#endif

public:
    virtual const char* what() const noexcept override
    {
        return pop<const char*>();
    }

    virtual ~SharedLockerRace() = default;
};

template<class T>
struct SharedLocker final
       : virtual protected ucm::mock::Sequence
{
    SharedLocker(std::shared_ptr<T>& var)
        : variable_(var)  {pop<void>();}

    SharedLocker<T>(SharedLocker<T>&&) = delete;
    SharedLocker<T>& operator=(SharedLocker<T>&&) = delete;

    SharedLocker<T>(const SharedLocker<T>&) = delete;
    SharedLocker<T>& operator=(const SharedLocker<T>&) = delete;

    ~SharedLocker()
    {
        variable_->unlock();
    }

    static std::shared_ptr<T>
    lockit(std::shared_ptr<T>& variable)
    {
        return pop<std::shared_ptr<T>>();
    }

    static void release(std::shared_ptr<T>& variable)
    {
        pop<void>();
    }

private:
    std::shared_ptr<T> variable_;
};


}    // namespace utl
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY_LIB_UTL_SHARED_LOCKER_H_
