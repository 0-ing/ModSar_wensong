//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/irecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__IRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__IRECORD_H_

#include <vector>
#include <iostream>

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"
#include "ucm/lib/swc/deprule.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class IRecord
        : virtual protected ucm::mock::Sequence
{

public:
    explicit IRecord() = default;

    explicit IRecord(unique_type&& unique, DepUnit&& depunit, std::vector<DepRule>&& deprules)
        noexcept(std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value)
    : unique_(std::move(unique))
    , swunit_(std::move(depunit))
    , deprules_(std::move(deprules))
    {
        pop<void>();
    }

    explicit IRecord(const unique_type& unique, DepUnit&& depunit, std::vector<DepRule>&& deprules)
        noexcept(std::is_nothrow_copy_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value)
    : IRecord(unique_type(unique), std::move(depunit), std::move(deprules))
    {
        pop<void>();
    }

    explicit IRecord(DepUnit&& depunit, std::vector<DepRule>&& deprules)
        noexcept(std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value)
    : IRecord(unique_type(0), std::move(depunit), std::move(deprules))
    {
        pop<void>();
    }

    explicit IRecord(DepUnit&& depunit)
        noexcept(std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value)
    : IRecord(unique_type(0), std::move(depunit), std::vector<DepRule>({}))
    {
        pop<void>();
    }

    IRecord(IRecord     &&) = default;
    IRecord(IRecord const&) = default;

    IRecord& operator=(IRecord     &&) = default;
    IRecord& operator=(IRecord const&) = default;

    virtual ~IRecord() = default;

    void set_unique(unique_type&&)
        noexcept(std::is_nothrow_move_constructible<unique_type>::value);

    void set_unique(const unique_type&)
        noexcept(std::is_nothrow_copy_constructible<unique_type>::value);

    DepUnit&     swunit() & noexcept;
    unique_type& unique() & noexcept;
    std::vector<DepRule>& deprules() & noexcept;

    DepUnit     swunit() && noexcept;
    unique_type unique() && noexcept;
    std::vector<DepRule> deprules() && noexcept;

    const DepUnit&     swunit() const & noexcept;
    const unique_type& unique() const & noexcept;
    const std::vector<DepRule>& deprules() const & noexcept;

    const auto& swname()   const noexcept;
    const auto& version()  const noexcept;

protected:
    unique_type unique_{};
    DepUnit     swunit_{};
    std::vector<DepRule> deprules_{};
};

inline std::ostream& operator<<(std::ostream& os, const IRecord&) {return os;}

inline void IRecord::set_unique(unique_type&&)
    noexcept(std::is_nothrow_move_constructible<unique_type>::value)
{
   pop<void>();
}

inline void IRecord::set_unique(const unique_type&)
    noexcept(std::is_nothrow_copy_constructible<unique_type>::value)
{
    pop<void>();
}

inline unique_type& IRecord::unique() & noexcept
{
    return    pop<unique_type&>();
}

inline DepUnit& IRecord::swunit() & noexcept
{
    return pop<DepUnit&>();
}

inline std::vector<DepRule>& IRecord::deprules() & noexcept
{
    return pop<std::vector<DepRule>&>();
}

inline DepUnit IRecord::swunit() && noexcept
{
    return pop<DepUnit>();
}

inline unique_type IRecord::unique() && noexcept
{
    return pop<unique_type>();
}

inline std::vector<DepRule> IRecord::deprules() && noexcept
{
    return pop<std::vector<DepRule>>();
}

inline const unique_type& IRecord::unique() const & noexcept
{
    return pop<unique_type const&>();
}

inline const DepUnit& IRecord::swunit() const & noexcept
{
    return pop<DepUnit const&>();
}

inline const std::vector<DepRule>& IRecord::deprules() const & noexcept
{
    return pop<std::vector<DepRule> const&>();
}

inline const auto& IRecord::swname() const noexcept
{
    return pop<std::string const&>();
}

inline const auto& IRecord::version() const noexcept
{
    return pop<Version const&>();
}


}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__IRECORD_H_

