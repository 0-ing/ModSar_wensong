//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/srecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__SRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__SRECORD_H_

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

class SRecord
{
    static constexpr bool move_noexcept = 
            std::is_nothrow_move_constructible<DepUnit    >::value &&
            std::is_nothrow_move_constructible<unique_type>::value &&
            std::is_nothrow_move_constructible<astate_type>::value &&
            std::is_nothrow_move_constructible<aerror_type>::value;

#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc__SRecord, CTor1);
#endif
public:

    explicit SRecord() = default;

    explicit SRecord(unique_type&&, DepUnit&&,
                     astate_type&&, aerror_type&&)
        noexcept(move_noexcept);

    explicit SRecord(const unique_type&, DepUnit&&,
                     const astate_type&, const aerror_type&)
        noexcept(move_noexcept);

    explicit SRecord(DepUnit&&, astate_type&&, aerror_type&&)
        noexcept(move_noexcept);

    explicit SRecord(DepUnit&&, const astate_type&, const aerror_type&)
        noexcept(move_noexcept);


    SRecord(SRecord     &&) = default;
    SRecord(SRecord const&) = default;

    SRecord& operator=(SRecord     &&) = default;
    SRecord& operator=(SRecord const&) = default;

    virtual ~SRecord() = default;

    DepUnit&     swunit() & noexcept;
    unique_type& unique() & noexcept;
    astate_type& astate() & noexcept;
    aerror_type& aerror() & noexcept;

    DepUnit     swunit() && noexcept;
    unique_type unique() && noexcept;
    astate_type astate() && noexcept;
    aerror_type aerror() && noexcept;

    const DepUnit&     swunit() const & noexcept;
    const unique_type& unique() const & noexcept;
    const astate_type& astate() const & noexcept;
    const aerror_type& aerror() const & noexcept;

    const auto& swname()  const noexcept;
    const auto& version() const noexcept;

protected:
    DepUnit     swunit_{};
    unique_type unique_{};
    astate_type astate_{};
    aerror_type aerror_{};
};

std::ostream& operator<<(std::ostream&, const SRecord&);

inline DepUnit& SRecord::swunit() & noexcept
{
    return swunit_;
}

inline unique_type& SRecord::unique() & noexcept
{
    return unique_;
}

inline astate_type& SRecord::astate() & noexcept
{
    return astate_;
}

inline aerror_type& SRecord::aerror() & noexcept
{
    return aerror_;
}

inline DepUnit SRecord::swunit() && noexcept
{
    return std::move(swunit_);
}

inline unique_type SRecord::unique() && noexcept
{
    return std::move(unique_);
}

inline astate_type SRecord::astate() && noexcept
{
    return std::move(astate_);
}

inline aerror_type SRecord::aerror() && noexcept
{
    return std::move(aerror_);
}

inline const unique_type& SRecord::unique() const & noexcept
{
    return unique_;
}

inline const DepUnit& SRecord::swunit() const & noexcept
{
    return swunit_;
}

inline const astate_type& SRecord::astate() const & noexcept
{
    return astate_;
}

inline const aerror_type& SRecord::aerror() const & noexcept
{
    return aerror_;
}

inline const auto& SRecord::swname() const noexcept
{
    return swunit_.swname();
}

inline const auto& SRecord::version() const noexcept
{
    return swunit_.version();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__SRECORD_H_

