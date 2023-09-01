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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/types.h"
#include "ucm/lib/swc/depunit.h"
#include "ucm/lib/swc/deprule.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {

class IRecord
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor1);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor2);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor3);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor4);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor5);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor6);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor7);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor8);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, CTor9);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, MoveMembers1);
    FRIEND_TEST(Test_ucm_lib_swc__IRecord, MoveMembers2);
#endif
public:
    explicit IRecord() = default;

    explicit IRecord(unique_type&&, DepUnit&&, std::vector<DepRule>&&)
        noexcept(std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value);

    explicit IRecord(const unique_type&, DepUnit&&, std::vector<DepRule>&&)
        noexcept(std::is_nothrow_copy_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value);

    explicit IRecord(DepUnit&&, std::vector<DepRule>&&)
        noexcept(std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value);

    explicit IRecord(DepUnit&&)
        noexcept(std::is_nothrow_move_constructible<unique_type>::value &&
                 std::is_nothrow_move_constructible<DepUnit>::value     &&
                 std::is_nothrow_move_constructible<
                     std::vector<DepRule>>::value);

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

std::ostream& operator<<(std::ostream&, const IRecord&);

inline void IRecord::set_unique(unique_type&& unique)
    noexcept(std::is_nothrow_move_constructible<unique_type>::value)
{
    unique_ = std::move_if_noexcept(unique);
}

inline void IRecord::set_unique(const unique_type& unique)
    noexcept(std::is_nothrow_copy_constructible<unique_type>::value)
{
    unique_ = unique;
}

inline unique_type& IRecord::unique() & noexcept
{
    return unique_;
}

inline DepUnit& IRecord::swunit() & noexcept
{
    return swunit_;
}

inline std::vector<DepRule>& IRecord::deprules() & noexcept
{
    return deprules_;
}

inline DepUnit IRecord::swunit() && noexcept
{
    return std::move(swunit_);
}

inline unique_type IRecord::unique() && noexcept
{
    return std::move(unique_);
}

inline std::vector<DepRule> IRecord::deprules() && noexcept
{
    return std::move(deprules_);
}

inline const unique_type& IRecord::unique() const & noexcept
{
    return unique_;
}

inline const DepUnit& IRecord::swunit() const & noexcept
{
    return swunit_;
}

inline const std::vector<DepRule>& IRecord::deprules() const & noexcept
{
    return deprules_;
}

inline const auto& IRecord::swname() const noexcept
{
    return swunit_.swname();
}

inline const auto& IRecord::version() const noexcept
{
    return swunit_.version();
}


}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC__IRECORD_H_

