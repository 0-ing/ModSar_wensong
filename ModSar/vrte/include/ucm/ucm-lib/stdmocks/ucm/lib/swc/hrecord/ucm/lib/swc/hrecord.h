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

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class HRecord
        : virtual protected ucm::mock::Sequence
{

    static constexpr bool move_noexcept = 
            std::is_nothrow_move_constructible<DepUnit    >::value &&
            std::is_nothrow_move_constructible<unique_type>::value &&
            std::is_nothrow_move_constructible<tstamp_type>::value &&
            std::is_nothrow_move_constructible<action_type>::value &&
            std::is_nothrow_move_constructible<aerror_type>::value;


public:
    static tstamp_type timestamp() noexcept {return pop<tstamp_type>();}

    explicit HRecord() = default;

    explicit HRecord(unique_type&&, unique_type&&, DepUnit&&,
                     tstamp_type&&, action_type&&, aerror_type&&)
        noexcept(move_noexcept)
    {
    }

    explicit HRecord(const unique_type&, const unique_type&, DepUnit&&,
                     const tstamp_type&, const action_type&, const aerror_type&)
        noexcept(move_noexcept)
    {
    }

    explicit HRecord(DepUnit&&, tstamp_type&&, action_type&&, aerror_type&&)
        noexcept(move_noexcept)
    {
    }

    explicit HRecord(DepUnit&&, const tstamp_type&,
                     const action_type&, const aerror_type&)
        noexcept(move_noexcept)
    {
    }


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

inline std::ostream& operator<<(std::ostream& os, const HRecord&) {return os;}

inline DepUnit& HRecord::swunit() & noexcept
{
    return pop<DepUnit&>();
}

inline unique_type& HRecord::unique() & noexcept
{
    return pop<unique_type&>();
}

inline unique_type& HRecord::cookie() & noexcept
{
    return pop<unique_type&>();
}

inline tstamp_type& HRecord::tstamp() & noexcept
{
    return pop<tstamp_type&>();
}

inline action_type& HRecord::action() & noexcept
{
    return pop<action_type&>();
}

inline aerror_type& HRecord::aerror() & noexcept
{
    return pop<aerror_type&>();
}

inline DepUnit HRecord::swunit() && noexcept
{
    return pop<DepUnit>();
}

inline unique_type HRecord::unique() && noexcept
{
    return pop<unique_type>();
}

inline unique_type HRecord::cookie() && noexcept
{
    return pop<unique_type>();
}

inline tstamp_type HRecord::tstamp() && noexcept
{
    return pop<tstamp_type>();
}

inline action_type HRecord::action() && noexcept
{
    return pop<action_type>();
}

inline aerror_type HRecord::aerror() && noexcept
{
    return pop<aerror_type>();
}

inline const unique_type& HRecord::unique() const & noexcept
{
    return pop<unique_type const&>();
}

inline const unique_type& HRecord::cookie() const & noexcept
{
    return pop<unique_type const&>();
}

inline const DepUnit& HRecord::swunit() const & noexcept
{
    return pop<DepUnit const&>();
}

inline const tstamp_type& HRecord::tstamp() const & noexcept
{
    return pop<tstamp_type const&>();
}

inline const action_type& HRecord::action() const & noexcept
{
    return pop<action_type const&>();
}

inline const aerror_type& HRecord::aerror() const & noexcept
{
    return pop<aerror_type const&>();
}

inline const auto& HRecord::swname() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& HRecord::version() const noexcept
{
    return pop<Version const&>();
}


}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__HRECORD_H_

