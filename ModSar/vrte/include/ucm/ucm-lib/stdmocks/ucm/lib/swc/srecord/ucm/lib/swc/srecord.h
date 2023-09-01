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

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class SRecord
    : virtual protected ucm::mock::Sequence
{
    static constexpr bool move_noexcept = 
            std::is_nothrow_move_constructible<DepUnit    >::value &&
            std::is_nothrow_move_constructible<unique_type>::value &&
            std::is_nothrow_move_constructible<astate_type>::value &&
            std::is_nothrow_move_constructible<aerror_type>::value;

public:

    explicit SRecord() = default;

    explicit SRecord(unique_type&&, DepUnit&&,
                     astate_type&&, aerror_type&&)
        noexcept(move_noexcept)
    {
    }

    explicit SRecord(const unique_type&, DepUnit&&,
                     const astate_type&, const aerror_type&)
        noexcept(move_noexcept)
    {
    }

    explicit SRecord(DepUnit&&, astate_type&&, aerror_type&&)
        noexcept(move_noexcept)
    {
    }

    explicit SRecord(DepUnit&&, const astate_type&, const aerror_type&)
        noexcept(move_noexcept)
    {
    }


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
    return pop<DepUnit&>();
}

inline unique_type& SRecord::unique() & noexcept
{
    return pop<unique_type&>();
}

inline astate_type& SRecord::astate() & noexcept
{
    return pop<astate_type&>();
}

inline aerror_type& SRecord::aerror() & noexcept
{
    return pop<aerror_type&>();
}

inline DepUnit SRecord::swunit() && noexcept
{
    return pop<DepUnit>();
}

inline unique_type SRecord::unique() && noexcept
{
    return pop<unique_type>();
}

inline astate_type SRecord::astate() && noexcept
{
    return pop<astate_type>();
}

inline aerror_type SRecord::aerror() && noexcept
{
    return pop<aerror_type>();
}

inline const unique_type& SRecord::unique() const & noexcept
{
    return pop<unique_type const&>();
}

inline const DepUnit& SRecord::swunit() const & noexcept
{
    return pop<DepUnit const&>();
}

inline const astate_type& SRecord::astate() const & noexcept
{
    return pop<astate_type const&>();
}

inline const aerror_type& SRecord::aerror() const & noexcept
{
    return pop<aerror_type const&>();
}

inline const auto& SRecord::swname() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& SRecord::version() const noexcept
{
    return pop<Version const&>();
}

}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__SRECORD_H_

