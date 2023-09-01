//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/hrecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__HRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__HRECORD_H_

#include <vector>
#include <iostream>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class HRecord
{

    static constexpr bool move_noexcept = 
            std::is_nothrow_move_constructible<DepUnit    >::value &&
            std::is_nothrow_move_constructible<unique_type>::value &&
            std::is_nothrow_move_constructible<tstamp_type>::value &&
            std::is_nothrow_move_constructible<action_type>::value &&
            std::is_nothrow_move_constructible<aerror_type>::value;

#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor1);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor2);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor3);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor4);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor5);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor6);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor7);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor8);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, CTor9);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, MoveMembers1);
    FRIEND_TEST(Test_ucm_lib_swc__HRecord, MoveMembers2);
#endif
public:
    static tstamp_type timestamp() noexcept;

    explicit HRecord() = default;

    explicit HRecord(unique_type&&, unique_type&&, DepUnit&&,
                     tstamp_type&&, action_type&&, aerror_type&&)
        noexcept(move_noexcept);

    explicit HRecord(const unique_type&, const unique_type&, DepUnit&&,
                     const tstamp_type&, const action_type&, const aerror_type&)
        noexcept(move_noexcept);

    explicit HRecord(DepUnit&&, tstamp_type&&, action_type&&, aerror_type&&)
        noexcept(move_noexcept);

    explicit HRecord(DepUnit&&, const tstamp_type&,
                     const action_type&, const aerror_type&)
        noexcept(move_noexcept);

    /* explicit HRecord(DepUnit, tstamp_type, action_type, aerror_type) */
    /*     noexcept(move_noexcept); */


    HRecord(HRecord     &&) = default;
    HRecord(HRecord const&) = default;

    HRecord& operator=(HRecord     &&) = default;
    HRecord& operator=(HRecord const&) = default;

    virtual ~HRecord() = default;

    DepUnit&     swunit() & noexcept;
    unique_type& unique() & noexcept;
    unique_type& cookie() & noexcept;
    tstamp_type& tstamp() & noexcept;
    action_type& action() & noexcept;
    aerror_type& aerror() & noexcept;

    DepUnit     swunit() && noexcept;
    unique_type unique() && noexcept;
    unique_type cookie() && noexcept;
    tstamp_type tstamp() && noexcept;
    action_type action() && noexcept;
    aerror_type aerror() && noexcept;

    const DepUnit&     swunit() const & noexcept;
    const unique_type& unique() const & noexcept;
    const unique_type& cookie() const & noexcept;
    const tstamp_type& tstamp() const & noexcept;
    const action_type& action() const & noexcept;
    const aerror_type& aerror() const & noexcept;


    const auto& swname()  const noexcept;
    const auto& version() const noexcept;

protected:
    DepUnit     swunit_{};
    unique_type unique_{};
    unique_type cookie_{};
    tstamp_type tstamp_{};
    action_type action_{};
    aerror_type aerror_{};
};

std::ostream& operator<<(std::ostream&, const HRecord&);

inline DepUnit& HRecord::swunit() & noexcept
{
    return swunit_;
}

inline unique_type& HRecord::unique() & noexcept
{
    return unique_;
}

inline unique_type& HRecord::cookie() & noexcept
{
    return cookie_;
}

inline tstamp_type& HRecord::tstamp() & noexcept
{
    return tstamp_;
}

inline action_type& HRecord::action() & noexcept
{
    return action_;
}

inline aerror_type& HRecord::aerror() & noexcept
{
    return aerror_;
}

inline DepUnit HRecord::swunit() && noexcept
{
    return std::move(swunit_);
}

inline unique_type HRecord::unique() && noexcept
{
    return std::move(unique_);
}

inline unique_type HRecord::cookie() && noexcept
{
    return std::move(cookie_);
}

inline tstamp_type HRecord::tstamp() && noexcept
{
    return std::move(tstamp_);
}

inline action_type HRecord::action() && noexcept
{
    return std::move(action_);
}

inline aerror_type HRecord::aerror() && noexcept
{
    return std::move(aerror_);
}

inline const unique_type& HRecord::unique() const & noexcept
{
    return unique_;
}

inline const unique_type& HRecord::cookie() const & noexcept
{
    return cookie_;
}

inline const DepUnit& HRecord::swunit() const & noexcept
{
    return swunit_;
}

inline const tstamp_type& HRecord::tstamp() const & noexcept
{
    return tstamp_;
}

inline const action_type& HRecord::action() const & noexcept
{
    return action_;
}

inline const aerror_type& HRecord::aerror() const & noexcept
{
    return aerror_;
}

inline const auto& HRecord::swname() const noexcept
{
    return swunit_.swname();
}

inline const auto& HRecord::version() const noexcept
{
    return swunit_.version();
}


}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__HRECORD_H_

